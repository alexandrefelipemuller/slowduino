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
 * @brief Verifica se o idle advance deve atuar
 *
 * Exige: habilitado, motor girando, TPS abaixo de idleAdvTPS e RPM abaixo de
 * idleAdvRPM. O gate de TPS é essencial - sem ele o avanço extra era aplicado
 * com o acelerador aberto em baixo RPM.
 */
bool isIdleAdvanceActive();

/**
 * @brief Correção de avanço em idle
 *
 * Interpola idleAdvValues sobre idleAdvBins usando o quanto o RPM está abaixo
 * de currentStatus.CLIdleTarget. Substituiu o degrau de valor único, que
 * saltava de +15° para 0° ao cruzar o alvo.
 *
 * @return Avanço em graus (pode ser negativo)
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
