/**
 * @file tables.h
 * @brief Tabelas 3D e interpolacao - port C/HC08 da branch tiny
 *
 * Logica identica ao AVR: valores das celulas NAO ficam em RAM, so os
 * eixos residem (ver Table3D abaixo) - cada lookup le da "storage"
 * (ver storage.h - ainda placeholder, GP32 nao tem EEPROM).
 */

#ifndef TABLES_H
#define TABLES_H

#include <stdint.h>
#include <stdbool.h>
#include "config.h"

struct Table3D {
  uint16_t axisX[TABLE_SIZE_X];
  uint8_t  axisY[TABLE_SIZE_Y];
  uint16_t eepromValuesBase;
  bool     isSigned;
};

extern struct Table3D veTable;
extern struct Table3D ignTable;

void initTables(void);

int16_t getTableValue(struct Table3D *table, uint8_t valueY, uint16_t valueX);
void findTableXIndices(struct Table3D *table, uint16_t value, uint8_t *idxLow, uint8_t *idxHigh);
void findTableYIndices(struct Table3D *table, uint8_t value, uint8_t *idxLow, uint8_t *idxHigh);

static inline int16_t interpolate(int16_t x, int16_t x1, int16_t x2, int16_t y1, int16_t y2) {
  if (x2 == x1) return y1;
  return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
}

uint8_t lookupCurveU8(const int8_t *bins, const uint8_t *values, uint8_t size, int16_t x);
int8_t  lookupCurveI8(const uint8_t *bins, const int8_t *values, uint8_t size, int16_t x);

#endif /* TABLES_H */
