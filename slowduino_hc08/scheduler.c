/**
 * @file scheduler.c
 * @brief Implementacao do scheduler de ignicao (ver scheduler.h)
 *
 * Logica 1:1 com scheduler.cpp da branch tiny (setIgnitionSchedule,
 * armIgnitionCompare, handleIgnitionChannel, incluindo a protecao de
 * wraparound do contador de 16 bits) - so trocando os registradores AVR
 * (OCR1A/OCR1B/TCNT1/ISR) pelos equivalentes HC08 (T1CH0H/T1CH1H/T1CNTH:L/
 * __interrupt). C nao tem overload de funcao como o C++ do AVR usa para
 * escolher entre "porta compareReg direto" vs "ponteiro de funcao" (porte
 * STM32) - aqui so existe a variante de registrador direto, que e a unica
 * usada no AVR mesmo.
 */

#include "scheduler.h"
#include "timebase.h"

static const uint16_t IGNITION_MIN_DELAY_US = 25;

volatile IgnitionSchedule ignitionSchedule1 = {SCHED_OFF, 0, 0, 0, 1};
volatile IgnitionSchedule ignitionSchedule2 = {SCHED_OFF, 0, 0, 0, 2};

/* PLACEHOLDER: pino real das bobinas na placa Slowduino-HC08 ainda nao
 * definido - usando PTA0/PTA1 so para ter algo observavel no simulador. */
#define COIL1_BIT 0x01
#define COIL2_BIT 0x02

static void beginCoil1Charge(void) { PTA |= COIL1_BIT; }
static void endCoil1Charge(void)   { PTA &= (uint8_t)~COIL1_BIT; }
static void beginCoil2Charge(void) { PTA |= COIL2_BIT; }
static void endCoil2Charge(void)   { PTA &= (uint8_t)~COIL2_BIT; }

/* PLACEHOLDER: pinos reais dos injetores na placa Slowduino-HC08 ainda
 * nao definidos - PTB0/PTB1/PTB2 so para ter algo observavel/testavel. */
#define INJ1_BIT 0x01
#define INJ2_BIT 0x02
#define INJ3_BIT 0x04

static void openInjector1(void)  { PTB |= INJ1_BIT; }
static void closeInjector1(void) { PTB &= (uint8_t)~INJ1_BIT; }
static void openInjector2(void)  { PTB |= INJ2_BIT; }
static void closeInjector2(void) { PTB &= (uint8_t)~INJ2_BIT; }
static void openInjector3(void)  { PTB |= INJ3_BIT; }
static void closeInjector3(void) { PTB &= (uint8_t)~INJ3_BIT; }

InjectorPollingState injector1Polling;
InjectorPollingState injector2Polling;
InjectorPollingState injector3Polling;

void scheduleInjectorPolling(InjectorPollingState *injState, uint32_t startDelay, uint16_t pulseWidth) {
  uint32_t now = micros();
  injState->openTime = now + startDelay;
  injState->closeTime = injState->openTime + pulseWidth;
  injState->isScheduled = true;
  injState->isOpen = false;
}

void processInjectorPolling(void) {
  uint32_t now = micros();

  if (injector1Polling.isScheduled) {
    if (!injector1Polling.isOpen && now >= injector1Polling.openTime) {
      openInjector1();
      injector1Polling.isOpen = true;
    } else if (injector1Polling.isOpen && now >= injector1Polling.closeTime) {
      closeInjector1();
      injector1Polling.isOpen = false;
      injector1Polling.isScheduled = false;
    }
  }

  if (injector2Polling.isScheduled) {
    if (!injector2Polling.isOpen && now >= injector2Polling.openTime) {
      openInjector2();
      injector2Polling.isOpen = true;
    } else if (injector2Polling.isOpen && now >= injector2Polling.closeTime) {
      closeInjector2();
      injector2Polling.isOpen = false;
      injector2Polling.isScheduled = false;
    }
  }

  if (injector3Polling.isScheduled) {
    if (!injector3Polling.isOpen && now >= injector3Polling.openTime) {
      openInjector3();
      injector3Polling.isOpen = true;
    } else if (injector3Polling.isOpen && now >= injector3Polling.closeTime) {
      closeInjector3();
      injector3Polling.isOpen = false;
      injector3Polling.isScheduled = false;
    }
  }
}

