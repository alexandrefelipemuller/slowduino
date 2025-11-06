/**
 * @file decoders.h
 * @brief Decoders de trigger wheel (roda fônica)
 *
 * Implementa decodificação de sinais de sensores de rotação
 * e sincronização do motor
 */

#ifndef DECODERS_H
#define DECODERS_H

#include <Arduino.h>
#include "globals.h"
#include "config.h"

// ============================================================================
// ESTRUTURA DE DADOS DO DECODER
// ============================================================================

struct TriggerState {
  // Timing
  volatile uint32_t toothLastToothTime;    // Timestamp do último dente (micros)
  volatile uint32_t toothLastMinusOneTime; // Timestamp do penúltimo dente
  volatile uint32_t revolutionTime;        // Duração da última revolução (micros)
  volatile uint32_t toothOneTime;          // Timestamp do dente #1 (referência)

  // Contadores
  volatile uint16_t toothCurrentCount;     // Contador de dentes na revolução atual
  volatile uint16_t toothTotalCount;       // Total de dentes na roda (ex: 36)
  volatile uint16_t triggerActualTeeth;    // Dentes reais (ex: 35 em 36-1)

  // Gaps e sincronização
  volatile uint32_t curGap;                // Gap atual entre dentes
  volatile uint32_t lastGap;               // Gap anterior
  volatile bool hasSync;                   // Motor sincronizado?
  volatile uint8_t syncLossCounter;        // Contador de falhas de sync

  // RPM
  volatile uint16_t RPM;                   // RPM atual
  volatile uint32_t toothPeriod;           // Período médio entre dentes (micros)

  // Configuração
  uint8_t triggerTeeth;                    // Total de dentes (incluindo faltantes)
  uint8_t triggerMissing;                  // Dentes faltantes (ex: 1 para 36-1)
  uint16_t triggerFilterTime;              // Tempo mínimo entre dentes (debounce)
  uint16_t toothAngle;                     // Ângulo por dente (graus * 10)
};

extern volatile struct TriggerState triggerState;

// ============================================================================
// FUNÇÕES PÚBLICAS
// ============================================================================

/**
 * @brief Inicializa sistema de trigger
 *
 * Seleciona e configura decoder baseado em configPage2.triggerPattern
 */
void triggerInit();

/**
 * @brief Setup do decoder Missing Tooth
 *
 * Configura para rodas tipo 36-1, 60-2, etc
 */
void triggerSetup_MissingTooth();

/**
 * @brief Setup do decoder Basic Distributor
 *
 * Configura para distribuidor simples (1 pulso/revolução)
 */
void triggerSetup_BasicDistributor();

/**
 * @brief ISR primária do trigger (Missing Tooth)
 *
 * Chamada por interrupção externa INT0 (pino D2 - PIN_TRIGGER_PRIMARY)
 * CRÍTICO: código deve ser MUITO rápido!
 */
void triggerPri_MissingTooth();

/**
 * @brief ISR primária do trigger (Basic Distributor)
 */
void triggerPri_BasicDistributor();

/**
 * @brief Calcula RPM baseado no período de revolução
 *
 * Deve ser chamado no loop principal (não na ISR)
 */
void calculateRPM();

/**
 * @brief Verifica timeout de sincronismo
 *
 * Se não receber dentes por muito tempo, perde sync
 * Chamar periodicamente no loop (~10Hz)
 */
void checkSyncLoss();

/**
 * @brief Converte ângulo para tempo (microsegundos)
 *
 * @param angle Ângulo em graus
 * @return Tempo em microsegundos no RPM atual
 */
uint32_t angleToTime(uint16_t angle);

/**
 * @brief Converte tempo para ângulo (graus)
 *
 * @param time Tempo em microsegundos
 * @return Ângulo em graus no RPM atual
 */
uint16_t timeToAngle(uint32_t time);

/**
 * @brief Retorna ângulo atual do virabrequim
 *
 * Calcula posição baseada no último dente e tempo decorrido
 * @return Ângulo em graus (0-359 para 2-stroke, 0-719 para 4-stroke)
 */
uint16_t getCrankAngle();

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

/**
 * @brief Anexa interrupção ao pino de trigger
 *
 * Configura INT0 (pino D2 - PIN_TRIGGER_PRIMARY) com a ISR apropriada
 */
void attachTriggerInterrupt();

/**
 * @brief Remove interrupção do trigger
 */
void detachTriggerInterrupt();

/**
 * @brief Reseta estado do decoder
 *
 * Usado ao trocar de padrão de trigger
 */
void resetTriggerState();

#endif // DECODERS_H
