/**
 * @file board_stm32.cpp
 * @brief Implementação do contrato de placa (board.h) para STM32
 *        (Arduino_Core_STM32, ex.: Blue Pill).
 */

#include "board.h"

#if defined(ARDUINO_ARCH_STM32)

void boardInit(uint32_t baud) {
  Serial.begin(baud);
#if defined(USBCON) && defined(USBD_USE_CDC)
  // Com USB CDC o core descarta em silêncio TUDO que é escrito no Serial
  // enquanto o host não ativa a linha DTR. Terminais e drivers que abrem a
  // porta sem DTR recebiam zero bytes (issue #4): o firmware lia o 'Q' mas a
  // resposta nunca saía.
  Serial.dtr(false);
#endif
}

uint16_t boardFreeRam(void) {
  // newlib: `end` é o fim do BSS / início do heap.
  extern char end;
  char v;
  return (uint16_t)((uint32_t)&v - (uint32_t)&end);
}

#endif // ARDUINO_ARCH_STM32
