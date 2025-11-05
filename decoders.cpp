/**
 * @file decoders.cpp
 * @brief Implementação dos decoders de trigger
 */

#include "decoders.h"
#include "scheduler.h"
#include "fuel.h"
#include "ignition.h"

// Forward declarations
void scheduleInjection();
void scheduleIgnition();

// Estado global do trigger
volatile struct TriggerState triggerState;

// Ponteiro para ISR atual (permite trocar decoder dinamicamente)
typedef void (*TriggerISR)(void);
volatile TriggerISR currentTriggerISR = nullptr;

// Controle de sequenciamento
volatile uint8_t revolutionCounter = 0;  // 0 ou 1 (para alternar cilindros)

// Ângulos de evento
#define INJECTION_ANGLE 355   // 5° BTDC (fixo - pode ser configurável depois)

// ============================================================================
// FUNÇÕES INLINE PARA AGENDAMENTO RÁPIDO NA ISR
// ============================================================================

// Agenda injeção - CHAMADO DIRETAMENTE DA ISR
inline void scheduleInjectionISR() __attribute__((always_inline));
inline void scheduleInjectionISR() {
  if (triggerState.revolutionTime == 0) return;

  // Calcula tempo até ângulo de injeção
  uint32_t timeToInjection = ((uint32_t)INJECTION_ANGLE * triggerState.revolutionTime) / 360UL;

  // Obtém PW (calculado no loop principal)
  uint16_t pw = currentStatus.PW1;

  // Valida PW
  if (pw < INJ_MIN_PW || pw > INJ_MAX_PW) {
    pw = INJ_MIN_PW;
  }

  // Agenda baseado em revolução (wasted paired)
  if (revolutionCounter == 0) {
    setFuelSchedule(&fuelSchedule1, timeToInjection, pw, 1);
  } else {
    setFuelSchedule(&fuelSchedule2, timeToInjection, pw, 2);
  }
}

// Agenda ignição - CHAMADO DIRETAMENTE DA ISR
inline void scheduleIgnitionISR() __attribute__((always_inline));
inline void scheduleIgnitionISR() {
  if (triggerState.revolutionTime == 0) return;

  // Obtém valores (calculados no loop principal)
  int8_t advance = currentStatus.advance;
  uint16_t dwellTime = currentStatus.dwell;

  // Valida valores
  if (dwellTime < DWELL_MIN) dwellTime = DWELL_MIN;
  if (dwellTime > DWELL_MAX) dwellTime = DWELL_MAX;

  // Calcula ângulo do dwell em graus
  uint16_t dwellAngle = ((uint32_t)dwellTime * 360UL) / triggerState.revolutionTime;

  // Ângulo de faísca (advance é BTDC, então 360 - advance)
  // Ex: 15° BTDC = 345° ATDC
  uint16_t sparkAngle = (advance > 0) ? (360 - advance) : 360;

  // Ângulo de início do dwell (antes da faísca)
  uint16_t dwellStartAngle = (sparkAngle > dwellAngle) ? (sparkAngle - dwellAngle) : 0;

  // Calcula tempo até início do dwell
  uint32_t timeToDwell = ((uint32_t)dwellStartAngle * triggerState.revolutionTime) / 360UL;

  // Agenda baseado em revolução
  if (revolutionCounter == 0) {
    setIgnitionSchedule(&ignitionSchedule1, timeToDwell, dwellTime, 1);
  } else {
    setIgnitionSchedule(&ignitionSchedule2, timeToDwell, dwellTime, 2);
  }
}

// ============================================================================
// INICIALIZAÇÃO
// ============================================================================

void triggerInit() {
  resetTriggerState();

  // Seleciona decoder baseado na configuração
  switch (configPage2.triggerPattern) {
    case TRIGGER_MISSING_TOOTH:
      triggerSetup_MissingTooth();
      break;

    case TRIGGER_BASIC_DIST:
      triggerSetup_BasicDistributor();
      break;

    default:
      // Fallback para missing tooth
      triggerSetup_MissingTooth();
      break;
  }

  // Anexa interrupção
  attachTriggerInterrupt();

  DEBUG_PRINTLN(F("Trigger inicializado"));
}

// ============================================================================
// SETUP: MISSING TOOTH
// ============================================================================

