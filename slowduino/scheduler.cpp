/**
 * @file scheduler.cpp
 * @brief Implementação do sistema de scheduling
 */

#include "scheduler.h"

static const uint16_t IGNITION_MIN_DELAY_US = 25;  // Proteção contra eventos já vencidos

// Instancia schedules globais
volatile FuelSchedule fuelSchedule1 = {SCHED_OFF, 0, 0, 0, 1};
volatile FuelSchedule fuelSchedule2 = {SCHED_OFF, 0, 0, 0, 2};
volatile FuelSchedule fuelSchedule3 = {SCHED_OFF, 0, 0, 0, 3};
volatile IgnitionSchedule ignitionSchedule1 = {SCHED_OFF, 0, 0, 0, 1};
volatile IgnitionSchedule ignitionSchedule2 = {SCHED_OFF, 0, 0, 0, 2};

// ============================================================================
// INICIALIZAÇÃO
// ============================================================================

void schedulerInit() {
  // Configura pinos de saída
  pinMode(PIN_INJECTOR_1, OUTPUT);
  pinMode(PIN_INJECTOR_2, OUTPUT);
  pinMode(PIN_INJECTOR_3, OUTPUT);
  pinMode(PIN_IGNITION_1, OUTPUT);
  pinMode(PIN_IGNITION_2, OUTPUT);

  // Garante que tudo está desligado
  closeInjector1();
  closeInjector2();
  closeInjector3();
  endCoil1Charge();
  endCoil2Charge();

  // Configura Timer1
  setupTimer1();

  DEBUG_PRINTLN(F("Scheduler inicializado"));
}

void setupTimer1() {
  // Desliga timer durante configuração
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Modo Normal (contagem livre até overflow 0xFFFF)
  // WGM13:0 = 0000 → nenhum reset no compare, permite usar OCR1A/B como agendadores absolutos

  // Prescaler = 256
  // CS12:0 = 100
  // 16MHz / 256 = 62.5kHz -> 16us por tick (cobre cranking lento)
  TCCR1B |= (1 << CS12);

  // Valor inicial alto evita interrupção imediata antes do primeiro agendamento
  OCR1A = 0xFFFF;

  // Habilita interrupções de Compare Match para Channels A, B
  TIMSK1 |= (1 << OCIE1A);  // Compare Match A (usaremos para fuel/ign 1)
  TIMSK1 |= (1 << OCIE1B);  // Compare Match B (usaremos para fuel/ign 2)
}

// ============================================================================
// AGENDAMENTO DE INJEÇÃO
// ============================================================================

void setFuelSchedule(volatile FuelSchedule* schedule, uint16_t startTime, uint16_t duration, uint8_t channel) {
  // Proteção: Não agendar se schedule anterior ainda está RUNNING
  if (schedule->status == SCHED_RUNNING) {
    // Cancela schedule anterior
    clearFuelSchedule(schedule);
  }

  // Converte microsegundos para ticks do timer (× 2)
  uint16_t startTicks = US_TO_TIMER1(startTime);
  uint16_t durationTicks = US_TO_TIMER1(duration);

  // Calcula valores de compare
  uint16_t currentCount = TCNT1;
  schedule->startCompare = currentCount + startTicks;
  schedule->endCompare = schedule->startCompare + durationTicks;
  schedule->duration = durationTicks;
  schedule->channel = channel;
  schedule->status = SCHED_PENDING;

  // Configura compare register apropriado
  if (channel == 1 || channel == 3) {
    // Canais 1 e 3 compartilham OCR1A
    OCR1A = schedule->startCompare;
  } else {
    // Canal 2 usa OCR1B
    OCR1B = schedule->startCompare;
  }
}

void clearFuelSchedule(volatile FuelSchedule* schedule) {
  schedule->status = SCHED_OFF;

  // Fecha injetor se estava aberto
  if (schedule->channel == 1) {
    closeInjector1();
  } else if (schedule->channel == 2) {
    closeInjector2();
  } else if (schedule->channel == 3) {
    closeInjector3();
  }
}

// ============================================================================
// AGENDAMENTO DE IGNIÇÃO
// ============================================================================

