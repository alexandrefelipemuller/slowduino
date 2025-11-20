/**
 * @file sensors.cpp
 * @brief Implementação da leitura de sensores
 */

#include "sensors.h"

// Variáveis estáticas para cálculo de TPSdot
static uint32_t lastTPSReadTime = 0;

static uint8_t convertNarrowbandToScale(uint16_t adc) {
  uint16_t millivolts = adcToMillivolts(adc);

  if (millivolts > 1000) {
    millivolts = 1000;
  }

  // Escala 0-1000mV -> 0-200 (100 = ~0.5V, próximo a lambda 1.0)
  uint32_t scaled = (uint32_t)millivolts * 200UL;
  scaled /= 1000UL;

  if (scaled > 200) {
    scaled = 200;
  }

  return (uint8_t)scaled;
}

// ============================================================================
// INICIALIZAÇÃO
// ============================================================================

void sensorsInit() {
  // Configura pinos como entrada
  pinMode(PIN_MAP, INPUT);
  pinMode(PIN_TPS, INPUT);
  pinMode(PIN_CLT, INPUT);
  pinMode(PIN_IAT, INPUT);
  pinMode(PIN_O2, INPUT);
  pinMode(PIN_BAT, INPUT);
  pinMode(PIN_OIL_PRESSURE, INPUT);
  pinMode(PIN_FUEL_PRESSURE, INPUT);

  // Realiza leituras iniciais (sem filtro)
  currentStatus.mapADC = analogRead(PIN_MAP);
  currentStatus.tpsADC = analogRead(PIN_TPS);
  currentStatus.cltADC = analogRead(PIN_CLT);
  currentStatus.iatADC = analogRead(PIN_IAT);
  currentStatus.o2ADC = analogRead(PIN_O2);
  currentStatus.batADC = analogRead(PIN_BAT);
  currentStatus.oilPressADC = analogRead(PIN_OIL_PRESSURE);
  currentStatus.fuelPressADC = analogRead(PIN_FUEL_PRESSURE);

  // Converte valores iniciais
  currentStatus.MAP = fastMap(currentStatus.mapADC, 0, 1023, configPage1.mapMin, configPage1.mapMax);
  currentStatus.TPS = fastMap(currentStatus.tpsADC, adc8to10(configPage1.tpsMin), adc8to10(configPage1.tpsMax), 0, 100);
  currentStatus.coolant = ntcToCelsius(currentStatus.cltADC);
  currentStatus.IAT = ntcToCelsius(currentStatus.iatADC);
  currentStatus.O2 = convertNarrowbandToScale(currentStatus.o2ADC);
  currentStatus.afrTarget = 100;
  currentStatus.battery10 = (uint8_t)(((uint32_t)currentStatus.batADC * ADC_VREF * BAT_MULTIPLIER) / (1024UL * 1000UL));
  currentStatus.oilPressure = (uint8_t)fastMap(currentStatus.oilPressADC, 0, 1023, 0, 250);  // 0-1000 kPa em escala 0-250
  currentStatus.fuelPressure = (uint8_t)fastMap(currentStatus.fuelPressADC, 0, 1023, 0, 250);

  currentStatus.TPSlast = currentStatus.TPS;
  lastTPSReadTime = micros();

  DEBUG_PRINTLN(F("Sensores inicializados"));
}

// ============================================================================
// LEITURA DE MAP
// ============================================================================

void readMAP() {
  // Lê ADC
  uint16_t rawADC = analogRead(PIN_MAP);

  // Aplica filtro
  currentStatus.mapADC = applyFilter(rawADC, currentStatus.mapADC, configPage1.mapFilter);

  // Converte para kPa usando calibração
  currentStatus.MAP = fastMap(currentStatus.mapADC, 0, 1023, configPage1.mapMin, configPage1.mapMax);

  // Limita
  if (currentStatus.MAP < 10) currentStatus.MAP = 10;    // Mínimo 10 kPa
  if (currentStatus.MAP > 255) currentStatus.MAP = 255;  // Máximo 255 kPa
}

// ============================================================================
// LEITURA DE TPS
// ============================================================================

