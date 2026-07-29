/**
 * @file auxiliaries.cpp
 * @brief Implementação de controle de funções auxiliares
 */

#include "auxiliaries.h"
#include "tables.h"

// Variáveis estáticas para controle de estado
static uint32_t lastFuelPumpActivity = 0;
static uint32_t fuelPumpPrimeStart = 0;
static bool isPriming = false;

// ----------------------------------------------------------------------------
// Estado do PWM do IAC (compartilhado com a ISR do Timer2)
// ----------------------------------------------------------------------------
// Todos uint8_t: no AVR a leitura/escrita de 8 bits é atômica, então o loop
// principal pode atualizar o alvo sem desabilitar interrupções.
static volatile uint8_t idlePwmCount = 0;        // Tick corrente dentro do período
static volatile uint8_t idlePwmPeriodTicks = 25; // Ticks por período de PWM
static volatile uint8_t idlePwmTargetTicks = 0;  // Tick em que o pino vai para LOW

// Estado do controlador
// BRANCH ms1: int32_t -> int16_t. O valor JÁ CLAMPADO cabe à vontade em
// int16_t (IDLE_INTEGRAL_LIMIT=25600, dentro de +-32767) - mas a soma
// idleKI*err10 antes do clamp pode passar de 200000 num único passo, então
// a conta em si continua em int32_t (variável local em idleControl()) e só
// o resultado já clampado é gravado aqui. Ver idleControl().
static int16_t idleIntegral = 0;     // Acumulador da integral (escala 1/256)
static uint16_t idleLastRpm = 0;     // RPM da chamada anterior (termo derivativo)
static uint8_t idleTaperTotal = 0;   // Duração total do taper, em chamadas
static uint8_t idleLastFreq = 0;     // idleFreq já aplicado (detecta retune)

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

  currentStatus.fanActive = false;
  currentStatus.fuelPumpActive = false;
  currentStatus.idleValveDuty = 0;
  currentStatus.CLIdleTarget = 0;
  currentStatus.idleTaper = 0;

  // PWM do IAC via Timer2 (NUNCA analogWrite - ver board_config.h)
  idlePwmInit();

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
// VÁLVULA DE MARCHA LENTA (IAC) - CAMADA DE PWM (Timer2)
// ============================================================================

/**
 * ISR de PWM por software.
 *
 * Roda a ~4kHz e mantém um contador de ticks. O pino sobe no início do
 * período e desce ao atingir o alvo de duty. Não toca em NENHUM registrador
 * do Timer1 - é por isso que este PWM existe em vez de um analogWrite().
 *
 * Precisa ser curtíssima: usa acesso direto à porta (IDLE_PIN_HIGH/LOW), não
 * digitalWrite(), para não atrasar a ISR de ignição do Timer1.
 */
ISR(TIMER2_COMPA_vect) {
  uint8_t count = idlePwmCount + 1;

  if (count >= idlePwmPeriodTicks) {
    count = 0;
    IDLE_PIN_HIGH();
  } else if (count >= idlePwmTargetTicks) {
    IDLE_PIN_LOW();
  }

  idlePwmCount = count;
}

void idlePwmInit() {
  pinMode(PIN_IDLE_VALVE, OUTPUT);
  IDLE_PIN_LOW();

  // Timer2 em CTC: OCR2A define o período do tick.
  // Prescaler 64 @16MHz = 4us/tick de contagem; OCR2A=62 -> 63*4us = 252us
  // (~3968Hz). Timer2 está livre no projeto - Timer0 é do core (millis) e
  // Timer1 é do scheduler de ignição/injeção.
  TCCR2A = (1 << WGM21);               // CTC
  TCCR2B = (1 << CS22);                // Prescaler 64
  OCR2A  = (IDLE_PWM_TICK_DIVISOR - 1);
  TCNT2  = 0;
  TIMSK2 = 0;                          // ISR habilitada só quando necessário

  idlePwmCount = 0;
  idlePwmTargetTicks = 0;
  idlePwmSetFrequency(configPage2.idleFreq);
  idleLastFreq = configPage2.idleFreq;
  idleSetDuty(0);
}

