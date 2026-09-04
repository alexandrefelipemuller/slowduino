/**
 * @file serial_hc08.c
 * @brief Implementacao da camada de I/O serial via SCI (ver serial_hc08.h)
 */

#include "serial_hc08.h"
#include "mc68hc908gp32_sfr.h"

void sciInit(void) {
  /* PLACEHOLDER: SCBR=0x00 (prescaler /1, SCR=0) da o baud rate MAXIMO
   * possivel para o clock assumido - NAO calculado para nenhum baud
   * especifico (ex: 115200) porque a formula exata de SCBR depende do
   * bus clock real da placa, ainda nao definido (ver mesma ressalva em
   * timebase.h/scheduler.h). Ajustar antes de testar com TunerStudio de
   * verdade. */
  SCBR = 0x00;

  /* Liga transmissor e receptor */
  SCC2 |= (1 << SCC2_TE) | (1 << SCC2_RE);

  /* Liga a SCI (ENSCI) */
  SCC1 |= (1 << SCC1_ENSCI);
}

bool sciAvailable(void) {
  return (SCS1 & (1 << SCS1_SCRF)) != 0;
}

uint8_t sciReadByte(void) {
  /* Ler SCDR limpa SCRF automaticamente (apos leitura de SCS1 com SCRF=1,
   * que ja aconteceu em sciAvailable()) - mesmo mecanismo de "read status,
   * then read/write data" do resto do chip. */
  return SCDR;
}

void sciWriteByte(uint8_t data) {
  /* Bloqueia ate o registrador de transmissao ficar livre. Sem buffer de
   * TX aqui (ver ressalva de design em serial_hc08.h) - isto e o preco. */
  while ((SCS1 & (1 << SCS1_SCTE)) == 0) {
    /* espera */
  }
  SCDR = data;
}

void sciWriteBytes(const uint8_t *data, uint16_t length) {
  uint16_t i;
  for (i = 0; i < length; i++) {
    sciWriteByte(data[i]);
  }
}

void sciPrintString(const char *str) {
  while (*str != '\0') {
    sciWriteByte((uint8_t)*str);
    str++;
  }
}
