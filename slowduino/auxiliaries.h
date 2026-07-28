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
 * @brief Inicializa o PWM da válvula de marcha lenta (Timer2)
 *
 * ATENÇÃO: o PWM do IAC é gerado por software na ISR do Timer2, e NÃO por
 * analogWrite(). No Uno/Nano o pino do IAC (D9) é OC1A, e analogWrite() nele
 * sobrescreveria OCR1A - o registrador que o scheduler usa para agendar a
 * ignição do canal 1. Ver o comentário em board_config.h.
 *
 * Deve ser chamada depois de storageInit(), pois lê configPage2.idleFreq.
 */
void idlePwmInit();

/**
 * @brief Define a frequência do PWM do IAC
 *
 * @param freqDiv2 Frequência em Hz dividida por 2 (ex: 80 = 160Hz)
 *
 * A resolução de duty é 1/(3968/freq): 160Hz dá ~4% por passo, 80Hz dá ~2%.
 * Valores fora da faixa suportada são saturados.
 */
void idlePwmSetFrequency(uint8_t freqDiv2);

/**
 * @brief Aplica um duty cycle (0-100%) na válvula de marcha lenta
 *
 * Em 0% e 100% a ISR é desligada e o pino fica estático.
 */
void idleSetDuty(uint8_t duty);

/**
 * @brief Controla válvula de marcha lenta
 *
 * Estilo Speeduino, executado a 15Hz:
 * - Partida: duty da curva iacCrankDuty por temperatura
 * - Taper: transição suave partida -> funcionamento (idleTaperTime)
 * - Open loop: duty da curva iacOLPWMVal por temperatura
 * - Closed loop (iacAlgorithm == 2): PID inteiro sobre o duty open loop,
 *   perseguindo currentStatus.CLIdleTarget, com anti-windup por TPS e por
 *   clamp do acumulador
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
