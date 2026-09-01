/**
 * @file sensors.cpp
 * @brief Implementação da leitura de sensores
 */

#include "sensors.h"

// Variáveis estáticas para cálculo de TPSdot
static uint32_t lastTPSReadTime = 0;

// ============================================================================
// INICIALIZAÇÃO
// ============================================================================

void sensorsInit() {
#if !defined(__AVR__)
  // O código inteiro assume ADC de 10 bits (0-1023), igual ao AVR. Núcleos
  // não-AVR (ex: STM32) tipicamente têm ADC de 12 bits por padrão - força
  // 10 bits aqui para não ter que tocar em nenhuma conta de sensores.cpp.
  analogReadResolution(10);
#endif

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
  currentStatus.coolant = calibrateTemperature(currentStatus.cltADC, calibrationConfig.cltAdcBins, calibrationConfig.cltTempValues);
  currentStatus.IAT = calibrateTemperature(currentStatus.iatADC, calibrationConfig.iatAdcBins, calibrationConfig.iatTempValues);
  currentStatus.O2 = calibrateO2(currentStatus.o2ADC);
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

  // Converte para temperatura usando calibração do usuário (TunerStudio)
  currentStatus.coolant = calibrateTemperature(currentStatus.cltADC, calibrationConfig.cltAdcBins, calibrationConfig.cltTempValues);
}

// ============================================================================
// LEITURA DE IAT
// ============================================================================

void readIAT() {
  // Lê ADC
  uint16_t rawADC = analogRead(PIN_IAT);

  // Aplica filtro
  currentStatus.iatADC = applyFilter(rawADC, currentStatus.iatADC, FILTER_IAT);

  // Converte para temperatura usando calibração do usuário (TunerStudio)
  currentStatus.IAT = calibrateTemperature(currentStatus.iatADC, calibrationConfig.iatAdcBins, calibrationConfig.iatTempValues);
}

// ============================================================================
// LEITURA DE O2
// ============================================================================

void readO2() {
  // Lê ADC
  uint16_t rawADC = analogRead(PIN_O2);

  // Aplica filtro
  currentStatus.o2ADC = applyFilter(rawADC, currentStatus.o2ADC, FILTER_O2);

  // Converte para percentual (0-255, 100 = lambda 1.0) usando calibração
  // linear min/max do usuário (mesma escala de tpsMin/tpsMax)
  currentStatus.O2 = calibrateO2(currentStatus.o2ADC);
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
// CALIBRAÇÃO DE SENSORES (CLT/IAT/O2, curvas editáveis via TunerStudio)
// ============================================================================

static int8_t clampToInt8(int32_t value) {
  if (value > 127) return 127;
  if (value < -128) return -128;
  return (int8_t)value;
}

int8_t calibrateTemperature(uint16_t adc, const uint16_t* adcBins, const int8_t* tempValues) {
  // adcBins é decrescente (ADC alto = frio, resistência alta do NTC)
  if (adc >= adcBins[0]) return tempValues[0];
  if (adc <= adcBins[CALIB_POINTS - 1]) return tempValues[CALIB_POINTS - 1];

  for (uint8_t i = 0; i < CALIB_POINTS - 1; i++) {
    uint16_t adc1 = adcBins[i];
    uint16_t adc2 = adcBins[i + 1];

    if (adc <= adc1 && adc >= adc2) {
      // Pontos iguais/corrompidos (ex: EEPROM zerada ou escrita inválida
      // do TunerStudio) - evita divisão por zero
      if (adc1 == adc2) return tempValues[i];

      int32_t temp1 = tempValues[i];
      int32_t temp2 = tempValues[i + 1];
      int32_t result = temp1 + (int32_t)(adc1 - adc) * (temp2 - temp1) / (adc1 - adc2);
      return clampToInt8(result);
    }
  }

  return tempValues[CALIB_POINTS - 1];
}

uint8_t calibrateO2(uint16_t adc) {
  uint8_t adc8 = adc10to8(adc);

  if (adc8 <= calibrationConfig.o2Min) return 0;
  if (adc8 >= calibrationConfig.o2Max) return 255;

  // calibrationConfig.o2Max > o2Min é garantido por sanitizeConfigValues()
  return (uint8_t)fastMap(adc8, calibrationConfig.o2Min, calibrationConfig.o2Max, 0, 255);
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