void schedulerInit(void) {
  DDRA |= (COIL1_BIT | COIL2_BIT);  /* bobinas como saida */
  DDRB |= (INJ1_BIT | INJ2_BIT | INJ3_BIT);  /* injetores como saida */
  endCoil1Charge();
  endCoil2Charge();
  closeInjector1();
  closeInjector2();
  closeInjector3();

  /* Reset do contador + prescaler, depois arma canais 0 e 1 em modo
   * "software compare only" (MSxA=1, ELSxB:ELSxA=00 - ver ressalva de
   * verificacao pendente no topo de scheduler.h) e liga TSTOP=0 (roda). */
  T1SC = (1 << T1SC_TRST);
  T1SC0 = (1 << TxSCx_MSxA);
  T1SC0 |= (1 << TxSCx_CHxIE);
  T1SC1 = (1 << TxSCx_MSxA) | (1 << TxSCx_CHxIE);
  T1SC = (6 << T1SC_PS0);  /* PS[2:0]=110 -> /64. Ver US_TO_TIMER1 em scheduler.h */
}

static void handleIgnitionChannel(volatile IgnitionSchedule *schedule,
                                   void (*beginCharge)(void),
                                   void (*endCharge)(void),
                                   volatile uint16_t *compareReg) {
  if (schedule->status == SCHED_PENDING) {
    schedule->status = SCHED_RUNNING;
    beginCharge();
    *compareReg = schedule->endCompare;

    if ((int16_t)(getTimer1Count() - schedule->endCompare) >= 0) {
      schedule->status = SCHED_OFF;
      endCharge();
    }
    return;
  }

  if (schedule->status == SCHED_RUNNING) {
    schedule->status = SCHED_OFF;
    endCharge();
  }
}

static void armIgnitionCompare(volatile IgnitionSchedule *schedule,
                                void (*beginCharge)(void),
                                void (*endCharge)(void),
                                volatile uint16_t *compareReg) {
  *compareReg = schedule->startCompare;

  if ((int16_t)(getTimer1Count() - schedule->startCompare) >= 0) {
    handleIgnitionChannel(schedule, beginCharge, endCharge, compareReg);
  }
}

void setIgnitionSchedule(volatile IgnitionSchedule *schedule, uint32_t startTime,
                          uint16_t duration, uint8_t channel) {
  uint32_t startTicks, durationTicks, totalTicks, minTicks;
  uint16_t currentCount, startTicks16, durationTicks16;

  if (channel > 2) {
    schedule->status = SCHED_OFF;
    return;
  }

  if (schedule->status == SCHED_RUNNING) {
    schedule->status = SCHED_OFF;
    if (schedule->channel == 1) { endCoil1Charge(); } else { endCoil2Charge(); }
  }

  startTicks = US_TO_TIMER1(startTime);
  durationTicks = US_TO_TIMER1(duration);
  if (durationTicks == 0) { durationTicks = 1; }

  totalTicks = startTicks + durationTicks;
  minTicks = US_TO_TIMER1(IGNITION_MIN_DELAY_US);

  if (startTicks < minTicks) {
    startTicks = minTicks;
    if (totalTicks > startTicks) {
      durationTicks = totalTicks - startTicks;
    } else {
      durationTicks = 1;
    }
  }

  currentCount = getTimer1Count();
  startTicks16 = (uint16_t)startTicks;
  durationTicks16 = (uint16_t)durationTicks;

  schedule->startCompare = currentCount + startTicks16;
  schedule->endCompare = schedule->startCompare + durationTicks16;
  schedule->duration = durationTicks16;
  schedule->channel = channel;
  schedule->status = SCHED_PENDING;

  if (channel == 1) {
    armIgnitionCompare(schedule, beginCoil1Charge, endCoil1Charge, (volatile uint16_t *)&T1CH0H);
  } else {
    armIgnitionCompare(schedule, beginCoil2Charge, endCoil2Charge, (volatile uint16_t *)&T1CH1H);
  }
}

void clearIgnitionSchedule(volatile IgnitionSchedule *schedule) {
  schedule->status = SCHED_OFF;
  if (schedule->channel == 1) {
    endCoil1Charge();
  } else if (schedule->channel == 2) {
    endCoil2Charge();
  }
}

/* ISRs - N=4 e N=5 verificados empiricamente (ver mc68hc908gp32_sfr.h) */
void isr_tim1_ch0(void) __interrupt(4) {
  handleIgnitionChannel(&ignitionSchedule1, beginCoil1Charge, endCoil1Charge, (volatile uint16_t *)&T1CH0H);
}

void isr_tim1_ch1(void) __interrupt(5) {
  handleIgnitionChannel(&ignitionSchedule2, beginCoil2Charge, endCoil2Charge, (volatile uint16_t *)&T1CH1H);
}
