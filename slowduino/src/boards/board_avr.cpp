/**
 * @file board_avr.cpp
 * @brief Implementação do contrato de placa (board.h) para AVR
 *        (Uno/Nano ATmega328p e Mega 2560).
 */

#include "board.h"

#if defined(__AVR__)

void boardInit(uint32_t baud) {
  Serial.begin(baud);
}

uint16_t boardFreeRam(void) {
  extern int __heap_start, *__brkval;
  int v;
  return (uint16_t)((int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval));
}

#endif // __AVR__