void triggerSetup_MissingTooth() {
  triggerState.triggerTeeth = configPage2.triggerTeeth;       // ex: 36
  triggerState.triggerMissing = configPage2.triggerMissing;   // ex: 1
  triggerState.triggerActualTeeth = triggerState.triggerTeeth - triggerState.triggerMissing;  // 35

  // Ângulo por dente (graus * 10 para precisão)
  // 360° / 36 dentes = 10° por dente
  triggerState.toothAngle = (3600 / triggerState.triggerTeeth);

  // Filtro de debounce: tempo mínimo entre dentes
  // A 10.000 RPM com 36 dentes: ~27us por dente
  // Filtro de 50us é seguro
  triggerState.triggerFilterTime = 50;

  // Total de dentes na roda (incluindo faltantes)
  triggerState.toothTotalCount = triggerState.triggerTeeth;

  // Define ISR
  currentTriggerISR = triggerPri_MissingTooth;

  DEBUG_PRINT(F("Missing Tooth: "));
  DEBUG_PRINT(triggerState.triggerTeeth);
  DEBUG_PRINT(F("-"));
  DEBUG_PRINTLN(triggerState.triggerMissing);
}

// ============================================================================
// SETUP: BASIC DISTRIBUTOR
// ============================================================================

void triggerSetup_BasicDistributor() {
  triggerState.triggerTeeth = 1;            // 1 pulso por revolução
  triggerState.triggerMissing = 0;
  triggerState.triggerActualTeeth = 1;
  triggerState.toothAngle = 3600;           // 360° por dente

  triggerState.triggerFilterTime = 500;     // 500us de filtro

  triggerState.toothTotalCount = 1;

  currentTriggerISR = triggerPri_BasicDistributor;

  DEBUG_PRINTLN(F("Basic Distributor"));
}

// ============================================================================
// ISR: MISSING TOOTH
// ============================================================================

void triggerPri_MissingTooth() {
  // CRÍTICO: código deve ser extremamente rápido!

  // Timestamp atual
  uint32_t curTime = micros();

  // Gap desde último dente
  triggerState.curGap = curTime - triggerState.toothLastToothTime;

  // Filtro de debounce
  if (triggerState.curGap < triggerState.triggerFilterTime) {
    return;  // Ignora ruído
  }

  // Incrementa contador de dentes
  triggerState.toothCurrentCount++;

  // Detecta missing tooth (gap significativamente maior)
  // Gap do missing tooth é ~2x maior que dente normal
  // Usa 1.5x como threshold para robustez
  if (triggerState.curGap > (triggerState.lastGap + (triggerState.lastGap >> 1))) {
    // Encontrou o gap!

    // Verifica se número de dentes bate (validação de sync)
    if (triggerState.toothCurrentCount >= triggerState.triggerActualTeeth) {
      // Sincronismo OK
      triggerState.hasSync = true;
      triggerState.syncLossCounter = 0;

      // Marca tempo de referência (dente #1)
      triggerState.toothOneTime = curTime;

      // Calcula tempo de revolução
      triggerState.revolutionTime = curTime - triggerState.toothLastMinusOneTime;
      triggerState.toothLastMinusOneTime = triggerState.toothOneTime;

      // Reseta contador
      triggerState.toothCurrentCount = 1;

      // Alterna revolução (para sequenciamento wasted paired)
      revolutionCounter = (revolutionCounter == 0) ? 1 : 0;

      // *** AGENDAMENTO DIRETO NA ISR - TEMPO REAL! ***
      scheduleInjectionISR();
      scheduleIgnitionISR();
    } else {
      // Número de dentes não bate, perdeu sync
      triggerState.syncLossCounter++;
      if (triggerState.syncLossCounter > 3) {
        triggerState.hasSync = false;
      }
    }
  }

  // Atualiza histórico de gaps
  triggerState.lastGap = triggerState.curGap;
  triggerState.toothLastToothTime = curTime;
}

// ============================================================================
// ISR: BASIC DISTRIBUTOR
// ============================================================================

void triggerPri_BasicDistributor() {
  uint32_t curTime = micros();

  triggerState.curGap = curTime - triggerState.toothLastToothTime;

  // Filtro de debounce
  if (triggerState.curGap < triggerState.triggerFilterTime) {
    return;
  }

  // A cada pulso = 1 revolução completa
  triggerState.hasSync = true;
  triggerState.toothCurrentCount = 1;
  triggerState.toothOneTime = curTime;

  // Tempo de revolução
  triggerState.revolutionTime = triggerState.curGap;

  // Atualiza histórico
  triggerState.toothLastToothTime = curTime;
  triggerState.toothLastMinusOneTime = curTime;

  // Alterna revolução
  revolutionCounter = (revolutionCounter == 0) ? 1 : 0;

  // *** AGENDAMENTO DIRETO NA ISR - TEMPO REAL! ***
  scheduleInjectionISR();
  scheduleIgnitionISR();
}

