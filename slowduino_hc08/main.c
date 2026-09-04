/**
 * @file main.c
 * @brief Boot do port Slowduino-HC08 - trigger + fuel + tables conectados
 *
 * Ainda faltam comms (protocolo Speeduino) e storage real (GP32 nao tem
 * EEPROM - ver storage.h) e ignition.c (avanco/dwell, hoje currentStatus.
 * advance/dwell ficam zerados de boot). getVE()/calculateInjection() ja
 * rodam de ponta a ponta, so que sobre dados de tabela placeholder.
 */

#include "globals.h"
#include "scheduler.h"
#include "decoders.h"
#include "timebase.h"
#include "tables.h"
#include "fuel.h"

int main(void) {
  timebaseInit();
  schedulerInit();
  initTables();
  triggerInit();

  interrupts();

  for (;;) {
    static uint32_t lastLoop67Hz = 0;
    uint32_t now = micros();

    /* Alta prioridade - mesma posicao que tem no loop() do AVR */
    processInjectorPolling();

    if ((uint32_t)(now - lastLoop67Hz) >= 67000UL) {
      lastLoop67Hz = now;
      calculateRPM();
      checkSyncLoss();
      updateEngineStatus();

      if (currentStatus.hasSync && currentStatus.RPM > 0) {
        calculateInjection();
      }
    }
  }

  return 0;
}
