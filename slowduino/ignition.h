/**
 * @file ignition.h
 * @brief Cálculos de ignição (avanço e dwell)
 */

#ifndef IGNITION_H
#define IGNITION_H

#include <Arduino.h>
#include "globals.h"
#include "config.h"
#include "tables.h"

// ============================================================================
// FUNÇÕES PRINCIPAIS
// ============================================================================

/**
 * @brief Calcula avanço de ignição
 *
 * Faz lookup na tabela de ignição e aplica correções
 * @return Avanço em graus BTDC (-10 a +45)
 */
int8_t calculateAdvance();

/**
 * @brief Calcula dwell (tempo de carga da bobina)
 *
 * Pode ser fixo ou baseado em tabela/tensão
 * @return Dwell em microsegundos
 */
uint16_t calculateDwell();

// ============================================================================
// LOOKUP E CORREÇÕES
// ============================================================================

/**
 * @brief Obtém avanço base da tabela
 *
 * Lookup 3D usando MAP e RPM
 * @return Avanço em graus
 */
int8_t getBaseAdvance();

/**
 * @brief Aplica correções ao avanço
 *
 * CLT, idle, etc
 * @param baseAdvance Avanço base da tabela
 * @return Avanço corrigido
 */
int8_t applyAdvanceCorrections(int8_t baseAdvance);

/**
 * @brief Correção de avanço por CLT
 *
 * Motor frio = mais avanço
 * @return Correção em graus (pode ser negativa)
 */
int8_t correctionCLTAdvance();

/**
 * @brief Correção de avanço em idle
 *
 * @return Avanço adicional em graus
 */
int8_t correctionIdleAdvance();

/**
 * @brief Verifica rev limiter
 *
 * Corta avanço se RPM exceder limite
 * @param advance Avanço atual
 * @return Avanço limitado
 */
int8_t applyRevLimiter(int8_t advance);

#endif // IGNITION_H
