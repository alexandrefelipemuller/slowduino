/**
 * @file tables.h
 * @brief Tabelas 2D/3D e interpolação
 *
 * Sistema de lookup e interpolação para mapas de combustível e ignição
 */

#ifndef TABLES_H
#define TABLES_H

#include <Arduino.h>
#include "config.h"

// ============================================================================
// ESTRUTURA DE TABELA 3D (8x8)
// ============================================================================

// BRANCH ms1: os valores da tabela (values[Y][X]) NÃO ficam em RAM. Só os
// eixos (36 bytes) e o cache ficam residentes; cada lookup lê as 4 células
// vizinhas direto da EEPROM (eepromValuesBase + y*TABLE_SIZE_X + x). Mesma
// técnica do firmware original do MS1 (68HC908, 512B de RAM): ele mantém as
// tabelas na memória persistente e só copia para RAM quando uma página está
// sendo editada ao vivo pelo tuning software - aqui não há RAM disponível
// nem para isso, cada lookup vai direto para EEPROM.
//
// Custo: cada lookup faz até 4 leituras de EEPROM (~3.3us cada no AVR) em
// vez de acesso a RAM. Ver documents/BRANCH_MS1_REDUCAO_RAM.md para a
// análise de timing.
struct Table3D {
  // Eixos
  uint16_t axisX[TABLE_SIZE_X];  // RPM
  uint8_t  axisY[TABLE_SIZE_Y];  // MAP ou TPS

  // Endereço EEPROM dos TABLE_SIZE_Y*TABLE_SIZE_X valores da tabela.
  // Para VE: uint8_t (0-255%). Para Ign: int8_t (-128 a +127 graus).
  uint16_t eepromValuesBase;

  // Cache para otimização
  uint8_t lastX;         // Último índice X
  uint8_t lastY;         // Último índice Y
  uint16_t lastInputX;   // Último input X (RPM)
  uint8_t lastInputY;    // Último input Y (MAP)
  int16_t lastOutput;    // Último resultado

  // Flag indicando se valores são signed
  bool isSigned;
};

// ============================================================================
// ESTRUTURA DE TABELA 2D (para correções)
// ============================================================================

struct Table2D {
  uint8_t size;              // Número de pontos
  int8_t* bins;              // Eixo X (ex: temperatura)
  uint8_t* values;           // Valores Y (ex: % de correção)

  // Cache
  uint8_t lastBin;
  int8_t lastInput;
  uint8_t lastOutput;
};

// ============================================================================
// TABELAS GLOBAIS
// ============================================================================

extern struct Table3D veTable;      // Tabela VE (Volumetric Efficiency)
extern struct Table3D ignTable;     // Tabela de Ignição (Advance)

// ============================================================================
// FUNÇÕES DE INICIALIZAÇÃO
// ============================================================================

/**
 * @brief Inicializa tabelas globais
 *
 * Configura flags isSigned e limpa caches.
 * Deve ser chamada no setup() antes de usar as tabelas.
 */
void initTables();

// ============================================================================
// FUNÇÕES DE INTERPOLAÇÃO
// ============================================================================

/**
 * @brief Obtém valor de tabela 3D com interpolação bilinear
 *
 * @param table Ponteiro para tabela
 * @param valueY Valor do eixo Y (ex: MAP em kPa)
 * @param valueX Valor do eixo X (ex: RPM)
 * @return Valor interpolado
 *
 * Usa aritmética inteira para performance.
 * Implementa interpolação bilinear entre os 4 pontos mais próximos.
 */
int16_t getTableValue(struct Table3D* table, uint8_t valueY, uint16_t valueX);

/**
 * @brief Obtém valor de tabela 2D com interpolação linear
 *
 * @param table Ponteiro para tabela
 * @param value Valor de entrada (ex: temperatura)
 * @return Valor interpolado
 */
uint8_t getTable2DValue(struct Table2D* table, int8_t value);

/**
 * @brief Encontra índices no eixo X (RPM) para interpolação
 *
 * @param table Ponteiro para tabela
 * @param value Valor procurado (RPM)
 * @param idxLow [out] Índice inferior
 * @param idxHigh [out] Índice superior
 *
 * Se value estiver abaixo do menor bin, ambos retornam 0.
 * Se value estiver acima do maior bin, ambos retornam TABLE_SIZE_X-1.
 */
void findTableXIndices(struct Table3D* table, uint16_t value, uint8_t* idxLow, uint8_t* idxHigh);

/**
 * @brief Encontra índices no eixo Y (MAP) para interpolação
 *
 * Similar a findTableXIndices, mas para eixo Y.
 */
void findTableYIndices(struct Table3D* table, uint8_t value, uint8_t* idxLow, uint8_t* idxHigh);

/**
 * @brief Interpolação linear simples (usada internamente)
 *
 * @param x Valor de entrada
 * @param x1 Ponto inferior
 * @param x2 Ponto superior
 * @param y1 Valor no ponto inferior
 * @param y2 Valor no ponto superior
 * @return Valor interpolado
 */
inline int16_t interpolate(int16_t x, int16_t x1, int16_t x2, int16_t y1, int16_t y2) {
  // Evita divisão por zero
  if (x2 == x1) return y1;

  // y = y1 + (x - x1) * (y2 - y1) / (x2 - x1)
  return y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1);
}

/**
 * @brief Interpola uma curva pequena com bins signed e valores unsigned
 *
 * Versão sem cache e sem estado do getTable2DValue(), para as curvas de 4
 * pontos guardadas direto no ConfigPage2 (idle por CLT, etc). Não gasta RAM
 * e é chamada a 15Hz, onde o custo da busca linear é irrelevante.
 *
 * Fora dos limites da curva, satura no primeiro/último valor.
 *
 * @param bins   Eixo X, em ordem crescente (ex: temperatura em °C)
 * @param values Valores Y
 * @param size   Número de pontos
 * @param x      Valor de entrada
 * @return Valor interpolado
 */
uint8_t lookupCurveU8(const int8_t* bins, const uint8_t* values, uint8_t size, int16_t x);

/**
 * @brief Interpola uma curva pequena com bins unsigned e valores signed
 *
 * Igual a lookupCurveU8, mas para curvas cujo eixo X não é negativo e cujo
 * valor pode ser (ex: idle advance por delta de RPM, que admite retardo).
 */
int8_t lookupCurveI8(const uint8_t* bins, const int8_t* values, uint8_t size, int16_t x);

/**
 * @brief Limpa cache de todas as tabelas
 *
 * Útil após modificação de tabelas via TunerStudio
 */
void clearTableCaches();

#endif // TABLES_H
