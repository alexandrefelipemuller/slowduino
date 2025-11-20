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

// Quantos pulsos por dente físico (CHANGE = 2, RISING/FALLING = 1)
static uint8_t triggerEdgesPerTooth = 2;

// Ponteiro para ISR atual (permite trocar decoder dinamicamente)
typedef void (*TriggerISR)(void);
volatile TriggerISR currentTriggerISR = nullptr;

// Controle de sequenciamento
volatile uint8_t revolutionCounter = 0;  // 0 ou 1 (para alternar cilindros)

// Ângulos de evento
// NOTA: Injeção precisa começar CEDO o suficiente para terminar antes do próximo gap!
// A 1000 RPM, 1 revolução = 30ms. PW típico = 8ms.
// Se começar a 355°, termina a 355° + (8ms/30ms)*360° = 355° + 96° = 451° (= 91° da próxima rev!)
// SOLUÇÃO: Começar mais cedo, ex: 270° (90° BTDC)
#define INJECTION_ANGLE 270   // 90° BTDC (garante término antes do TDC)

// ============================================================================
// FUNÇÕES INLINE PARA AGENDAMENTO RÁPIDO NA ISR
// ============================================================================

// Agenda injeção VIA POLLING - CHAMADO DIRETAMENTE DA ISR
inline void scheduleInjectionISR() __attribute__((always_inline));
inline void scheduleInjectionISR() {
  if (triggerState.revolutionTime == 0) return;

  // Calcula tempo até ângulo de injeção
  uint32_t timeToInjection = ((uint32_t)INJECTION_ANGLE * triggerState.revolutionTime) / 360UL;

  // Obtém PW (calculado no loop principal)
  uint16_t pw1 = currentStatus.PW1;
  uint16_t pw2 = currentStatus.PW2;

  // Valida PW
  if (pw1 < INJ_MIN_PW || pw1 > INJ_MAX_PW) pw1 = INJ_MIN_PW;
  if (pw2 < INJ_MIN_PW || pw2 > INJ_MAX_PW) pw2 = INJ_MIN_PW;

  // Agenda VIA POLLING (não usa compare match)
  if (revolutionCounter == 0) {
    // Primeira revolução: banco 1
    scheduleInjectorPolling(&injector1Polling, timeToInjection, pw1);
    // Canal 3 fica livre para estágio auxiliar (boost, metanol, etc.) - não agendado automaticamente
  } else {
    // Segunda revolução: banco 2
    scheduleInjectorPolling(&injector2Polling, timeToInjection, pw2);
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

  // PROTEÇÃO: Limita dwell a no máximo 50% da revolução (180°)
  if (dwellAngle > 180) {
    dwellAngle = 180;
    // Recalcula dwellTime baseado no ângulo limitado
    dwellTime = (180UL * triggerState.revolutionTime) / 360UL;
  }

  // Ângulo de faísca (advance é BTDC, então 360 - advance)
  // Ex: 15° BTDC = 345° ATDC
  uint16_t sparkAngle = (advance > 0) ? (360 - advance) : 360;

  // Ângulo de início do dwell (antes da faísca)
  // PROTEÇÃO: Garante que dwellStartAngle seja sempre válido
  uint16_t dwellStartAngle;
  if (sparkAngle > dwellAngle) {
    dwellStartAngle = sparkAngle - dwellAngle;
  } else {
    // Dwell muito longo para este avanço, inicia mais cedo
    dwellStartAngle = 0;
    // Ajusta dwell para caber
    dwellAngle = sparkAngle;
    dwellTime = (dwellAngle * triggerState.revolutionTime) / 360UL;
  }

  // Calcula tempo até início do dwell
  uint32_t timeToDwell = ((uint32_t)dwellStartAngle * triggerState.revolutionTime) / 360UL;

  if (revolutionCounter == 0) {
    // Primeira revolução: bobina 1
    setIgnitionSchedule(&ignitionSchedule1, timeToDwell, dwellTime, 1);

  } else {
    // Segunda revolução: bobina 2
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

  // Filtro de debounce mínimo (50us absoluto)
  if (triggerState.curGap < 50) {
    return;  // Ignora ruído
  }

  // Atualiza tempo
  triggerState.toothLastToothTime = curTime;

  // ESTRATÉGIA SIMPLIFICADA: Com CHANGE, temos HIGH e LOW
  // HIGH->LOW: gap ~500us (meio dente)
  // LOW->HIGH do próximo dente: gap ~500us (outro meio)
  // Gap entre dentes COMPLETOS: ~1000us
  // Missing tooth gap: ~2000us

  // Aceita TODOS os pulsos, mas detecta gap pelo tamanho absoluto
  triggerState.toothCurrentCount++;

  // Detecta missing tooth com threshold DINÂMICO baseado no último dente
  // Gap normal ≈ gap anterior; missing tooth precisa ser pelo menos 1.5x maior
  uint32_t baseGap = (triggerState.lastGap > 0) ? triggerState.lastGap : triggerState.curGap;
  uint32_t dynamicThreshold = baseGap + (baseGap >> 1);  // 1.5x
  bool isGap = (triggerState.curGap > dynamicThreshold);

  if (isGap) {
    // Encontrou o gap!

    // Com CHANGE, esperamos ~70 pulsos (35 dentes × 2 bordas)
    // Mas o gap também gera 2 pulsos, então ~72 total
    // Validação flexível: entre 60-80 pulsos
    uint16_t expectedPulses = triggerState.triggerActualTeeth * triggerEdgesPerTooth;

    if (triggerState.toothCurrentCount >= (expectedPulses - 10) &&
        triggerState.toothCurrentCount <= (expectedPulses + 10)) {

      // Sincronismo OK
      triggerState.hasSync = true;
      triggerState.syncLossCounter = 0;

      // Marca tempo de referência (dente #1)
      triggerState.toothOneTime = curTime;

      // Calcula tempo de revolução (desde último gap)
      if (triggerState.toothLastMinusOneTime > 0) {
        triggerState.revolutionTime = curTime - triggerState.toothLastMinusOneTime;
      }
      triggerState.toothLastMinusOneTime = curTime;

      // Reseta contador
      triggerState.toothCurrentCount = 1;

      // Alterna revolução (para sequenciamento wasted paired)
      revolutionCounter = (revolutionCounter == 0) ? 1 : 0;

      // *** AGENDAMENTO DIRETO NA ISR - TEMPO REAL! ***
      if (triggerState.revolutionTime > 0) {
        scheduleInjectionISR();
        scheduleIgnitionISR();
      }
    } else {
      // Número de pulsos não bate - tenta resincronizar
      triggerState.toothCurrentCount = 1;
      triggerState.syncLossCounter++;

      if (triggerState.syncLossCounter > 10) {
        triggerState.hasSync = false;
      }
    }
  }

  // Atualiza lastGap para referência
  triggerState.lastGap = triggerState.curGap;
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
  // revolutionTime = tempo de uma volta completa (360°)
  if (triggerState.revolutionTime > 0) {
    // Calcula RPM com proteção de overflow
    // 60.000.000us = 1 minuto
    uint32_t rpm = MICROS_PER_MIN / triggerState.revolutionTime;

    // Limita range razoável (evita valores absurdos)
    if (rpm > 15000) rpm = 15000;  // Máximo 15k RPM
    if (rpm < 100) rpm = 0;        // Abaixo de 100 RPM considera parado

    triggerState.RPM = (uint16_t)rpm;

    // Atualiza status global (thread-safe)
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
  if (!triggerState.hasSync || triggerState.revolutionTime == 0) return 0;

  // Tempo desde dente #1
  uint32_t timeSinceToothOne = micros() - triggerState.toothOneTime;

  // Limita ao tempo de revolução para evitar overflow e operação módulo
  // (entre revoluções o tempo pode exceder revolutionTime)
  if (timeSinceToothOne >= triggerState.revolutionTime) {
    timeSinceToothOne = triggerState.revolutionTime - 1;
  }

  // Converte para ângulo (0-359) - agora garantido sem necessidade de módulo
  uint16_t angle = ((uint32_t)timeSinceToothOne * 360UL) / triggerState.revolutionTime;

  return angle;
}

// ============================================================================
// GERENCIAMENTO DE INTERRUPÇÕES
// ============================================================================

void attachTriggerInterrupt() {
  // Configura pino como entrada com pullup
  pinMode(PIN_TRIGGER_PRIMARY, INPUT_PULLUP);

  uint8_t edgeConfig = configPage2.triggerEdge;
  uint8_t interruptMode;
  switch (edgeConfig) {
    case TRIGGER_EDGE_RISING:
      interruptMode = RISING;
      triggerEdgesPerTooth = 1;
      break;
    case TRIGGER_EDGE_FALLING:
      interruptMode = FALLING;
      triggerEdgesPerTooth = 1;
      break;
    default:
      interruptMode = CHANGE;
      triggerEdgesPerTooth = 2;
      break;
  }

  // Anexa interrupção INT0 (pino D2 no Uno/Nano - PIN_TRIGGER_PRIMARY)
  // Pode ser RISING, FALLING ou CHANGE (ambas as bordas)
  // NOTA: Com CHANGE, cada dente físico gera 2 pulsos!
  // Lambda chama ISR atual dinamicamente (permite trocar decoder em runtime)
  attachInterrupt(digitalPinToInterrupt(PIN_TRIGGER_PRIMARY), []() {
    if (currentTriggerISR != nullptr) {
      currentTriggerISR();
    }
  }, interruptMode);
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
