/**
 * @file board.h
 * @brief Contrato de placa do Slowduino
 *
 * Tudo que muda de uma placa para outra e não é lógica de motor passa por
 * aqui. O restante do firmware não deve usar #if de arquitetura para isso.
 *
 * CONTRATO (o que toda placa precisa fornecer)
 * --------------------------------------------
 * Macros, definidas pelo header da placa (board_uno.h, board_bluepill.h,
 * board_speeduino_v04.h) e selecionadas por board_config.h:
 *   BOARD_NAME            texto para debug
 *   BOARD_MAX_CYLINDERS   máximo de cilindros suportado
 *   BOARD_INJ_CHANNELS    canais de injeção
 *   BOARD_IGN_CHANNELS    canais de ignição
 *   PIN_*                 pinos de trigger, injetores, ignição, auxiliares, ADC
 *   IDLE_PIN_HIGH/LOW()   escrita rápida no pino do IAC (usada em ISR)
 *
 * Funções, implementadas por um .cpp por arquitetura (board_avr.cpp,
 * board_stm32.cpp), cada um ativo só na sua arquitetura:
 *   boardInit()           inicializa a serial/USB, antes de tudo
 *   boardFreeRam()        RAM livre em bytes, para o TunerStudio
 *
 * Fora do contrato por enquanto (ainda em #if dentro de scheduler, auxiliares,
 * decoders e storage): timers do scheduler e do IAC, EEPROM, interrupção do
 * trigger. São os próximos candidatos a entrar aqui.
 */

#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include "board_config.h"

/**
 * @brief Inicializa a comunicação serial da placa.
 * @param baud Velocidade da serial (TunerStudio: 115200).
 *
 * No STM32 com USB CDC também desliga a espera por DTR (issue #4: o core
 * descarta tudo que é escrito enquanto o host não ativa DTR).
 */
void boardInit(uint32_t baud);

/** @brief RAM livre (heap até a pilha), em bytes. */
uint16_t boardFreeRam(void);

#endif // BOARD_H
