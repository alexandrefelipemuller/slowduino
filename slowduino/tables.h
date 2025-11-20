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

struct Table3D {
  // Valores da tabela [Y][X]
  // Para VE: uint8_t (0-255%)
  // Para Ign: int8_t (-128 a +127 graus)
  union {
    uint8_t valuesU[TABLE_SIZE_Y][TABLE_SIZE_X];  // Unsigned (VE)
    int8_t  valuesI[TABLE_SIZE_Y][TABLE_SIZE_X];  // Signed (Ignição)
  };

  // Eixos
  uint16_t axisX[TABLE_SIZE_X];  // RPM (0-8000)
  uint8_t  axisY[TABLE_SIZE_Y];  // MAP ou TPS (0-255)

  // Cache para otimização
  uint8_t lastX;         // Último índice X
  uint8_t lastY;         // Último índice Y
  uint16_t lastInputX;   // Último input X (RPM)
  uint8_t lastInputY;    // Último input Y (MAP)
  int16_t lastOutput;    // Último resultado

  // Flag indicando se valores são signed
  bool isSigned;
};

// Alias para clareza
#define values valuesU  // Padrão: usa unsigned

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
extern struct Table3D afrTable;     // Tabela alvo AFR/lambda

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
 * @brief Limpa cache de todas as tabelas
 *
 * Útil após modificação de tabelas via TunerStudio
 */
void clearTableCaches();

#endif // TABLES_H