void idlePwmSetFrequency(uint8_t freqDiv2) {
  uint16_t freqHz = (uint16_t)freqDiv2 * 2U;

  // O período em ticks precisa caber num uint8_t (leitura atômica na ISR),
  // e precisa de alguns ticks para ter resolução de duty utilizável.
  if (freqHz < IDLE_PWM_FREQ_MIN) freqHz = IDLE_PWM_FREQ_MIN;
  if (freqHz > IDLE_PWM_FREQ_MAX) freqHz = IDLE_PWM_FREQ_MAX;

  idlePwmPeriodTicks = (uint8_t)(IDLE_PWM_TICK_HZ / freqHz);
}

/**
 * Aplica um duty (0-100%) na válvula.
 *
 * Nos extremos a ISR é desligada e o pino fica estático - além de economizar
 * CPU, isso zera o custo do IAC quando o motor está em carga (duty 0).
 */
void idleSetDuty(uint8_t duty) {
  if (duty > 100) duty = 100;
  currentStatus.idleValveDuty = duty;

  if (duty == 0) {
    TIMSK2 &= ~(1 << OCIE2A);
    IDLE_PIN_LOW();
    return;
  }

  if (duty >= 100) {
    TIMSK2 &= ~(1 << OCIE2A);
    IDLE_PIN_HIGH();
    return;
  }

  uint8_t target = (uint8_t)(((uint16_t)duty * idlePwmPeriodTicks) / 100U);
  if (target == 0) target = 1;  // Garante um pulso mínimo em duty muito baixo
  idlePwmTargetTicks = target;

  // Se estávamos num extremo (ISR desligada), o contador está velho: reinicia
  // o período para o PWM começar limpo em vez de gerar um ciclo torto.
  if ((TIMSK2 & (1 << OCIE2A)) == 0) {
    idlePwmCount = 0;
    IDLE_PIN_HIGH();
    TIMSK2 |= (1 << OCIE2A);
  }
}

// ============================================================================
// VÁLVULA DE MARCHA LENTA (IAC) - CONTROLE
// ============================================================================

