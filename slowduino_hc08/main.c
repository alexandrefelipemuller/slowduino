/**
 * @file main.c
 * @brief Boot do port Slowduino-HC08 - decoder de trigger real conectado
 *
 * Ainda faltam fuel/comms/storage - configPage1/configPage2 ficam com os
 * valores zerados de boot (sem loadDefaults() nem protocolo Speeduino
 * ainda), entao RPM/PW/advance nao vao refletir um motor de verdade, mas
 * a cadeia trigger -> ISR -> scheduler ja fica completa e testavel.
 */

#include "globals.h"
#include "scheduler.h"
#include "decoders.h"
#include "timebase.h"

int main(void) {
  timebaseInit();
  schedulerInit();
  triggerInit();

  interrupts();

  for (;;) {
    static uint32_t lastLoop67Hz = 0;
    uint32_t now = micros();

    /* Mesma cadencia de calculateRPM()/checkSyncLoss() do loop() no AVR
     * (~67ms, ver CLAUDE.md) - aqui feito por tempo decorrido em vez de
     * time-slicing por millis() (ainda nao portado). */
    if ((uint32_t)(now - lastLoop67Hz) >= 67000UL) {
      lastLoop67Hz = now;
      calculateRPM();
      checkSyncLoss();
    }
  }

  return 0;
}
