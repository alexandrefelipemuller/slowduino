/**
 * @file decoders.c
 * @brief Implementacao dos decoders de trigger - port C/HC08
 *
 * Logica 1:1 com decoders.cpp da branch tiny (deteccao de gap dinamica,
 * validacao de contagem de dentes, protecao contra ruido/EMI, agendamento
 * direto de injecao/ignicao na ISR). Diferencas sao so de HARDWARE:
 *
 *   - AVR: attachInterrupt(INT0, lambda, RISING/FALLING/CHANGE)
 *     HC08: pino dedicado IRQ (cap. 9 do datasheet), SO borda de descida
 *     (MODE=0). Ver ressalva grande em decoders.h - RISING/CHANGE nao sao
 *     suportados neste pino, NAO fingido aqui.
 *   - AVR: ISR troca em runtime via ponteiro de funcao currentTriggerISR,
 *     chamada de dentro da lambda do attachInterrupt.
 *     HC08: mesma tecnica (ponteiro de funcao), so que chamada de dentro
 *     da UNICA isr_irq() fixa no vetor de hardware (nao da pra trocar o
 *     vetor em si, so o que ele chama).
 */

#include "decoders.h"
#include "globals.h"
#include "scheduler.h"
#include "timebase.h"
#include "mc68hc908gp32_sfr.h"

#define TRIGGER_MISSING_TOOTH  0
#define TRIGGER_BASIC_DIST     1
#define TRIGGER_EDGE_RISING    0
#define TRIGGER_EDGE_FALLING   1
#define TRIGGER_EDGE_BOTH      2

#define SYNC_TIMEOUT  1000UL
#define INJ_MIN_PW    500
#define INJ_MAX_PW    20000
#define DWELL_MIN     1000
#define DWELL_MAX     8000

#define INJECTION_ANGLE 270  /* 90 graus BTDC - mesma razao doc no AVR */

volatile struct TriggerState triggerState;
volatile uint8_t revolutionCounter = 0;

/* Pulsos por dente fisico. No AVR, CHANGE=2; aqui so FALLING existe no
 * pino IRQ dedicado, entao isto fica fixo em 1 (ver decoders.h). */
static uint8_t triggerEdgesPerTooth = 1;

typedef void (*TriggerISR)(void);
static volatile TriggerISR currentTriggerISR;

/* Precisa das mesmas structs de injector polling que scheduler.h/.c do AVR
 * definiam (InjectorPollingState) - ainda nao portadas para este arquivo;
 * placeholder minimo so para nao travar a compilacao do decoder agora. Ver
 * TODO no README: portar scheduler de injecao (polling) junto com fuel.c. */
typedef struct {
  bool isScheduled, isOpen;
  uint32_t openTime, closeTime;
} InjectorPollingState;
static InjectorPollingState injector1Polling;
static InjectorPollingState injector2Polling;

static void scheduleInjectorPolling(InjectorPollingState *injState, uint32_t startDelay, uint16_t pulseWidth) {
  uint32_t now = micros();
  injState->openTime = now + startDelay;
  injState->closeTime = injState->openTime + pulseWidth;
  injState->isScheduled = true;
  injState->isOpen = false;
}

/* ==========================================================================
 * AGENDAMENTO DIRETO NA ISR (identico ao AVR - scheduleInjectionISR/
 * scheduleIgnitionISR de decoders.cpp)
 * ========================================================================== */
static void scheduleInjectionISR(void) {
  uint32_t timeToInjection;
  uint16_t pw1, pw2;

  if (triggerState.revolutionTime == 0) return;

  timeToInjection = ((uint32_t)INJECTION_ANGLE * triggerState.revolutionTime) / 360UL;

  pw1 = currentStatus.PW1;
  pw2 = currentStatus.PW2;
  if (pw1 < INJ_MIN_PW || pw1 > INJ_MAX_PW) pw1 = INJ_MIN_PW;
  if (pw2 < INJ_MIN_PW || pw2 > INJ_MAX_PW) pw2 = INJ_MIN_PW;

  if (revolutionCounter == 0) {
    scheduleInjectorPolling(&injector1Polling, timeToInjection, pw1);
  } else {
    scheduleInjectorPolling(&injector2Polling, timeToInjection, pw2);
  }
}

