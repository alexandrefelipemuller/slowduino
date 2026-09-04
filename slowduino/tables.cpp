/**
 * @file tables.cpp
 * @brief Implementação de tabelas e interpolação
 */

#include "tables.h"
#include "storage.h"  // eepromReadByte/eepromReadI8 - valores da tabela vêm da EEPROM (branch ms1)

// ============================================================================
// INSTANCIAÇÃO DAS TABELAS GLOBAIS
// ============================================================================

struct Table3D veTable;
struct Table3D ignTable;

// ============================================================================
// INICIALIZAÇÃO DAS TABELAS
// ============================================================================

void initTables() {
  // Inicializa flags de tipo
  veTable.isSigned = false;   // VE usa valores unsigned
  ignTable.isSigned = true;   // Ignição usa valores signed (pode ser negativo)

  // Endereço EEPROM onde os valores de cada tabela residem (fixo, nunca muda)
  veTable.eepromValuesBase = EEPROM_VE_TABLE;
  ignTable.eepromValuesBase = EEPROM_IGN_TABLE;
}

// ============================================================================
// LEITURA DE CÉLULA (EEPROM) - branch ms1
// ============================================================================

static int16_t readTableCell(const struct Table3D* table, uint8_t y, uint8_t x) {
  uint16_t addr = table->eepromValuesBase + ((uint16_t)y * TABLE_SIZE_X) + x;
  return table->isSigned ? (int16_t)eepromReadI8(addr) : (int16_t)eepromReadByte(addr);
}

// ============================================================================
// INTERPOLAÇÃO 3D (Bilinear)
// ============================================================================

int16_t getTableValue(struct Table3D* table, uint8_t valueY, uint16_t valueX) {
  // Encontra índices nos eixos
  uint8_t xLow, xHigh, yLow, yHigh;
  findTableXIndices(table, valueX, &xLow, &xHigh);
  findTableYIndices(table, valueY, &yLow, &yHigh);

  // Valores nos 4 cantos do retângulo (lidos da EEPROM - branch ms1)
  int16_t q11 = readTableCell(table, yLow, xLow);
  int16_t q21 = readTableCell(table, yLow, xHigh);
  int16_t q12 = readTableCell(table, yHigh, xLow);
  int16_t q22 = readTableCell(table, yHigh, xHigh);

  // Caso especial: se índices são iguais, não precisa interpolar
  if (xLow == xHigh && yLow == yHigh) {
    return q11;
  }

  // Valores dos eixos nos 4 cantos
  uint16_t x1 = table->axisX[xLow];
  uint16_t x2 = table->axisX[xHigh];
  uint8_t y1 = table->axisY[yLow];
  uint8_t y2 = table->axisY[yHigh];

  // Interpolação bilinear
  int16_t result;

  if (xLow == xHigh) {
    // Só interpola em Y
    result = interpolate(valueY, y1, y2, q11, q12);
  } else if (yLow == yHigh) {
    // Só interpola em X
    result = interpolate(valueX, x1, x2, q11, q21);
  } else {
    // Interpolação bilinear completa
    // Primeiro interpola em X para obter R1 e R2
    int16_t r1 = interpolate(valueX, x1, x2, q11, q21);  // Linha inferior
    int16_t r2 = interpolate(valueX, x1, x2, q12, q22);  // Linha superior

    // Depois interpola em Y entre R1 e R2
    result = interpolate(valueY, y1, y2, r1, r2);
  }

  return result;
}

// ============================================================================
// BUSCA DE ÍNDICES
// ============================================================================

void findTableXIndices(struct Table3D* table, uint16_t value, uint8_t* idxLow, uint8_t* idxHigh) {
  // Verifica limites inferiores
  if (value <= table->axisX[0]) {
    *idxLow = 0;
    *idxHigh = 0;
    return;
  }

  // Verifica limites superiores
  if (value >= table->axisX[TABLE_SIZE_X - 1]) {
    *idxLow = TABLE_SIZE_X - 1;
    *idxHigh = TABLE_SIZE_X - 1;
    return;
  }

  // Busca linear (tabela pequena, busca binária não compensa)
  for (uint8_t i = 0; i < TABLE_SIZE_X - 1; i++) {
    if (value >= table->axisX[i] && value < table->axisX[i + 1]) {
      *idxLow = i;
      *idxHigh = i + 1;
      return;
    }
  }

  // Fallback (não deveria chegar aqui)
  *idxLow = TABLE_SIZE_X - 2;
  *idxHigh = TABLE_SIZE_X - 1;
}

void findTableYIndices(struct Table3D* table, uint8_t value, uint8_t* idxLow, uint8_t* idxHigh) {
  // Verifica limites inferiores
  if (value <= table->axisY[0]) {
    *idxLow = 0;
    *idxHigh = 0;
    return;
  }

  // Verifica limites superiores
  if (value >= table->axisY[TABLE_SIZE_Y - 1]) {
    *idxLow = TABLE_SIZE_Y - 1;
    *idxHigh = TABLE_SIZE_Y - 1;
    return;
  }

  // Busca linear
  for (uint8_t i = 0; i < TABLE_SIZE_Y - 1; i++) {
    if (value >= table->axisY[i] && value < table->axisY[i + 1]) {
      *idxLow = i;
      *idxHigh = i + 1;
      return;
    }
  }

  // Fallback
  *idxLow = TABLE_SIZE_Y - 2;
  *idxHigh = TABLE_SIZE_Y - 1;
}

// ============================================================================
// CURVAS PEQUENAS SEM ESTADO (config pages)
// ============================================================================

uint8_t lookupCurveU8(const int8_t* bins, const uint8_t* values, uint8_t size, int16_t x) {
  if (size == 0) return 0;
  if (x <= bins[0]) return values[0];
  if (x >= bins[size - 1]) return values[size - 1];

  for (uint8_t i = 0; i < size - 1; i++) {
    if (x >= bins[i] && x < bins[i + 1]) {
      return (uint8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
    }
  }

  return values[size - 1];
}

int8_t lookupCurveI8(const uint8_t* bins, const int8_t* values, uint8_t size, int16_t x) {
  if (size == 0) return 0;
  if (x <= (int16_t)bins[0]) return values[0];
  if (x >= (int16_t)bins[size - 1]) return values[size - 1];

  for (uint8_t i = 0; i < size - 1; i++) {
    if (x >= (int16_t)bins[i] && x < (int16_t)bins[i + 1]) {
      return (int8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
    }
  }

  return values[size - 1];
}