// ============================================================================
// CÁLCULO DE RPM
// ============================================================================

void calculateRPM() {
  // Evita cálculo se não tiver sync
  if (!triggerState.hasSync) {
    triggerState.RPM = 0;
    currentStatus.RPM = 0;
    currentStatus.RPMdiv100 = 0;
    currentStatus.hasSync = false;
    return;
  }

  // RPM = 60.000.000 / revolutionTime (microsegundos)
  // Mas para 4-stroke, revolução = 720°, então RPM = 30.000.000 / revolutionTime
  // Para 2-stroke, RPM = 60.000.000 / revolutionTime

  if (triggerState.revolutionTime > 0) {
    // Assume 4-stroke (2 revoluções = 1 ciclo completo)
    // Mas roda fônica gira 1x por revolução do virabrequim
    // Então RPM = 60.000.000 / revolutionTime
    uint32_t rpm = MICROS_PER_MIN / triggerState.revolutionTime;

    // Para missing tooth, revolutionTime é 1 volta completa (360°)
    // RPM correto
    triggerState.RPM = (uint16_t)rpm;

    // Atualiza status global
    noInterrupts();
    currentStatus.RPM = triggerState.RPM;
    currentStatus.RPMdiv100 = triggerState.RPM / 100;
    currentStatus.hasSync = true;
    interrupts();
  } else {
    triggerState.RPM = 0;
    currentStatus.RPM = 0;
    currentStatus.RPMdiv100 = 0;
  }
}

// ============================================================================
// VERIFICAÇÃO DE PERDA DE SYNC
// ============================================================================

void checkSyncLoss() {
  // Se não recebeu dentes por muito tempo, perde sync
  uint32_t timeSinceLastTooth = micros() - triggerState.toothLastToothTime;

  if (timeSinceLastTooth > (SYNC_TIMEOUT * 1000UL)) {
    // Timeout!
    noInterrupts();
    triggerState.hasSync = false;
    currentStatus.hasSync = false;
    currentStatus.RPM = 0;
    currentStatus.RPMdiv100 = 0;
    interrupts();
  }
}

// ============================================================================
// CONVERSÕES ÂNGULO <-> TEMPO
// ============================================================================

uint32_t angleToTime(uint16_t angle) {
  // Tempo = (ângulo / 360) * revolutionTime
  if (triggerState.revolutionTime == 0) return 0;

  return ((uint32_t)angle * triggerState.revolutionTime) / 360UL;
}

uint16_t timeToAngle(uint32_t time) {
  // Ângulo = (tempo / revolutionTime) * 360
  if (triggerState.revolutionTime == 0) return 0;

  return (uint16_t)(((uint32_t)time * 360UL) / triggerState.revolutionTime);
}

uint16_t getCrankAngle() {
  if (!triggerState.hasSync) return 0;

  // Tempo desde dente #1
  uint32_t timeSinceToothOne = micros() - triggerState.toothOneTime;

  // Converte para ângulo
  uint16_t angle = timeToAngle(timeSinceToothOne);

  // Normaliza para 0-359
  if (angle >= 360) {
    angle = angle % 360;
  }

  return angle;
}

// ============================================================================
// GERENCIAMENTO DE INTERRUPÇÕES
// ============================================================================

void attachTriggerInterrupt() {
  // Configura pino como entrada
  pinMode(PIN_TRIGGER_PRIMARY, INPUT_PULLUP);

  // Anexa interrupção INT0 (pino D2 no Uno)
  // Detecta borda de subida (padrão)
  attachInterrupt(digitalPinToInterrupt(PIN_TRIGGER_PRIMARY), []() {
    if (currentTriggerISR != nullptr) {
      currentTriggerISR();
    }
  }, RISING);
}

void detachTriggerInterrupt() {
  detachInterrupt(digitalPinToInterrupt(PIN_TRIGGER_PRIMARY));
}

void resetTriggerState() {
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
  currentStatus.RPMdiv100 = 0;

  revolutionCounter = 0;

  interrupts();
}