void readTPS() {
  uint32_t now = micros();

  // Lê ADC
  uint16_t rawADC = analogRead(PIN_TPS);

  // Aplica filtro
  currentStatus.tpsADC = applyFilter(rawADC, currentStatus.tpsADC, configPage1.tpsFilter);

  // Converte para 8-bit para economizar espaço
  uint8_t tpsADC8 = adc10to8(currentStatus.tpsADC);

  // Aplica calibração (0-100%)
  if (tpsADC8 <= configPage1.tpsMin) {
    currentStatus.TPS = 0;
  } else if (tpsADC8 >= configPage1.tpsMax) {
    currentStatus.TPS = 100;
  } else {
    currentStatus.TPS = fastMap(tpsADC8, configPage1.tpsMin, configPage1.tpsMax, 0, 100);
  }

  // Calcula TPSdot
  uint32_t deltaTime = now - lastTPSReadTime;
  if (deltaTime > 0) {
    currentStatus.TPSdot = calculateTPSdot(currentStatus.TPS, currentStatus.TPSlast, deltaTime);

    // Atualiza histórico
    currentStatus.TPSlast = currentStatus.TPS;
    lastTPSReadTime = now;
  }
}

// ============================================================================
// LEITURA DE CLT
// ============================================================================

void readCLT() {
  // Lê ADC
  uint16_t rawADC = analogRead(PIN_CLT);

  // Aplica filtro forte (temperatura muda lentamente)
  currentStatus.cltADC = applyFilter(rawADC, currentStatus.cltADC, FILTER_CLT);

  // Converte para temperatura
  currentStatus.coolant = ntcToCelsius(currentStatus.cltADC);
}

// ============================================================================
// LEITURA DE IAT
// ============================================================================

void readIAT() {
  // Lê ADC
  uint16_t rawADC = analogRead(PIN_IAT);

  // Aplica filtro
  currentStatus.iatADC = applyFilter(rawADC, currentStatus.iatADC, FILTER_IAT);

  // Converte para temperatura
  currentStatus.IAT = ntcToCelsius(currentStatus.iatADC);
}

// ============================================================================
// LEITURA DE O2
// ============================================================================

void readO2() {
  // Lê ADC
  uint16_t rawADC = analogRead(PIN_O2);

  // Aplica filtro
  currentStatus.o2ADC = applyFilter(rawADC, currentStatus.o2ADC, FILTER_O2);

  // Converte para escala 0-200 (0-1V). 100 ≈ 0,5V (~lambda 1.0)
  currentStatus.O2 = convertNarrowbandToScale(currentStatus.o2ADC);
}

// ============================================================================
// LEITURA DE BATERIA
// ============================================================================

void readBattery() {
  // Lê ADC
  uint16_t rawADC = analogRead(PIN_BAT);

  // Aplica filtro
  currentStatus.batADC = applyFilter(rawADC, currentStatus.batADC, FILTER_BAT);

  // Converte para tensão * 10
  // Formula: V = (ADC / 1024) * VREF * (R1+R2)/R2
  // Com divisor 10K:1K5 -> multiplicador = 7.67
  // Resultado em volts * 10 (ex: 145 = 14.5V)
  uint32_t voltage = ((uint32_t)currentStatus.batADC * ADC_VREF * BAT_MULTIPLIER) / (1024UL * 1000UL);
  currentStatus.battery10 = (uint8_t)voltage;
}

// ============================================================================
// LEITURA DE PRESSÃO DE ÓLEO
// ============================================================================

void readOilPressure() {
  // Lê ADC
  uint16_t rawADC = analogRead(PIN_OIL_PRESSURE);

  // Aplica filtro
  currentStatus.oilPressADC = applyFilter(rawADC, currentStatus.oilPressADC, FILTER_OIL_PRESS);

  // Converte para kPa (sensor típico 0-5V = 0-1000 kPa)
  // Usa escala 0-250 para caber em uint8_t (multiplicar por 4 para obter kPa real)
  uint16_t pressKpa = fastMap(currentStatus.oilPressADC, 0, 1023, 0, 1000);
  currentStatus.oilPressure = (uint8_t)(pressKpa >> 2);  // Divide por 4

  // Limita
  if (currentStatus.oilPressure > 250) currentStatus.oilPressure = 250;
}