static void scheduleIgnitionISR(void) {
  int8_t advance;
  uint16_t dwellTime, dwellAngle, sparkAngle, dwellStartAngle;
  uint32_t timeToDwell;

  if (triggerState.revolutionTime == 0) return;

  advance = currentStatus.advance;
  dwellTime = currentStatus.dwell;
  if (dwellTime < DWELL_MIN) dwellTime = DWELL_MIN;
  if (dwellTime > DWELL_MAX) dwellTime = DWELL_MAX;

  dwellAngle = (uint16_t)(((uint32_t)dwellTime * 360UL) / triggerState.revolutionTime);

  if (dwellAngle > 180) {
    dwellAngle = 180;
    dwellTime = (uint16_t)((180UL * triggerState.revolutionTime) / 360UL);
  }

  sparkAngle = (advance > 0) ? (uint16_t)(360 - advance) : 360;

  if (sparkAngle > dwellAngle) {
    dwellStartAngle = sparkAngle - dwellAngle;
  } else {
    dwellStartAngle = 0;
    dwellAngle = sparkAngle;
    dwellTime = (uint16_t)(((uint32_t)dwellAngle * triggerState.revolutionTime) / 360UL);
  }

  timeToDwell = ((uint32_t)dwellStartAngle * triggerState.revolutionTime) / 360UL;

  if (revolutionCounter == 0) {
    setIgnitionSchedule(&ignitionSchedule1, timeToDwell, dwellTime, 1);
  } else {
    setIgnitionSchedule(&ignitionSchedule2, timeToDwell, dwellTime, 2);
  }
}

/* ==========================================================================
 * ISRs DE TRIGGER (chamadas via ponteiro por isr_irq(), ver fim do arquivo)
 * ========================================================================== */
static void triggerPri_MissingTooth(void) {
  uint32_t curTime = micros();
  uint32_t baseGap, dynamicThreshold;
  bool isCranking, isGap;

  triggerState.curGap = curTime - triggerState.toothLastToothTime;

  if (triggerState.curGap < 50) return;
  if (triggerState.lastGap > 0 && triggerState.curGap < (triggerState.lastGap / 3)) return;

  triggerState.toothLastToothTime = curTime;
  triggerState.toothCurrentCount++;

  if (triggerState.toothCurrentCount > (uint8_t)(triggerState.toothTotalCount * 2)) {
    triggerState.toothCurrentCount = 1;
    triggerState.hasSync = false;
  }

  isCranking = (currentStatus.RPM > 0) &&
               (currentStatus.RPM < ((uint16_t)configPage1.crankRPM * 10));

  baseGap = (triggerState.lastGap > 0) ? triggerState.lastGap : triggerState.curGap;
  dynamicThreshold = isCranking ? (baseGap + ((baseGap * 2) / 5))
                                 : (baseGap + (baseGap >> 1));
  isGap = (triggerState.curGap > dynamicThreshold);

  if (isGap) {
    uint16_t expectedPulses = (uint16_t)triggerState.triggerActualTeeth * triggerEdgesPerTooth;
    uint16_t toleranceWindow = isCranking ? 20 : 10;

    if (triggerState.toothCurrentCount >= (expectedPulses - toleranceWindow) &&
        triggerState.toothCurrentCount <= (expectedPulses + toleranceWindow)) {

      triggerState.hasSync = true;
      triggerState.syncLossCounter = 0;
      triggerState.toothOneTime = curTime;

      if (triggerState.toothLastMinusOneTime > 0) {
        triggerState.revolutionTime = curTime - triggerState.toothLastMinusOneTime;
      }
      triggerState.toothLastMinusOneTime = curTime;
      triggerState.toothCurrentCount = 1;
      revolutionCounter = (revolutionCounter == 0) ? 1 : 0;

      if (triggerState.revolutionTime > 0) {
        scheduleInjectionISR();
        scheduleIgnitionISR();
      }
    } else {
      triggerState.toothCurrentCount = 1;
      triggerState.syncLossCounter++;
      if (triggerState.syncLossCounter > 10) {
        triggerState.hasSync = false;
      }
    }
  }

  triggerState.lastGap = triggerState.curGap;
}

static void triggerPri_BasicDistributor(void) {
  uint32_t curTime = micros();

  triggerState.curGap = curTime - triggerState.toothLastToothTime;
  if (triggerState.curGap < triggerState.triggerFilterTime) return;

  triggerState.hasSync = true;
  triggerState.toothCurrentCount = 1;
  triggerState.toothOneTime = curTime;
  triggerState.revolutionTime = triggerState.curGap;
  triggerState.toothLastToothTime = curTime;
  triggerState.toothLastMinusOneTime = curTime;
  revolutionCounter = (revolutionCounter == 0) ? 1 : 0;

  scheduleInjectionISR();
  scheduleIgnitionISR();
}

/* ==========================================================================
 * INICIALIZACAO
 * ========================================================================== */
void triggerSetup_MissingTooth(void) {
  triggerState.triggerTeeth = configPage2.triggerTeeth;
  triggerState.triggerMissing = configPage2.triggerMissing;
  triggerState.triggerActualTeeth = triggerState.triggerTeeth - triggerState.triggerMissing;
  triggerState.toothAngle = (uint16_t)(3600 / triggerState.triggerTeeth);
  triggerState.triggerFilterTime = 50;
  triggerState.toothTotalCount = triggerState.triggerTeeth;

  currentTriggerISR = triggerPri_MissingTooth;
}

