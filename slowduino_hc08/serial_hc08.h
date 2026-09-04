/**
 * @file serial_hc08.h
 * @brief Camada de I/O serial sobre a SCI do GP32 - equivalente ao
 *        HardwareSerial do Arduino core, usado pelo comms.c
 *
 * DIFERENCA DE DESIGN: o AVR usa HardwareSerial com ring buffer
 * orientado a interrupcao (RX/TX). Aqui, primeira versao por POLLING
 * simples (sem ISR, sem buffer) - mais simples e suficiente para o
 * protocolo Speeduino, que ja processa comando a comando no loop
 * principal. Trade-off: sciWriteByte() bloqueia ate o registrador de
 * transmissao ficar livre (SCTE) - no AVR isso e escondido pelo buffer
 * de TX; aqui e explicito. Pode virar ISR-driven depois se precisar.
 *
 * Baud rate: PLACEHOLDER, assume bus clock de 8MHz (mesma ressalva de
 * timebase.h/scheduler.h) - ajustar SCBR quando o clock real for
 * definido.
 */

#ifndef SERIAL_HC08_H
#define SERIAL_HC08_H

#include <stdint.h>
#include <stdbool.h>

void sciInit(void);
bool sciAvailable(void);
uint8_t sciReadByte(void);
void sciWriteByte(uint8_t data);
void sciWriteBytes(const uint8_t *data, uint16_t length);
void sciPrintString(const char *str);

#endif /* SERIAL_HC08_H */
