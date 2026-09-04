/**
 * @file timebase.c
 * @brief Implementacao de micros() sobre TIM2 (ver timebase.h)
 */

#include "timebase.h"
#include "mc68hc908gp32_sfr.h"
#include "globals.h"

/* Prescaler PS2:PS1:PS0 = 000 (/1). Com clock de barramento de 8MHz,
 * 1 tick = 0.125us -> overflow de 16 bits a cada 8192us. AJUSTAR se o
 * clock real da placa for diferente (ver nota em timebase.h). */
static volatile uint32_t tim2OverflowCount;

void timebaseInit(void) {
  T2SC = (1 << T2SC_TRST);  /* reset do contador */
  T2SC = (1 << T2SC_TOIE);  /* liga overflow interrupt, prescaler /1, roda */
  tim2OverflowCount = 0;
}

uint32_t micros(void) {
  uint32_t overflows;
  uint16_t count;

  /* Le os dois de forma atomica (mesma tecnica do timer0_millis do AVR:
   * desliga interrupcao, le os dois valores consistentes, religa). */
  noInterrupts();
  overflows = tim2OverflowCount;
  count = (uint16_t)((T2CNTH << 8) | T2CNTL);
  interrupts();

  /* 1 tick = 1/8 us (clock de 8MHz, prescaler /1) -> divide por 8 */
  return (overflows << 13) + (count >> 3);
}

void isr_tim2_overflow(void) __interrupt(9) {
  if (T2SC & (1 << T2SC_TOF)) {
    tim2OverflowCount++;
    T2SC &= (uint8_t)~(1 << T2SC_TOF);  /* limpa flag (write 0 apos leitura) */
  }
}
