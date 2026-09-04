/**
 * @file storage.h
 * @brief Leitura de celulas de tabela - PLACEHOLDER, nao e storage real
 *
 * O AVR le/escreve EEPROM de verdade (storage.cpp, eepromReadByte/
 * eepromWriteByte). O MC68HC908GP32 NAO TEM EEPROM separada - so Flash
 * (ver Chapter 2.6 do datasheet: paginas apagadas em blocos de 128 bytes,
 * regravadas com bomba de carga interna via FLCR). Isso exige um redesign
 * de verdade (provavelmente um shadow em RAM sincronizado com Flash de
 * tempos em tempos), NAO uma troca de registrador - ainda nao decidido
 * nem implementado.
 *
 * Por ora, para nao travar o port de tables.c/fuel.c, estas funcoes
 * retornam um valor fixo (placeholder). O RESULTADO NAO REPRESENTA UMA
 * TABELA DE VERDADE - so existe para exercitar a estrutura de codigo
 * (interpolacao, indices, etc) e medir RAM/Flash do restante do port.
 */

#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>

uint8_t eepromReadByte(uint16_t address);
int8_t  eepromReadI8(uint16_t address);

#endif /* STORAGE_H */