void triggerSetup_BasicDistributor(void) {
  triggerState.triggerTeeth = 1;
  triggerState.triggerMissing = 0;
  triggerState.triggerActualTeeth = 1;
  triggerState.toothAngle = 3600;
  triggerState.triggerFilterTime = 500;
  triggerState.toothTotalCount = 1;

  currentTriggerISR = triggerPri_BasicDistributor;
}

void triggerInit(void) {
  resetTriggerState();

  if (configPage2.triggerPattern == TRIGGER_BASIC_DIST) {
    triggerSetup_BasicDistributor();
  } else {
    triggerSetup_MissingTooth();
  }

  attachTriggerInterrupt();
}

void calculateRPM(void) {
  if (!triggerState.hasSync) {
    triggerState.RPM = 0;
    currentStatus.RPM = 0;
    currentStatus.hasSync = false;
    return;
  }

  if (triggerState.revolutionTime > 0) {
    uint32_t rpm = MICROS_PER_SEC * 60UL / triggerState.revolutionTime;
    if (rpm > 15000) rpm = 15000;
    if (rpm < 100) rpm = 0;

    triggerState.RPM = (uint16_t)rpm;

    noInterrupts();
    currentStatus.RPM = triggerState.RPM;
    currentStatus.hasSync = true;
    interrupts();
  } else {
    triggerState.RPM = 0;
    currentStatus.RPM = 0;
  }
}

void checkSyncLoss(void) {
  uint32_t timeSinceLastTooth = micros() - triggerState.toothLastToothTime;

  if (timeSinceLastTooth > (SYNC_TIMEOUT * 1000UL)) {
    noInterrupts();
    triggerState.hasSync = false;
    currentStatus.hasSync = false;
    currentStatus.RPM = 0;
    interrupts();
  }
}

uint32_t angleToTime(uint16_t angle) {
  if (triggerState.revolutionTime == 0) return 0;
  return ((uint32_t)angle * triggerState.revolutionTime) / 360UL;
}

uint16_t timeToAngle(uint32_t time) {
  if (triggerState.revolutionTime == 0) return 0;
  return (uint16_t)((time * 360UL) / triggerState.revolutionTime);
}

uint16_t getCrankAngle(void) {
  uint32_t timeSinceToothOne;
  uint16_t angle;

  if (!triggerState.hasSync || triggerState.revolutionTime == 0) return 0;

  timeSinceToothOne = micros() - triggerState.toothOneTime;
  if (timeSinceToothOne >= triggerState.revolutionTime) {
    timeSinceToothOne = triggerState.revolutionTime - 1;
  }

  angle = (uint16_t)((timeSinceToothOne * 360UL) / triggerState.revolutionTime);
  return angle;
}

/* ==========================================================================
 * INTERRUPCAO EXTERNA (IRQ) - N=2, $FFFA (ver mc68hc908gp32_sfr.h)
 * ========================================================================== */
void attachTriggerInterrupt(void) {
  /* MODE=0: borda de descida apenas (unico modo suportado pelo pino IRQ
   * dedicado - ver ressalva grande em decoders.h). configPage2.triggerEdge
   * RISING/BOTH nao tem efeito aqui ainda - nao implementado, nao fingido. */
  INTSCR &= (uint8_t)~(1 << INTSCR_MODE);

  /* Desmascara a interrupcao IRQ (IMASK=0 libera) */
  INTSCR &= (uint8_t)~(1 << INTSCR_IMASK);
}

void resetTriggerState(void) {
  noInterrupts();

  triggerState.toothLastToothTime = 0;
  triggerState.toothLastMinusOneTime = 0;
  triggerState.revolutionTime = 0;
  triggerState.toothOneTime = 0;

  triggerState.toothCurrentCount = 0;
  triggerState.toothTotalCount = 0;
  triggerState.triggerActualTeeth = 0;

  triggerState.curGap = 0;
  triggerState.lastGap = 0;
  triggerState.hasSync = false;
  triggerState.syncLossCounter = 0;

  triggerState.RPM = 0;
  triggerState.toothPeriod = 0;

  currentStatus.hasSync = false;
  currentStatus.RPM = 0;

  revolutionCounter = 0;

  interrupts();
}

/* N=2 verificado empiricamente (0xFFFE - 2*2 = 0xFFFA = vetor IRQ). Com
 * MODE=0 (borda de descida), o proprio vector fetch reconhece a
 * interrupcao automaticamente - nao precisa escrever ACK em INTSCR aqui
 * (isso so seria necessario em MODE=1, nivel+borda, nao usado). */
void isr_irq(void) __interrupt(2) {
  if (currentTriggerISR != 0) {
    currentTriggerISR();
  }
}
