/**
 * @file sensors.h
 * @brief Leitura e processamento de sensores
 *
 * Gerencia ADC, filtros e conversão de sensores analógicos
 */

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "globals.h"
#include "config.h"

// ============================================================================
// FUNÇÕES DE LEITURA DE SENSORES
// ============================================================================

/**
 * @brief Inicializa sistema de sensores
 *
 * Configura pinos de entrada e realiza leituras iniciais
 */
void sensorsInit();

/**
 * @brief Lê sensor MAP (Manifold Absolute Pressure)
 *
 * Lê ADC, aplica filtro IIR e converte para kPa usando calibração.
 * Deve ser chamado frequentemente (1kHz ideal, mínimo 30Hz)
 */
void readMAP();

/**
 * @brief Lê sensor TPS (Throttle Position Sensor)
 *
 * Lê ADC, aplica filtro e converte para percentual (0-100%).
 * Calcula também TPSdot (taxa de mudança).
 * Frequência: 30-50Hz
 */
void readTPS();

/**
 * @brief Lê sensor CLT (Coolant Temperature)
 *
 * Lê ADC do termistor NTC, aplica filtro forte e converte para °C.
 * Usa lookup table ou formula de Steinhart-Hart simplificada.
 * Frequência: 4-10Hz (temperatura muda lentamente)
 */
void readCLT();

/**
 * @brief Lê sensor IAT (Intake Air Temperature)
 *
 * Similar ao CLT, mas para temperatura do ar de admissão.
 * Frequência: 4-10Hz
 */
void readIAT();

/**
 * @brief Lê sonda Lambda (O2)
 *
 * Lê sensor de oxigênio narrowband (0-1V).
 * Converte para valor percentual (100 = lambda 1.0)
 * Frequência: 15-30Hz
 */
void readO2();

/**
 * @brief Lê tensão da bateria
 *
 * Lê ADC através de divisor resistivo e converte para volts * 10
 * (ex: 145 = 14.5V)
 * Frequência: 4-10Hz
 */
void readBattery();

/**
 * @brief Lê sensor de pressão de óleo
 *
 * Lê ADC e converte para kPa (0-1000 kPa típico)
 * Sensores comuns: 0-5V = 0-1000 kPa
 * Frequência: 10-15Hz
 */
void readOilPressure();

/**
 * @brief Lê sensor de pressão de combustível
 *
 * Lê ADC e converte para kPa (0-1000 kPa típico)
 * Sensores comuns: 0-5V = 0-1000 kPa
 * Frequência: 10-15Hz
 */
void readFuelPressure();

/**
 * @brief Lê todos os sensores
 *
 * Chama todas as funções de leitura. Use com cuidado (lento).
 * Melhor chamar cada sensor na frequência apropriada.
 */
void readAllSensors();

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

/**
 * @brief Aplica filtro IIR (Infinite Impulse Response)
 *
 * @param newValue Novo valor lido
 * @param oldValue Valor anterior (filtrado)
 * @param alpha Constante de filtro (0-255, maior = mais filtro)
 * @return Valor filtrado
 *
 * Formula: output = (newValue * (256-alpha) + oldValue * alpha) / 256
 */
inline uint16_t applyFilter(uint16_t newValue, uint16_t oldValue, uint8_t alpha) {
  return ((uint32_t)newValue * (256 - alpha) + (uint32_t)oldValue * alpha) >> 8;
}

/**
 * @brief Converte ADC 10-bit para 8-bit
 *
 * Útil para economizar espaço em buffers
 */
inline uint8_t adc10to8(uint16_t adc) {
  return adc >> 2;
}

/**
 * @brief Converte ADC 8-bit de volta para 10-bit (aproximado)
 */
inline uint16_t adc8to10(uint8_t adc) {
  return (uint16_t)adc << 2;
}

/**
 * @brief Converte ADC para tensão (mV)
 *
 * @param adc Valor ADC (0-1023)
 * @return Tensão em milivolts
 */
inline uint16_t adcToMillivolts(uint16_t adc) {
  return ((uint32_t)adc * ADC_VREF) / 1024;
}

/**
 * @brief Converte ADC para °C usando curva de calibração do usuário
 *
 * Interpolação linear por faixas sobre CALIB_POINTS pontos (ADC decrescente
 * -> temperatura crescente), editável via TunerStudio (CalibrationConfig,
 * página 6) e persistido em EEPROM_CALIBRATION.
 *
 * @param adc Valor ADC do termistor (10-bit)
 * @param adcBins Pontos ADC da curva (calibrationConfig.cltAdcBins/iatAdcBins)
 * @param tempValues Temperaturas correspondentes (°C)
 * @return Temperatura em °C
 */
int8_t calibrateTemperature(uint16_t adc, const uint16_t* adcBins, const int8_t* tempValues);

/**
 * @brief Converte ADC do sensor O2 para 0-255 usando calibração linear min/max
 *
 * Mesmo padrão de tpsMin/tpsMax: calibrationConfig.o2Min/o2Max em escala
 * ADC 8-bit (0-255), editável via TunerStudio.
 *
 * @param adc Valor ADC do sensor O2 (10-bit)
 * @return Valor calibrado (0-255, 100 = lambda 1.0)
 */
uint8_t calibrateO2(uint16_t adc);

/**
 * @brief Calcula TPSdot (taxa de mudança do TPS)
 *
 * Retorna %/segundo
 *
 * @param currentTPS TPS atual (%)
 * @param lastTPS TPS anterior (%)
 * @param deltaTimeUs Tempo decorrido (microsegundos)
 * @return Taxa de mudança (%/s)
 */
int16_t calculateTPSdot(uint8_t currentTPS, uint8_t lastTPS, uint32_t deltaTimeUs);

#endif // SENSORS_H
