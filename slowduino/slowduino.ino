/**
 * @file slowduino.ino
 * @brief Loop principal do Slowduino
 *
 * ECU minimalista para ATmega328p (Arduino Uno/Nano)
 * Baseado na Speeduino, otimizado para 32KB Flash / 2KB RAM
 *
 * ARQUITETURA DE AGENDAMENTO:
 * ---------------------------
 * IGNIÇÃO: Compare Match (Timer1) - Alta precisão (±5µs)
 *   - OCR1A: Ignition Channels 1
 *   - OCR1B: Ignition Channel 2
 *
 * INJEÇÃO: Polling no loop - Precisão relaxada (±100µs, ~2-3% do PW)
 *   - processInjectorPolling() executado a cada iteração
 *   - Suficiente para wasted paired (semi-sequential)
 *
 * RAZÃO: Arduino Uno tem apenas 2 compare registers (OCR1A, OCR1B)
 *        Não há hardware suficiente para agendar 6+ eventos simultâneos
 *
 * @author Alexandre F M SOUZA
 * @version 0.2.1
 * @date 2025
 */

#include "globals.h"
#include "config.h"
#include "storage.h"
#include "sensors.h"
#include "tables.h"
#include "decoders.h"
#include "fuel.h"
#include "ignition.h"
#include "scheduler.h"
#include "comms.h"
#include "auxiliaries.h"
#include "protections.h"

// ============================================================================
// VARIÁVEIS DO LOOP
// ============================================================================

// Timers para controle de frequência
static uint32_t lastLoop1ms = 0;
static uint32_t lastLoop4Hz = 0;
static uint32_t lastLoop15Hz = 0;
static uint32_t lastLoop30Hz = 0;

// Flags e controle de priming
static bool primedFuel = false;

// ============================================================================
// SETUP
// ============================================================================

void setup() {
  // Inicializa serial
  Serial.begin(SERIAL_BAUD);
  DEBUG_PRINTLN(F(""));
  DEBUG_PRINTLN(F("========================================"));
  DEBUG_PRINTLN(F("  SLOWDUINO - Super Lowcost Speeduino"));
  DEBUG_PRINTLN(F("  Version: " SLOWDUINO_VERSION));
  DEBUG_PRINTLN(F("========================================"));

  // Inicializa subsistemas
  DEBUG_PRINTLN(F("Inicializando subsistemas..."));

  // 1. Tabelas (inicializa flags)
  DEBUG_PRINT(F("- Tabelas... "));
  initTables();
  DEBUG_PRINTLN(F("OK"));

  // 2. Storage (carrega config da EEPROM)
  DEBUG_PRINT(F("- Storage... "));
  storageInit();
  DEBUG_PRINTLN(F("OK"));

  // 3. Sensores
  DEBUG_PRINT(F("- Sensores... "));
  sensorsInit();
  DEBUG_PRINTLN(F("OK"));

  // 4. Scheduler (Timer1 + pinos de saída)
  DEBUG_PRINT(F("- Scheduler... "));
  schedulerInit();
  DEBUG_PRINTLN(F("OK"));

  // 5. Trigger (decoder + ISR)
  DEBUG_PRINT(F("- Trigger... "));
  triggerInit();
  DEBUG_PRINTLN(F("OK"));

  // 6. Comunicação (já inicializado Serial no início)
  DEBUG_PRINT(F("- Comunicação... "));
  commsInit();
  DEBUG_PRINTLN(F("OK"));

  // 7. Auxiliares (ventoinha, IAC, bomba)
  DEBUG_PRINT(F("- Auxiliares... "));
  auxiliariesInit();
  DEBUG_PRINTLN(F("OK"));

  // 8. Inicializa status
  currentStatus.secl = 0;
  currentStatus.runSecs = 0;
  currentStatus.afrTarget = 100;

  // 9. Estado inicial do motor
  currentStatus.engineStatus = 0;
  BIT_CLEAR(currentStatus.engineStatus, ENGINE_CRANK);
  BIT_CLEAR(currentStatus.engineStatus, ENGINE_RUN);
  BIT_SET(currentStatus.engineStatus, ENGINE_WARMUP);  // Assume frio no boot

  DEBUG_PRINTLN(F(""));
  DEBUG_PRINTLN(F("Sistema pronto!"));
  DEBUG_PRINT(F("Cilindros: "));
  DEBUG_PRINTLN(configPage1.nCylinders);
  DEBUG_PRINT(F("Trigger: "));
  if (configPage2.triggerPattern == TRIGGER_MISSING_TOOTH) {
    DEBUG_PRINT(configPage2.triggerTeeth);
    DEBUG_PRINT(F("-"));
    DEBUG_PRINTLN(configPage2.triggerMissing);
  } else {
    DEBUG_PRINTLN(F("Basic Distributor"));
  }
  DEBUG_PRINTLN(F(""));
  DEBUG_PRINTLN(F("Aguardando sincronismo..."));
  DEBUG_PRINTLN(F("========================================"));

  // Marca tempo inicial
  lastLoop1ms = millis();
  lastLoop4Hz = millis();
  lastLoop15Hz = millis();
  lastLoop30Hz = millis();
}

// ============================================================================
// LOOP PRINCIPAL
// ============================================================================

