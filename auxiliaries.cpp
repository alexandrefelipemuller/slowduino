/**
 * @file auxiliaries.cpp
 * @brief Implementação de controle de funções auxiliares
 */

#include "auxiliaries.h"

// Variáveis estáticas para controle de estado
static uint32_t lastFuelPumpActivity = 0;
static uint32_t fuelPumpPrimeStart = 0;
static bool isPriming = false;

// ============================================================================
// INICIALIZAÇÃO
// ============================================================================

void auxiliariesInit() {
  // Configura pinos como saída
  pinMode(PIN_FAN, OUTPUT);
  pinMode(PIN_IDLE_VALVE, OUTPUT);
  pinMode(PIN_FUEL_PUMP, OUTPUT);

  // Estado inicial (tudo desligado)
  FAN_OFF();
  FUEL_PUMP_OFF();
  analogWrite(PIN_IDLE_VALVE, 0);

  currentStatus.fanActive = false;
  currentStatus.fuelPumpActive = false;
  currentStatus.idleValveDuty = 0;

  // Inicia priming da bomba
  FUEL_PUMP_ON();
  fuelPumpPrimeStart = millis();
  isPriming = true;

  DEBUG_PRINTLN(F("Auxiliares inicializados"));
  DEBUG_PRINTLN(F("Bomba: priming 2s"));
}

// ============================================================================
// VENTOINHA DO RADIADOR
// ============================================================================

void fanControl() {
  // Controle simples com histerese
  if (currentStatus.coolant >= FAN_ON_TEMP) {
    if (!currentStatus.fanActive) {
      FAN_ON();
      DEBUG_PRINT(F("Fan ON @ "));
      DEBUG_PRINT(currentStatus.coolant);
      DEBUG_PRINTLN(F("C"));
    }
  } else if (currentStatus.coolant <= FAN_OFF_TEMP) {
    if (currentStatus.fanActive) {
      FAN_OFF();
      DEBUG_PRINT(F("Fan OFF @ "));
      DEBUG_PRINT(currentStatus.coolant);
      DEBUG_PRINTLN(F("C"));
    }
  }
  // Entre FAN_OFF_TEMP e FAN_ON_TEMP: mantém estado atual (histerese)
}

// ============================================================================
// BOMBA DE COMBUSTÍVEL
// ============================================================================

void fuelPumpControl() {
  uint32_t now = millis();

  // Fase 1: Priming inicial (primeiros 2 segundos)
  if (isPriming) {
    if ((now - fuelPumpPrimeStart) >= FUEL_PUMP_PRIME_MS) {
      isPriming = false;
      DEBUG_PRINTLN(F("Bomba: priming concluído"));
    } else {
      FUEL_PUMP_ON();
      return;
    }
  }

  // Fase 2: Controle baseado em RPM
  if (currentStatus.RPM > 0 || BIT_CHECK(currentStatus.engineStatus, ENGINE_CRANK)) {
    // Motor girando -> liga bomba
    FUEL_PUMP_ON();
    lastFuelPumpActivity = now;
  } else {
    // Motor parado -> aguarda timeout de 1 segundo
    if ((now - lastFuelPumpActivity) >= 1000) {
      FUEL_PUMP_OFF();
    }
  }
}

// ============================================================================
// VÁLVULA DE MARCHA LENTA (IAC)
// ============================================================================

void idleControl() {
  // Só atua em marcha lenta (baixo TPS e motor aquecido)
  if (currentStatus.TPS > 5 || currentStatus.coolant < 60) {
    // Não está em idle ou motor frio -> mantém posição
    return;
  }

  // Calcula erro de RPM
  int16_t rpmError = IAC_IDLE_RPM - (int16_t)currentStatus.RPM;

  // Banda morta (deadband) - evita oscilação
  if (abs(rpmError) < IAC_RPM_DEADBAND) {
    return; // RPM dentro da faixa aceitável
  }

  // Ajusta duty cycle baseado no erro
  if (rpmError > 0) {
    // RPM abaixo do alvo -> aumenta abertura
    currentStatus.idleValveDuty += IAC_STEP_SIZE;
    if (currentStatus.idleValveDuty > IAC_MAX_DUTY) {
      currentStatus.idleValveDuty = IAC_MAX_DUTY;
    }
  } else {
    // RPM acima do alvo -> diminui abertura
    if (currentStatus.idleValveDuty >= IAC_STEP_SIZE) {
      currentStatus.idleValveDuty -= IAC_STEP_SIZE;
    } else {
      currentStatus.idleValveDuty = IAC_MIN_DUTY;
    }
  }

  // Aplica PWM (0-255 do analogWrite = 0-100% duty)
  uint8_t pwmValue = map(currentStatus.idleValveDuty, 0, 100, 0, 255);
  analogWrite(PIN_IDLE_VALVE, pwmValue);
}
