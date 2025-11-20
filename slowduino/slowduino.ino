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
 * @author Claude + User
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
static uint32_t primeStartTime = 0;

// ============================================================================
// SETUP
// ============================================================================

void setup() {
  // Inicializa serial
  Serial.begin(SERIAL_BAUD);
  Serial.println(F(""));
  Serial.println(F("========================================"));
  Serial.println(F("  SLOWDUINO - Super Lowcost Speeduino"));
  Serial.println(F("  Version: " SLOWDUINO_VERSION));
  Serial.println(F("========================================"));

  // Inicializa subsistemas
  Serial.println(F("Inicializando subsistemas..."));

  // 1. Tabelas (inicializa flags)
  Serial.print(F("- Tabelas... "));
  initTables();
  Serial.println(F("OK"));

  // 2. Storage (carrega config da EEPROM)
  Serial.print(F("- Storage... "));
  storageInit();
  Serial.println(F("OK"));

  // 3. Sensores
  Serial.print(F("- Sensores... "));
  sensorsInit();
  Serial.println(F("OK"));

  // 4. Scheduler (Timer1 + pinos de saída)
  Serial.print(F("- Scheduler... "));
  schedulerInit();
  Serial.println(F("OK"));

  // 5. Trigger (decoder + ISR)
  Serial.print(F("- Trigger... "));
  triggerInit();
  Serial.println(F("OK"));

  // 6. Comunicação (já inicializado Serial no início)
  Serial.print(F("- Comunicação... "));
  commsInit();
  Serial.println(F("OK"));

  // 7. Auxiliares (ventoinha, IAC, bomba)
  Serial.print(F("- Auxiliares... "));
  auxiliariesInit();
  Serial.println(F("OK"));

  // 8. Inicializa status
  currentStatus.secl = 0;
  currentStatus.runSecs = 0;
  currentStatus.loopCount = 0;
  currentStatus.ignitionCount = 0;
  currentStatus.egoCorrection = 100;
  currentStatus.afrTarget = 100;

  // 9. Estado inicial do motor
  currentStatus.engineStatus = 0;
  BIT_CLEAR(currentStatus.engineStatus, ENGINE_CRANK);
  BIT_CLEAR(currentStatus.engineStatus, ENGINE_RUN);
  BIT_SET(currentStatus.engineStatus, ENGINE_WARMUP);  // Assume frio no boot

  Serial.println(F(""));
  Serial.println(F("Sistema pronto!"));
  Serial.print(F("Cilindros: "));
  Serial.println(configPage1.nCylinders);
  Serial.print(F("Trigger: "));
  if (configPage2.triggerPattern == TRIGGER_MISSING_TOOTH) {
    Serial.print(configPage2.triggerTeeth);
    Serial.print(F("-"));
    Serial.println(configPage2.triggerMissing);
  } else {
    Serial.println(F("Basic Distributor"));
  }
  Serial.println(F(""));
  Serial.println(F("Aguardando sincronismo..."));
  Serial.println(F("========================================"));

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
  currentStatus.loopCount++;

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
    idleControl();
  }

  // ------------------------------------------------------------------------
  // Priming pulse (ao obter primeiro sync)
  // ------------------------------------------------------------------------
  if (!primedFuel && currentStatus.hasSync && currentStatus.RPM > 0) {
    // Iniciar priming pulse
    if (configPage1.primePulse > 0) {
      openInjector1();
      openInjector2();
      primeStartTime = micros();
    }
    primedFuel = true;
  }

  // Fechar injetores após priming (não-bloqueante)
  if (primedFuel && primeStartTime > 0) {
    uint32_t primeDuration = (uint32_t)configPage1.primePulse * 100UL; // ms*10 -> us
    if ((micros() - primeStartTime) >= primeDuration) {
      closeInjector1();
      closeInjector2();
      primeStartTime = 0; // Marca como concluído
    }
  }

  // ------------------------------------------------------------------------
  // Lógica de injeção/ignição (depende de sync)
  // ------------------------------------------------------------------------
  if (currentStatus.hasSync && currentStatus.RPM > 0) {

    // ---- Calcula injeção ----
    currentStatus.PW1 = calculateInjection();
    currentStatus.PW2 = currentStatus.PW1;  // Wasted paired = mesmo PW

    // ---- Calcula ignição ----
    currentStatus.advance = calculateAdvance();
    currentStatus.dwell = calculateDwell();

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

  // Pequeno delay para não saturar CPU (pode remover em produção)
  delayMicroseconds(100);
}
