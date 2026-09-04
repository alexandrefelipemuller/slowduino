/**
 * @file main.c
 * @brief Boot minimo do port Slowduino-HC08 - so pra validar a base
 *        (registradores, scheduler, timebase) compilando e rodando no
 *        simulador antes de portar decoders/fuel/comms.
 *
 * Nao tenta decodificar trigger ainda - agenda um pulso de ignicao
 * periodico artificial (a cada ~20ms) so para ter algo observavel via
 * GPIO (PTA0/PTA1) no simulador.
 */

#include "globals.h"
#include "scheduler.h"
#include "timebase.h"

int main(void) {
  timebaseInit();
  schedulerInit();

  __asm cli __endasm; /* habilita interrupcoes (equivalente a sei() do AVR) */

  currentStatus.RPM = 0;

  for (;;) {
    static uint32_t lastPulse = 0;
    uint32_t now = micros();

    if ((uint32_t)(now - lastPulse) >= 20000UL) {  /* ~50Hz, so para teste */
      lastPulse = now;
      setIgnitionSchedule(&ignitionSchedule1, 2000, 2500, 1);
      setIgnitionSchedule(&ignitionSchedule2, 2000, 2500, 2);
    }
  }

  return 0;
}
