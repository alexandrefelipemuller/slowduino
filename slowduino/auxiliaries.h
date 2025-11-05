/**
 * @file auxiliaries.h
 * @brief Controle de funções auxiliares (ventoinha, IAC, bomba)
 *
 * Implementação simples usando digitalWrite e analogWrite
 */

#ifndef AUXILIARIES_H
#define AUXILIARIES_H

#include "globals.h"
#include "config.h"

// ============================================================================
// INICIALIZAÇÃO
// ============================================================================

/**
 * @brief Inicializa pinos de saída dos auxiliares
 */
void auxiliariesInit();

// ============================================================================
// VENTOINHA DO RADIADOR
// ============================================================================

/**
 * @brief Controla ventoinha baseado em temperatura
 *
 * Usa histerese para evitar liga/desliga rápido
 * Liga em FAN_ON_TEMP, desliga em FAN_OFF_TEMP
 */
void fanControl();

// ============================================================================
// BOMBA DE COMBUSTÍVEL
// ============================================================================

/**
 * @brief Controla bomba de combustível
 *
 * Liga quando:
 * - Durante priming (primeiros 2s)
 * - Motor girando (RPM > 0)
 * - Modo cranking
 *
 * Desliga quando motor parado por mais de 1 segundo
 */
void fuelPumpControl();

// ============================================================================
// VÁLVULA DE MARCHA LENTA (IAC)
// ============================================================================

/**
 * @brief Controla válvula de marcha lenta (PWM)
 *
 * Ajusta duty cycle baseado no erro de RPM
 * - RPM < alvo: aumenta abertura
 * - RPM > alvo: diminui abertura
 *
 * Usa banda morta (deadband) para evitar oscilação
 */
void idleControl();

// ============================================================================
// MACROS SIMPLES
// ============================================================================

#define FAN_ON()           { digitalWrite(PIN_FAN, HIGH); currentStatus.fanActive = true; }
#define FAN_OFF()          { digitalWrite(PIN_FAN, LOW); currentStatus.fanActive = false; }

#define FUEL_PUMP_ON()     { digitalWrite(PIN_FUEL_PUMP, HIGH); currentStatus.fuelPumpActive = true; }
#define FUEL_PUMP_OFF()    { digitalWrite(PIN_FUEL_PUMP, LOW); currentStatus.fuelPumpActive = false; }

#endif // AUXILIARIES_H