void loop() {
  uint32_t now = millis();

  // ------------------------------------------------------------------------
  // POLLING DE INJETORES - MÁXIMA PRIORIDADE (DEVE SER PRIMEIRO!)
  // ------------------------------------------------------------------------
  // CRÍTICO: Processa abertura/fechamento de injetores via polling
  // Precisão: ±100µs (tempo de loop típico)
  processInjectorPolling();

  // ------------------------------------------------------------------------
  // COMUNICAÇÃO SERIAL - ALTA PRIORIDADE
  // ------------------------------------------------------------------------
  commsProcess();

  // ------------------------------------------------------------------------
  // Loop 1ms - Contador de tempo
  // ------------------------------------------------------------------------
  if ((now - lastLoop1ms) >= 1) {
    lastLoop1ms = now;

    // Incrementa contador de segundos
    static uint16_t msCounter = 0;
    msCounter++;
    if (msCounter >= 1000) {
      msCounter = 0;
      currentStatus.secl++;

      if (currentStatus.RPM > 0) {
        currentStatus.runSecs++;
      }
    }
  }

  // ------------------------------------------------------------------------
  // Loop 30Hz (~33ms) - Sensores médios
  // ------------------------------------------------------------------------
  if ((now - lastLoop30Hz) >= 33) {
    lastLoop30Hz = now;

    readTPS();
    readMAP();
  }

  // ------------------------------------------------------------------------
  // Loop 15Hz (~67ms) - RPM e estado
  // ------------------------------------------------------------------------
  if ((now - lastLoop15Hz) >= 67) {
    lastLoop15Hz = now;

    // Calcula RPM
    calculateRPM();

    // Verifica perda de sincronismo
    checkSyncLoss();

    // Atualiza estado do motor
    updateEngineStatus();

    // Marcha lenta: roda aqui e não no bloco de 4Hz porque precisa da mesma
    // cadência do RPM que ele persegue (a 4Hz o controle era mais lento que a
    // própria atualização da variável de processo).
    idleControl();
  }

  // ------------------------------------------------------------------------
  // Loop 4Hz (250ms) - Sensores lentos e auxiliares
  // ------------------------------------------------------------------------
  if ((now - lastLoop4Hz) >= 250) {
    lastLoop4Hz = now;

    readCLT();
    readIAT();
    readO2();
    readBattery();
    readOilPressure();
    readFuelPressure();

    // Controles auxiliares
    fanControl();
    fuelPumpControl();
  }

  // ------------------------------------------------------------------------
  // Priming pulse (ao obter primeiro sync)
  // ------------------------------------------------------------------------
  // Agendado pela MESMA máquina de estados de polling usada pela injeção
  // normal (em vez de digitalWrite direto): evita que o prime e uma injeção
  // real disputem o mesmo pino sem coordenação (um fechando/cortando o pulso
  // do outro logo na primeira sincronização do motor).
  if (!primedFuel && currentStatus.hasSync && currentStatus.RPM > 0) {
    if (configPage1.primePulse > 0) {
      uint16_t primeDuration = (uint16_t)((uint32_t)configPage1.primePulse * 100UL); // ms*10 -> us
      scheduleInjectorPolling(&injector1Polling, 0, primeDuration);
      scheduleInjectorPolling(&injector2Polling, 0, primeDuration);
    }
    primedFuel = true;
  }

  // ------------------------------------------------------------------------
  // Lógica de injeção/ignição (depende de sync)
  // ------------------------------------------------------------------------
  if (currentStatus.hasSync && currentStatus.RPM > 0) {

    // Calcula fora da seção crítica (cálculo pode ser custoso) e só então
    // publica os valores. PW1/PW2/dwell são uint16_t: a ISR do trigger lê
    // esses campos diretamente (scheduleInjectionISR/scheduleIgnitionISR) e,
    // em AVR, uma escrita de 16 bits não é atômica - sem essa proteção a ISR
    // podia ler um valor "torto" (metade byte antigo, metade novo) caso
    // disparasse no meio da atribuição.
    uint16_t newPW1 = calculateInjection();
    int8_t newAdvance = calculateAdvance();
    uint16_t newDwell = calculateDwell();

    noInterrupts();
    currentStatus.PW1 = newPW1;
    currentStatus.PW2 = newPW1;  // Wasted paired = mesmo PW
    currentStatus.advance = newAdvance;
    currentStatus.dwell = newDwell;
    interrupts();

    // Agendamento acontece automaticamente via ISR no trigger!
  }

  protectionProcess();

  // ------------------------------------------------------------------------
  // Debug serial (a cada 1 segundo)
  // ------------------------------------------------------------------------
  #ifdef DEBUG_ENABLED
  static uint32_t lastDebug = 0;
  if ((now - lastDebug) >= 1000) {
    lastDebug = now;

    Serial.print(F("RPM: "));
    Serial.print(currentStatus.RPM);
    Serial.print(F(" | Sync: "));
    Serial.print(currentStatus.hasSync ? F("OK") : F("NO"));
    Serial.print(F(" | Dentes: "));
    Serial.print(triggerState.toothCurrentCount);
    Serial.print(F(" | LastGap: "));
    Serial.print(triggerState.lastGap);
    Serial.print(F("us | RevTime: "));
    Serial.print(triggerState.revolutionTime);
    Serial.print(F("us | MAP: "));
    Serial.print(currentStatus.MAP);
    Serial.print(F(" kPa | TPS: "));
    Serial.print(currentStatus.TPS);
    Serial.print(F("% | CLT: "));
    Serial.print(currentStatus.coolant);
    Serial.print(F("C | PW: "));
    Serial.print(currentStatus.PW1);
    Serial.print(F("us | Adv: "));
    Serial.print(currentStatus.advance);
    Serial.println(F("deg"));
  }
  #endif
}
