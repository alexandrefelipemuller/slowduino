/**
 * @file fuel.h
 * @brief Cálculos de injeção de combustível
 *
 * Gerencia cálculo de pulsewidth e correções
 */

#ifndef FUEL_H
#define FUEL_H

#include <Arduino.h>
#include "globals.h"
#include "config.h"
#include "tables.h"

// ============================================================================
// FUNÇÕES PRINCIPAIS
// ============================================================================

/**
 * @brief Calcula pulsewidth de injeção
 *
 * Formula base: PW = (reqFuel × VE% × MAP% × corrections) + injectorOpenTime
 *
 * @return Pulsewidth em microsegundos
 */
uint16_t calculateInjection();

/**
 * @brief Obtém VE da tabela
 *
 * Faz lookup 3D usando MAP e RPM atual
 * @return VE em % (0-255)
 */
uint8_t getVE();

/**
 * @brief Calcula todas as correções de combustível
 *
 * Multiplica/adiciona correções: WUE, ASE, AE, CLT, Bat, etc
 * @return Fator de correção (base 100)
 */
uint16_t calculateCorrections();

// ============================================================================
// CORREÇÕES INDIVIDUAIS
// ============================================================================

/**
 * @brief Warm-Up Enrichment
 *
 * Enriquecimento durante aquecimento do motor
 * @return Percentual (100-200)
 */
uint8_t correctionWUE();

/**
 * @brief After-Start Enrichment
 *
 * Enriquecimento logo após partida
 * @return Percentual (100-200)
 */
uint8_t correctionASE();

/**
 * @brief Acceleration Enrichment
 *
 * Enriquecimento durante aceleração (pump shot)
 * @return Percentual adicional (0-100)
 */
uint8_t correctionAE();

/**
 * @brief Correção por temperatura do motor (CLT)
 *
 * Ajuste fino baseado em temperatura
 * @return Percentual (80-120)
 */
uint8_t correctionCLT();

/**
 * @brief Correção por tensão da bateria
 *
 * Compensa variação no tempo de abertura do injetor
 * @return Percentual (90-110)
 */
uint8_t correctionBattery();

/**
 * @brief Correção fechada baseada na sonda O2 (malha fechada)
 *
 * Replica algoritmo Simple EGO da Speeduino
 * @return Percentual (base 100)
 */
uint8_t correctionEGO();

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

/**
 * @brief Atualiza estado do motor (crank, run, warmup, etc)
 *
 * Verifica RPM e temperaturas para definir flags de estado
 */
void updateEngineStatus();

/**
 * @brief Inicia contador de ASE
 *
 * Chamado quando motor liga
 */
void startASE();

/**
 * @brief Decrementa contador de ASE
 *
 * Chamado a cada ignição
 */
void decrementASE();

#endif // FUEL_H