void setIgnitionSchedule(volatile IgnitionSchedule* schedule, uint32_t startTime, uint16_t duration, uint8_t channel) {
  if (channel > BOARD_IGN_CHANNELS) {
    schedule->status = SCHED_OFF;
    return;
  }

  // Proteção: Não agendar se schedule anterior ainda está RUNNING
  if (schedule->status == SCHED_RUNNING) {
    // Cancela schedule anterior
    clearIgnitionSchedule(schedule);
  }

  if (startTime < IGNITION_MIN_DELAY_US) {
    schedule->status = SCHED_OFF;
    return;
  }

  uint32_t startTicks = US_TO_TIMER1(startTime);
  uint32_t durationTicks = US_TO_TIMER1(duration);
  if (durationTicks == 0) {
    durationTicks = 1;  // Garante pelo menos 1 tick
  }

  uint32_t totalTicks = startTicks + durationTicks;
  uint32_t minTicks = US_TO_TIMER1(IGNITION_MIN_DELAY_US);

  if (startTicks < minTicks) {
    startTicks = minTicks;
    if (totalTicks > startTicks) {
      durationTicks = totalTicks - startTicks;
    } else {
      durationTicks = 1;  // Sem janela suficiente → pulso mínimo
    }
  }

  uint16_t currentCount = TCNT1;
  uint16_t startTicks16 = (uint16_t)startTicks;
  uint16_t durationTicks16 = (uint16_t)durationTicks;

  schedule->startCompare = currentCount + startTicks16;
  schedule->endCompare = schedule->startCompare + durationTicks16;
  schedule->duration = durationTicks16;
  schedule->channel = channel;

  schedule->status = SCHED_PENDING;

  if (channel == 1) {
    // Canal 1 usa OCR1A
    OCR1A = schedule->startCompare;
  } else {
    // Canal 2 usa OCR1B
    OCR1B = schedule->startCompare;
  }
}

void clearIgnitionSchedule(volatile IgnitionSchedule* schedule) {
  schedule->status = SCHED_OFF;

  // Desliga bobina se estava carregando
  if (schedule->channel == 1) {
    endCoil1Charge();
  } else if (schedule->channel == 2) {
    endCoil2Charge();
  }
}

// ============================================================================
// INJEÇÃO VIA POLLING - Implementação
// ============================================================================

// Estados globais dos injetores
InjectorPollingState injector1Polling = {false, false, 0, 0};
InjectorPollingState injector2Polling = {false, false, 0, 0};
InjectorPollingState injector3Polling = {false, false, 0, 0};

void scheduleInjectorPolling(InjectorPollingState* injState, uint32_t startDelay, uint16_t pulseWidth) {
  uint32_t now = micros();
  injState->openTime = now + startDelay;
  injState->closeTime = injState->openTime + pulseWidth;
  injState->isScheduled = true;
  injState->isOpen = false;
}

void processInjectorPolling() {
  uint32_t now = micros();

  // Injector 1
  if (injector1Polling.isScheduled) {
    if (!injector1Polling.isOpen && now >= injector1Polling.openTime) {
      // Hora de abrir
      openInjector1();
      injector1Polling.isOpen = true;
    } else if (injector1Polling.isOpen && now >= injector1Polling.closeTime) {
      // Hora de fechar
      closeInjector1();
      injector1Polling.isOpen = false;
      injector1Polling.isScheduled = false;
    }
  }

  // Injector 2
  if (injector2Polling.isScheduled) {
    if (!injector2Polling.isOpen && now >= injector2Polling.openTime) {
      openInjector2();
      injector2Polling.isOpen = true;
    } else if (injector2Polling.isOpen && now >= injector2Polling.closeTime) {
      closeInjector2();
      injector2Polling.isOpen = false;
      injector2Polling.isScheduled = false;
    }
  }

  // Injector 3
  if (injector3Polling.isScheduled) {
    if (!injector3Polling.isOpen && now >= injector3Polling.openTime) {
      openInjector3();
      injector3Polling.isOpen = true;
    } else if (injector3Polling.isOpen && now >= injector3Polling.closeTime) {
      closeInjector3();
      injector3Polling.isOpen = false;
      injector3Polling.isScheduled = false;
    }
  }
}

// ============================================================================
// HELPERS PARA ISRs DE IGNIÇÃO
// ============================================================================

static inline void handleIgnitionChannel(volatile IgnitionSchedule* schedule,
                                         void (*beginCharge)(),
                                         void (*endCharge)(),
                                         volatile uint16_t* compareReg) {
  if (schedule->status == SCHED_PENDING) {
    schedule->status = SCHED_RUNNING;
    beginCharge();
    *compareReg = schedule->endCompare;
    return;
  }

  if (schedule->status == SCHED_RUNNING) {
    schedule->status = SCHED_OFF;
    endCharge();
    currentStatus.ignitionCount++;
  }
}

// ============================================================================
// ISRs DO TIMER1 - APENAS IGNIÇÃO (Alta Precisão)
// ============================================================================
// NOTA: Injeção agora é feita por polling no loop (precisão relaxada OK)
//       Ignição usa compare match (~±20µs após quantização de 16µs)

// ISR para Compare Match A (Ignition Channel 1)
ISR(TIMER1_COMPA_vect) {
  handleIgnitionChannel(&ignitionSchedule1, beginCoil1Charge, endCoil1Charge, &OCR1A);
}

// ISR para Compare Match B (Ignition Channel 2)
ISR(TIMER1_COMPB_vect) {
  handleIgnitionChannel(&ignitionSchedule2, beginCoil2Charge, endCoil2Charge, &OCR1B);
}
