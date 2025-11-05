/**
 * @file fuel.cpp
 * @brief Implementação dos cálculos de combustível
 */

#include "fuel.h"

// Variáveis estáticas para ASE
static uint16_t aseCounter = 0;      // Contador de ignições restantes com ASE
static uint16_t aseValue = 100;      // Valor atual de ASE (%)

// ============================================================================
// CÁLCULO PRINCIPAL DE INJEÇÃO
// ============================================================================

uint16_t calculateInjection() {
  // 1. Obtém VE da tabela
  uint8_t ve = getVE();
  currentStatus.VE = ve;

  // 2. Calcula correções
  uint16_t corrections = calculateCorrections();
  currentStatus.corrections = corrections;

  // 3. Calcula PW base
  // PW = (reqFuel * VE / 100) * (MAP / 100) * (corrections / 100)
  // Simplificando para evitar overflow:
  // PW = (reqFuel * VE * MAP * corrections) / (100 * 100 * 100)

  uint32_t pw = (uint32_t)configPage1.reqFuel;
  pw = (pw * ve) / 100;
  pw = (pw * currentStatus.MAP) / 100;
  pw = (pw * corrections) / 100;

  // 4. Adiciona tempo de abertura do injetor (deadtime)
  pw += configPage1.injOpen;

  // 5. Limita
  if (pw < INJ_MIN_PW) pw = INJ_MIN_PW;
  if (pw > INJ_MAX_PW) pw = INJ_MAX_PW;

  return (uint16_t)pw;
}

// ============================================================================
// LOOKUP DE VE
// ============================================================================

uint8_t getVE() {
  // Usa MAP e RPM para buscar na tabela
  int16_t ve = getTableValue(&veTable, currentStatus.MAP, currentStatus.RPM);

  // Garante range válido
  if (ve < 0) ve = 0;
  if (ve > 255) ve = 255;

  return (uint8_t)ve;
}

// ============================================================================
// CORREÇÕES
// ============================================================================

uint16_t calculateCorrections() {
  uint16_t total = 100;  // Base 100%

  // 1. Warm-Up Enrichment (multiplicativo)
  uint8_t wue = correctionWUE();
  currentStatus.wueCorrection = wue;
  total = PERCENT(total, wue);

  // 2. After-Start Enrichment (multiplicativo)
  uint8_t ase = correctionASE();
  currentStatus.aseCorrection = ase;
  total = PERCENT(total, ase);

  // 3. CLT correction (multiplicativo)
  uint8_t clt = correctionCLT();
  currentStatus.cltCorrection = clt;
  total = PERCENT(total, clt);

  // 4. Battery correction (multiplicativo)
  uint8_t bat = correctionBattery();
  currentStatus.batCorrection = bat;
  total = PERCENT(total, bat);

  // 5. Acceleration Enrichment (aditivo)
  uint8_t ae = correctionAE();
  currentStatus.aeCorrection = ae;
  total += ae;

  // Limita resultado
  if (total < CORR_MIN) total = CORR_MIN;
  if (total > CORR_MAX) total = CORR_MAX;

  return total;
}

// ============================================================================
// WARM-UP ENRICHMENT
// ============================================================================

uint8_t correctionWUE() {
  // Verifica se motor está em aquecimento
  if (!BIT_CHECK(currentStatus.engineStatus, ENGINE_WARMUP)) {
    return 100;  // Sem correção
  }

  // Busca na tabela WUE baseado em temperatura
  // Tabela está em configPage1.wueBins[] e wueValues[]
  int8_t temp = currentStatus.coolant;

  // Busca linear nos bins
  for (uint8_t i = 0; i < 5; i++) {
    if (temp >= configPage1.wueBins[i] && temp < configPage1.wueBins[i + 1]) {
      // Interpola
      int8_t t1 = configPage1.wueBins[i];
      int8_t t2 = configPage1.wueBins[i + 1];
      uint8_t v1 = configPage1.wueValues[i];
      uint8_t v2 = configPage1.wueValues[i + 1];

      return v1 + (int32_t)(temp - t1) * (v2 - v1) / (t2 - t1);
    }
  }

  // Fora da tabela
  if (temp < configPage1.wueBins[0]) {
    return configPage1.wueValues[0];  // Muito frio
  } else {
    return configPage1.wueValues[5];  // Já aquecido
  }
}