void idleControl() {
  if (configPage2.iacAlgorithm == IAC_ALGORITHM_NONE) {
    if (currentStatus.idleValveDuty != 0) idleSetDuty(0);
    return;
  }

  // Reaplica a frequência se o usuário mudou idleFreq pelo TunerStudio
  if (configPage2.idleFreq != idleLastFreq) {
    idlePwmSetFrequency(configPage2.idleFreq);
    idleLastFreq = configPage2.idleFreq;
  }

  int16_t clt = currentStatus.coolant;

  // Alvo de RPM por temperatura. Fica em currentStatus porque o idle advance
  // (ignition.cpp) usa o mesmo alvo - antes havia dois alvos divergentes.
  currentStatus.CLIdleTarget = (uint16_t)lookupCurveU8(
      configPage2.iacBins, configPage2.iacCLValues, 4, clt) * 10U;

  // --------------------------------------------------------------------------
  // Partida: duty fixo pela curva de cranking, sem malha fechada
  // --------------------------------------------------------------------------
  uint8_t crankDuty = lookupCurveU8(
      configPage2.iacCrankBins, configPage2.iacCrankDuty, 4, clt);

  if (BIT_CHECK(currentStatus.engineStatus, ENGINE_CRANK)) {
    // Arma o taper para a transição partida -> funcionamento.
    // idleTaperTime está em décimos de segundo e idleControl roda a 15Hz.
    uint16_t total = ((uint16_t)configPage2.idleTaperTime * 3U) / 2U;
    idleTaperTotal = (total > 255U) ? 255U : (uint8_t)total;
    currentStatus.idleTaper = idleTaperTotal;

    idleIntegral = 0;
    idleLastRpm = currentStatus.RPM;
    idleSetDuty(crankDuty);
    return;
  }

  // --------------------------------------------------------------------------
  // Open loop: duty base por temperatura (também serve de feed-forward do PID)
  // --------------------------------------------------------------------------
  uint8_t olDuty = lookupCurveU8(
      configPage2.iacBins, configPage2.iacOLPWMVal, 4, clt);

  // --------------------------------------------------------------------------
  // Taper: decai suavemente do duty de partida para o de funcionamento
  // --------------------------------------------------------------------------
  if (currentStatus.idleTaper > 0 && idleTaperTotal > 0) {
    uint8_t elapsed = idleTaperTotal - currentStatus.idleTaper;
    int16_t blended = (int16_t)crankDuty +
                      (((int16_t)olDuty - (int16_t)crankDuty) * elapsed) / idleTaperTotal;

    currentStatus.idleTaper--;
    idleIntegral = 0;               // A malha fechada só entra após o taper
    idleLastRpm = currentStatus.RPM;
    idleSetDuty((uint8_t)blended);
    return;
  }

  // --------------------------------------------------------------------------
  // Closed loop (PID inteiro sobre o duty open loop)
  // --------------------------------------------------------------------------
  if (configPage2.iacAlgorithm != IAC_ALGORITHM_PWM_OLCL) {
    idleSetDuty(olDuty);
    return;
  }

  // Fora das condições de marcha lenta a integral é zerada, senão ela satura
  // enquanto o motor está em carga e devolve um salto de duty ao voltar.
  bool inIdle = (currentStatus.TPS <= configPage2.iacTPSlimit) &&
                (currentStatus.RPM > 0) &&
                (currentStatus.RPM < (currentStatus.CLIdleTarget + IDLE_CL_RPM_WINDOW));

  if (!inIdle) {
    idleIntegral = 0;
    idleLastRpm = currentStatus.RPM;
    idleSetDuty(olDuty);
    return;
  }

  // Erro em unidades de 10 RPM: mantém a aritmética inteira em faixa
  // confortável e dá uma escala de ganho utilizável (KP=16 -> 100 RPM de erro
  // resulta em ~10% de duty).
  int16_t err10 = ((int16_t)currentStatus.CLIdleTarget - (int16_t)currentStatus.RPM) / 10;

  int32_t pTerm = ((int32_t)configPage2.idleKP * err10) / 16;

  // Derivada sobre a medição (não sobre o erro): evita chute quando o alvo
  // muda com a temperatura.
  int16_t dRpm10 = ((int16_t)currentStatus.RPM - (int16_t)idleLastRpm) / 10;
  int32_t dTerm = -((int32_t)configPage2.idleKD * dRpm10) / 16;
  idleLastRpm = currentStatus.RPM;

  // Integral com clamp: o próprio acumulador é limitado (anti-windup), então
  // saturar a saída não deixa resíduo preso.
  // A soma é feita num int32_t local: idleKI*err10 sozinho pode passar de
  // 200000 num único passo, o que estouraria o int16_t de idleIntegral
  // antes mesmo do clamp abaixo rodar. Só o resultado já dentro do limite
  // (+-25600) é gravado de volta no acumulador de 16 bits.
  int32_t idleIntegralWide = (int32_t)idleIntegral + (int32_t)configPage2.idleKI * err10;
  if (idleIntegralWide > IDLE_INTEGRAL_LIMIT)  idleIntegralWide = IDLE_INTEGRAL_LIMIT;
  if (idleIntegralWide < -IDLE_INTEGRAL_LIMIT) idleIntegralWide = -IDLE_INTEGRAL_LIMIT;
  idleIntegral = (int16_t)idleIntegralWide;
  int32_t iTerm = idleIntegral / 256;

  int32_t output = (int32_t)olDuty + pTerm + iTerm + dTerm;

  if (output < configPage2.iacCLminValue) output = configPage2.iacCLminValue;
  if (output > configPage2.iacCLmaxValue) output = configPage2.iacCLmaxValue;

  idleSetDuty((uint8_t)output);
}
