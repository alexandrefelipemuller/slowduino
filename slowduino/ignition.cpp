/**
 * @file ignition.cpp
 * @brief Implementação dos cálculos de ignição
 */

#include "ignition.h"

// ============================================================================
// CÁLCULO DE AVANÇO
// ============================================================================

int8_t calculateAdvance() {
  // 1. Durante cranking, usa avanço fixo
  if (BIT_CHECK(currentStatus.engineStatus, ENGINE_CRANK)) {
    return configPage2.crankAdvance;
  }

  // 2. Obtém avanço base da tabela
  int8_t advance = getBaseAdvance();

  // 3. Aplica correções
  advance = applyAdvanceCorrections(advance);

  // 4. Aplica rev limiter
  advance = applyRevLimiter(advance);

  // 5. Limita range
  if (advance < IGN_MIN_ADVANCE) advance = IGN_MIN_ADVANCE;
  if (advance > IGN_MAX_ADVANCE) advance = IGN_MAX_ADVANCE;

  return advance;
}

// ============================================================================
// LOOKUP DE AVANÇO
// ============================================================================

int8_t getBaseAdvance() {
  // Busca na tabela de ignição (MAP vs RPM)
  int16_t advance = getTableValue(&ignTable, currentStatus.MAP, currentStatus.RPM);

  // Tabela de ignição usa int8_t (graus, pode ser negativo)
  return (int8_t)advance;
}

// ============================================================================
// CORREÇÕES DE AVANÇO
// ============================================================================

int8_t applyAdvanceCorrections(int8_t baseAdvance) {
  int8_t corrected = baseAdvance;

  // Correção por temperatura
  corrected += correctionCLTAdvance();

  // Correção de idle
  if (currentStatus.RPM > 0 && currentStatus.RPM < (configPage2.idleRPM * 10)) {
    corrected += correctionIdleAdvance();
  }

  return corrected;
}

int8_t correctionCLTAdvance() {
  // Motor frio = mais avanço (melhora partida)
  int8_t temp = currentStatus.coolant;

  // Busca linear na tabela de correção CLT
  for (uint8_t i = 0; i < 3; i++) {
    if (temp >= configPage2.cltAdvBins[i] && temp < configPage2.cltAdvBins[i + 1]) {
      // Interpola
      int8_t t1 = configPage2.cltAdvBins[i];
      int8_t t2 = configPage2.cltAdvBins[i + 1];
      int8_t v1 = configPage2.cltAdvValues[i];
      int8_t v2 = configPage2.cltAdvValues[i + 1];

      return v1 + (int32_t)(temp - t1) * (v2 - v1) / (t2 - t1);
    }
  }

  // Fora da tabela
  if (temp < configPage2.cltAdvBins[0]) {
    return configPage2.cltAdvValues[0];  // Muito frio
  } else {
    return configPage2.cltAdvValues[3];  // Já aquecido
  }
}

int8_t correctionIdleAdvance() {
  // Avanço adicional em idle (melhora estabilidade)
  return configPage2.idleAdvance;
}

// ============================================================================
// REV LIMITER
// ============================================================================

int8_t applyRevLimiter(int8_t advance) {
  uint16_t limitRPM = (uint16_t)configPage2.revLimitRPM * 100;

  if (currentStatus.RPM >= limitRPM) {
    // Corta avanço completamente (corte suave)
    // Pode alternar entre cortar e não cortar para "soft limiter"
    static bool cutState = false;
    cutState = !cutState;

    if (cutState) {
      return IGN_MIN_ADVANCE;  // Retardo máximo
    }
  }

  return advance;
}

// ============================================================================
// CÁLCULO DE DWELL
// ============================================================================

uint16_t calculateDwell() {
  uint16_t dwell;

  // Durante cranking, usa dwell maior (bobina carrega mais)
  if (BIT_CHECK(currentStatus.engineStatus, ENGINE_CRANK)) {
    dwell = configPage2.dwellCrank;
  } else {
    dwell = configPage2.dwellRun;
  }

  // Limita ao máximo (proteção)
  if (dwell > configPage2.dwellLimit) {
    dwell = configPage2.dwellLimit;
  }

  // Limita aos valores seguros
  if (dwell < DWELL_MIN) dwell = DWELL_MIN;
  if (dwell > DWELL_MAX) dwell = DWELL_MAX;

  return dwell;
}
