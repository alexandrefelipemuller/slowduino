/**
 * @file storage.c
 * @brief PLACEHOLDER - ver aviso grande em storage.h
 */

#include "storage.h"

uint8_t eepromReadByte(uint16_t address) {
  (void)address;
  return 128;  /* placeholder neutro - nao e dado real de tabela */
}

int8_t eepromReadI8(uint16_t address) {
  (void)address;
  return 0;  /* placeholder neutro */
}

bool eepromWriteByte(uint16_t address, uint8_t value) {
  (void)address;
  (void)value;
  return false;  /* placeholder - nao escreve nada de verdade ainda */
}

void eepromWriteI8(uint16_t address, int8_t value) {
  (void)address;
  (void)value;
}

void saveAllConfig(void) {
  /* placeholder - ver storage.h */
}