// ============================================================================
// LEITURA DE PRESSÃO DE COMBUSTÍVEL
// ============================================================================

void readFuelPressure() {
  // Lê ADC
  uint16_t rawADC = analogRead(PIN_FUEL_PRESSURE);

  // Aplica filtro
  currentStatus.fuelPressADC = applyFilter(rawADC, currentStatus.fuelPressADC, FILTER_FUEL_PRESS);

  // Converte para kPa (sensor típico 0-5V = 0-1000 kPa)
  // Usa escala 0-250 para caber em uint8_t (multiplicar por 4 para obter kPa real)
  uint16_t pressKpa = fastMap(currentStatus.fuelPressADC, 0, 1023, 0, 1000);
  currentStatus.fuelPressure = (uint8_t)(pressKpa >> 2);  // Divide por 4

  // Limita
  if (currentStatus.fuelPressure > 250) currentStatus.fuelPressure = 250;
}

// ============================================================================
// LEITURA COMPLETA
// ============================================================================

void readAllSensors() {
  readMAP();
  readTPS();
  readCLT();
  readIAT();
  readO2();
  readBattery();
  readOilPressure();
  readFuelPressure();
}

// ============================================================================
// CONVERSÃO NTC -> CELSIUS
// ============================================================================

int8_t ntcToCelsius(uint16_t adc) {
  // Tabela simplificada de conversão NTC 10K @ 25°C (Beta ~3950)
  // Usa aproximação linear por faixas para economia de memória

  // Pontos de referência (ADC, Temperatura)
  // ADC alto = temperatura baixa (resistência alta)
  // ADC baixo = temperatura alta (resistência baixa)

  // Tabela aproximada (valores típicos para NTC 10K com pull-up 10K)
  const struct {
    uint16_t adc;
    int8_t temp;
  } ntcTable[] PROGMEM = {
    {980, -40},   // ADC alto = muito frio
    {960, -20},
    {920, 0},
    {850, 20},
    {750, 40},
    {620, 60},
    {480, 80},
    {360, 100},
    {260, 120},
    {180, 140},
    {120, 160}    // ADC baixo = muito quente
  };

  const uint8_t tableSize = sizeof(ntcTable) / sizeof(ntcTable[0]);

  // Busca na tabela e interpola
  for (uint8_t i = 0; i < tableSize - 1; i++) {
    uint16_t adc1 = pgm_read_word(&ntcTable[i].adc);
    uint16_t adc2 = pgm_read_word(&ntcTable[i + 1].adc);
    int8_t temp1 = pgm_read_byte(&ntcTable[i].temp);
    int8_t temp2 = pgm_read_byte(&ntcTable[i + 1].temp);

    if (adc >= adc2 && adc <= adc1) {
      // Interpola (nota: ADC decresce quando temp aumenta)
      return temp1 + (int32_t)(adc1 - adc) * (temp2 - temp1) / (adc1 - adc2);
    }
  }

  // Fora da faixa
  if (adc > 980) return -40;  // Muito frio
  if (adc < 120) return 160;  // Muito quente

  return 25;  // Fallback
}

// ============================================================================
// CÁLCULO DE TPSdot
// ============================================================================

int16_t calculateTPSdot(uint8_t currentTPS, uint8_t lastTPS, uint32_t deltaTimeUs) {
  // Evita divisão por zero
  if (deltaTimeUs == 0) return 0;

  // Diferença de TPS
  int16_t deltaTPS = (int16_t)currentTPS - (int16_t)lastTPS;

  // Converte para %/segundo
  // TPSdot = (deltaTPS / deltaTimeUs) * 1.000.000
  int32_t tpsDot = ((int32_t)deltaTPS * 1000000L) / (int32_t)deltaTimeUs;

  // Limita para caber em int16_t
  if (tpsDot > 32767) tpsDot = 32767;
  if (tpsDot < -32768) tpsDot = -32768;

  return (int16_t)tpsDot;
}
