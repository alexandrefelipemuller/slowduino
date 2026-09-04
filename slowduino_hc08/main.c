/**
 * @file main.c
 * @brief Boot do port Slowduino-HC08 - trigger + fuel + tables + ignition
 *
 * Ainda falta comms (protocolo Speeduino via SCI) e storage real (ver
 * storage.h). Sem comms, configPage1/configPage2 ficam com os valores
 * zerados de boot (sem loadDefaults() nem TunerStudio ainda).
 */

#include "globals.h"
#include "scheduler.h"
#include "decoders.h"
#include "timebase.h"
#include "tables.h"
#include "fuel.h"
#include "ignition.h"
#include "comms.h"

int main(void) {
  timebaseInit();
  schedulerInit();
  initTables();
  triggerInit();
  commsInit();

  interrupts();

  for (;;) {
    static uint32_t lastLoop67Hz = 0;
    uint32_t now = micros();

    /* Maxima prioridade - mesma posicao que tem no loop() do AVR */
    commsProcess();

    /* Alta prioridade - mesma posicao que tem no loop() do AVR */
    processInjectorPolling();

    if ((uint32_t)(now - lastLoop67Hz) >= 67000UL) {
      lastLoop67Hz = now;
      calculateRPM();
      checkSyncLoss();
      updateEngineStatus();

      if (currentStatus.hasSync && currentStatus.RPM > 0) {
        /* Calcula fora da secao critica (pode ser custoso) e so entao
         * publica - PW1/advance/dwell sao lidos direto pela ISR do
         * trigger (scheduleInjectionISR/scheduleIgnitionISR em
         * decoders.c), mesma protecao de atomicidade que o AVR usa. */
        uint16_t newPW1 = calculateInjection();
        int8_t newAdvance = calculateAdvance();
        uint16_t newDwell = calculateDwell();

        noInterrupts();
        currentStatus.PW1 = newPW1;
        currentStatus.PW2 = newPW1;
        currentStatus.advance = newAdvance;
        currentStatus.dwell = newDwell;
        interrupts();
      }
    }
  }

  return 0;
}
