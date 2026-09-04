/**
 * @file tables.c
 * @brief Implementacao de tabelas - port 1:1 de tables.cpp (branch tiny)
 */

#include "tables.h"
#include "storage.h"

struct Table3D veTable;
struct Table3D ignTable;

/* PLACEHOLDER: enderecos ficticios ate storage.c ganhar um design real de
 * Flash (ver storage.h). Servem so para exercitar a logica de indice. */
#define EEPROM_VE_TABLE  0
#define EEPROM_IGN_TABLE (TABLE_SIZE_X * TABLE_SIZE_Y)

void initTables(void) {
  veTable.isSigned = false;
  ignTable.isSigned = true;
  veTable.eepromValuesBase = EEPROM_VE_TABLE;
  ignTable.eepromValuesBase = EEPROM_IGN_TABLE;
}

static int16_t readTableCell(const struct Table3D *table, uint8_t y, uint8_t x) {
  uint16_t addr = table->eepromValuesBase + ((uint16_t)y * TABLE_SIZE_X) + x;
  return table->isSigned ? (int16_t)eepromReadI8(addr) : (int16_t)eepromReadByte(addr);
}

int16_t getTableValue(struct Table3D *table, uint8_t valueY, uint16_t valueX) {
  uint8_t xLow, xHigh, yLow, yHigh;
  int16_t q11, q21, q12, q22;
  uint16_t x1, x2;
  uint8_t y1, y2;
  int16_t result;

  findTableXIndices(table, valueX, &xLow, &xHigh);
  findTableYIndices(table, valueY, &yLow, &yHigh);

  q11 = readTableCell(table, yLow, xLow);
  q21 = readTableCell(table, yLow, xHigh);
  q12 = readTableCell(table, yHigh, xLow);
  q22 = readTableCell(table, yHigh, xHigh);

  if (xLow == xHigh && yLow == yHigh) {
    return q11;
  }

  x1 = table->axisX[xLow];
  x2 = table->axisX[xHigh];
  y1 = table->axisY[yLow];
  y2 = table->axisY[yHigh];

  if (xLow == xHigh) {
    result = interpolate((int16_t)valueY, y1, y2, q11, q12);
  } else if (yLow == yHigh) {
    result = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q11, q21);
  } else {
    int16_t r1 = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q11, q21);
    int16_t r2 = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q12, q22);
    result = interpolate((int16_t)valueY, y1, y2, r1, r2);
  }

  return result;
}

void findTableXIndices(struct Table3D *table, uint16_t value, uint8_t *idxLow, uint8_t *idxHigh) {
  uint8_t i;

  if (value <= table->axisX[0]) {
    *idxLow = 0;
    *idxHigh = 0;
    return;
  }
  if (value >= table->axisX[TABLE_SIZE_X - 1]) {
    *idxLow = TABLE_SIZE_X - 1;
    *idxHigh = TABLE_SIZE_X - 1;
    return;
  }

  for (i = 0; i < TABLE_SIZE_X - 1; i++) {
    if (value >= table->axisX[i] && value < table->axisX[i + 1]) {
      *idxLow = i;
      *idxHigh = i + 1;
      return;
    }
  }

  *idxLow = TABLE_SIZE_X - 2;
  *idxHigh = TABLE_SIZE_X - 1;
}

void findTableYIndices(struct Table3D *table, uint8_t value, uint8_t *idxLow, uint8_t *idxHigh) {
  uint8_t i;

  if (value <= table->axisY[0]) {
    *idxLow = 0;
    *idxHigh = 0;
    return;
  }
  if (value >= table->axisY[TABLE_SIZE_Y - 1]) {
    *idxLow = TABLE_SIZE_Y - 1;
    *idxHigh = TABLE_SIZE_Y - 1;
    return;
  }

  for (i = 0; i < TABLE_SIZE_Y - 1; i++) {
    if (value >= table->axisY[i] && value < table->axisY[i + 1]) {
      *idxLow = i;
      *idxHigh = i + 1;
      return;
    }
  }

  *idxLow = TABLE_SIZE_Y - 2;
  *idxHigh = TABLE_SIZE_Y - 1;
}

uint8_t lookupCurveU8(const int8_t *bins, const uint8_t *values, uint8_t size, int16_t x) {
  uint8_t i;
  if (size == 0) return 0;
  if (x <= bins[0]) return values[0];
  if (x >= bins[size - 1]) return values[size - 1];

  for (i = 0; i < size - 1; i++) {
    if (x >= bins[i] && x < bins[i + 1]) {
      return (uint8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
    }
  }
  return values[size - 1];
}

int8_t lookupCurveI8(const uint8_t *bins, const int8_t *values, uint8_t size, int16_t x) {
  uint8_t i;
  if (size == 0) return 0;
  if (x <= (int16_t)bins[0]) return values[0];
  if (x >= (int16_t)bins[size - 1]) return values[size - 1];

  for (i = 0; i < size - 1; i++) {
    if (x >= (int16_t)bins[i] && x < (int16_t)bins[i + 1]) {
      return (int8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
    }
  }
  return values[size - 1];
}