// ============================================================================
// AFTER-START ENRICHMENT
// ============================================================================

uint8_t correctionASE() {
  // Verifica se ASE está ativo
  if (!BIT_CHECK(currentStatus.engineStatus, ENGINE_ASE)) {
    return 100;
  }

  return aseValue;
}

void startASE() {
  // Inicia ASE com valores configurados
  aseCounter = configPage1.aseCount;
  aseValue = configPage1.asePct;
  BIT_SET(currentStatus.engineStatus, ENGINE_ASE);
}

void decrementASE() {
  // Chamado a cada ignição
  if (aseCounter > 0) {
    aseCounter--;

    // Decremento linear do enriquecimento
    if (configPage1.aseCount > 0) {
      uint16_t step = (configPage1.asePct - 100) / configPage1.aseCount;
      aseValue -= step;

      if (aseValue <= 100) {
        aseValue = 100;
        BIT_CLEAR(currentStatus.engineStatus, ENGINE_ASE);
      }
    }
  } else {
    aseValue = 100;
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_ASE);
  }
}

// ============================================================================
// ACCELERATION ENRICHMENT
// ============================================================================

uint8_t correctionAE() {
  // Baseado em TPSdot (taxa de mudança do TPS)
  if (configPage1.aeMode != AE_MODE_TPS) {
    return 0;  // AE desabilitado ou modo MAP (não implementado ainda)
  }

  // Verifica se está acelerando
  if (currentStatus.TPSdot > configPage1.aeThresh) {
    // Aceleração detectada
    BIT_SET(currentStatus.engineStatus, ENGINE_ACC);

    // Retorna enriquecimento
    // Quanto maior TPSdot, maior o enriquecimento
    uint8_t ae = configPage1.aePct - 100;  // Ex: 120 - 100 = 20

    // Escalona baseado em TPSdot (simples)
    if (currentStatus.TPSdot > (configPage1.aeThresh * 3)) {
      ae = ae * 2;  // Dobra em aceleração forte
    }

    return ae;

  } else {
    // Não está acelerando
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_ACC);
    return 0;
  }
}

// ============================================================================
// CORREÇÃO POR TEMPERATURA (CLT)
// ============================================================================

uint8_t correctionCLT() {
  // Ajuste fino por temperatura (além do WUE)
  // Motor muito quente = reduz um pouco
  // Motor frio = já coberto pelo WUE

  if (currentStatus.coolant > 100) {
    // Acima de 100°C, reduz 1% a cada 5°C
    int8_t reduction = (currentStatus.coolant - 100) / 5;
    if (reduction > 5) reduction = 5;  // Máximo -5%
    return 100 - reduction;
  }

  return 100;  // Sem correção
}

// ============================================================================
// CORREÇÃO POR BATERIA
// ============================================================================

uint8_t correctionBattery() {
  // Injetores abrem mais lento com tensão baixa
  // Compensa aumentando PW

  uint8_t voltage = currentStatus.battery10;  // Volts * 10 (ex: 145 = 14.5V)

  if (voltage < 110) {
    // Abaixo de 11V: +10%
    return 110;
  } else if (voltage < 120) {
    // 11-12V: +5%
    return 105;
  } else if (voltage > 150) {
    // Acima de 15V: -3%
    return 97;
  }

  return 100;  // 12-15V: sem correção
}

// ============================================================================
// ESTADO DO MOTOR
// ============================================================================

void updateEngineStatus() {
  // Verifica se está em partida
  if (currentStatus.RPM > 0 && currentStatus.RPM < (configPage1.crankRPM * 10)) {
    BIT_SET(currentStatus.engineStatus, ENGINE_CRANK);
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_RUN);
  }
  // Verifica se está rodando
  else if (currentStatus.RPM >= (configPage1.crankRPM * 10)) {
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_CRANK);
    BIT_SET(currentStatus.engineStatus, ENGINE_RUN);

    // Primeira ignição após partida: inicia ASE
    static bool firstRun = true;
    if (firstRun) {
      startASE();
      firstRun = false;
    }
  }
  // Parado
  else {
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_CRANK);
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_RUN);
  }

  // Verifica aquecimento
  if (currentStatus.coolant < 60) {
    BIT_SET(currentStatus.engineStatus, ENGINE_WARMUP);
  } else {
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_WARMUP);
  }
}
