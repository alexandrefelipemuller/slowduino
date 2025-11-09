/**
 * @file scheduler.cpp
 * @brief Implementação do sistema de scheduling
 */

#include "scheduler.h"

// Instancia schedules globais
volatile FuelSchedule fuelSchedule1 = {SCHED_OFF, 0, 0, 0, 1};
volatile FuelSchedule fuelSchedule2 = {SCHED_OFF, 0, 0, 0, 2};
volatile FuelSchedule fuelSchedule3 = {SCHED_OFF, 0, 0, 0, 3};
volatile IgnitionSchedule ignitionSchedule1 = {SCHED_OFF, 0, 0, 0, 1};
volatile IgnitionSchedule ignitionSchedule2 = {SCHED_OFF, 0, 0, 0, 2};
volatile IgnitionSchedule ignitionSchedule3 = {SCHED_OFF, 0, 0, 0, 3};

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
  pinMode(PIN_IGNITION_3, OUTPUT);

  // Garante que tudo está desligado
  closeInjector1();
  closeInjector2();
  closeInjector3();
  endCoil1Charge();
  endCoil2Charge();
  endCoil3Charge();

  // Configura Timer1
  setupTimer1();

  DEBUG_PRINTLN(F("Scheduler inicializado"));
}

void setupTimer1() {
  // Desliga timer durante configuração
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Modo CTC (Clear Timer on Compare Match) com TOP em OCR1A
  // WGM13:0 = 0100 (CTC, TOP = OCR1A)
  TCCR1B |= (1 << WGM12);

  // Prescaler = 8
  // CS12:0 = 010
  // 16MHz / 8 = 2MHz -> 0.5us por tick
  TCCR1B |= (1 << CS11);

  // TOP value alto para não resetar contador (queremos free-running)
  OCR1A = 0xFFFF;

  // Habilita interrupções de Compare Match para Channels A, B
  TIMSK1 |= (1 << OCIE1A);  // Compare Match A (usaremos para fuel/ign 1)
  TIMSK1 |= (1 << OCIE1B);  // Compare Match B (usaremos para fuel/ign 2)
}

// ============================================================================
// AGENDAMENTO DE INJEÇÃO
// ============================================================================

void setFuelSchedule(volatile FuelSchedule* schedule, uint16_t startTime, uint16_t duration, uint8_t channel) {
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
  if (channel == 1) {
    OCR1A = schedule->startCompare;
  } else {
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

void setIgnitionSchedule(volatile IgnitionSchedule* schedule, uint16_t startTime, uint16_t duration, uint8_t channel) {
  uint16_t startTicks = US_TO_TIMER1(startTime);
  uint16_t durationTicks = US_TO_TIMER1(duration);

  uint16_t currentCount = TCNT1;
  schedule->startCompare = currentCount + startTicks;
  schedule->endCompare = schedule->startCompare + durationTicks;
  schedule->duration = durationTicks;
  schedule->channel = channel;
  schedule->status = SCHED_PENDING;

  // Nota: Ignição compartilha compare registers com fuel
  // Channel 1 usa OCR1A, Channel 2 usa OCR1B
  // ISR precisa distinguir entre fuel e ignition

  if (channel == 1) {
    OCR1A = schedule->startCompare;
  } else {
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
  } else if (schedule->channel == 3) {
    endCoil3Charge();
  }
}

// ============================================================================
// ISRs DO TIMER1
// ============================================================================

// ISR para Compare Match A (Fuel/Ign Channel 1 e 3)
ISR(TIMER1_COMPA_vect) {
  // CRÍTICO: Fuel e Ignition compartilham o mesmo compare register (OCR1A)
  // Prioridade: Fuel1 > Fuel3 > Ign1 > Ign3 (injeção tem precedência)

  // Processa Fuel Schedule 1
  if (fuelSchedule1.status == SCHED_PENDING) {
    // Inicia injeção
    fuelSchedule1.status = SCHED_RUNNING;
    openInjector1();

    // Agenda fim da injeção
    OCR1A = fuelSchedule1.endCompare;
    return;

  } else if (fuelSchedule1.status == SCHED_RUNNING) {
    // Termina injeção
    fuelSchedule1.status = SCHED_OFF;
    closeInjector1();

    // Verifica se há fuel3 pendente
    if (fuelSchedule3.status == SCHED_PENDING) {
      uint16_t now = TCNT1;
      if (fuelSchedule3.startCompare > now) {
        OCR1A = fuelSchedule3.startCompare;
      } else {
        fuelSchedule3.status = SCHED_RUNNING;
        openInjector3();
        OCR1A = fuelSchedule3.endCompare;
      }
      return;
    }

    // Se ignição está pendente, agenda agora
    if (ignitionSchedule1.status == SCHED_PENDING) {
      uint16_t now = TCNT1;
      if (ignitionSchedule1.startCompare > now) {
        OCR1A = ignitionSchedule1.startCompare;
      } else {
        // Já passou o timing, executa imediatamente
        ignitionSchedule1.status = SCHED_RUNNING;
        beginCoil1Charge();
        OCR1A = ignitionSchedule1.endCompare;
      }
    }
    return;
  }

  // Processa Fuel Schedule 3 (compartilha OCR1A)
  if (fuelSchedule3.status == SCHED_PENDING) {
    fuelSchedule3.status = SCHED_RUNNING;
    openInjector3();
    OCR1A = fuelSchedule3.endCompare;
    return;

  } else if (fuelSchedule3.status == SCHED_RUNNING) {
    fuelSchedule3.status = SCHED_OFF;
    closeInjector3();

    // Se ignição 1 ou 3 está pendente, agenda
    if (ignitionSchedule1.status == SCHED_PENDING) {
      uint16_t now = TCNT1;
      if (ignitionSchedule1.startCompare > now) {
        OCR1A = ignitionSchedule1.startCompare;
      } else {
        ignitionSchedule1.status = SCHED_RUNNING;
        beginCoil1Charge();
        OCR1A = ignitionSchedule1.endCompare;
      }
      return;
    }
    if (ignitionSchedule3.status == SCHED_PENDING) {
      uint16_t now = TCNT1;
      if (ignitionSchedule3.startCompare > now) {
        OCR1A = ignitionSchedule3.startCompare;
      } else {
        ignitionSchedule3.status = SCHED_RUNNING;
        beginCoil3Charge();
        OCR1A = ignitionSchedule3.endCompare;
      }
    }
    return;
  }

  // Processa Ignition Schedule 1 (apenas se fuel não estiver ativo)
  if (ignitionSchedule1.status == SCHED_PENDING) {
    // Inicia dwell
    ignitionSchedule1.status = SCHED_RUNNING;
    beginCoil1Charge();

    // Agenda faísca
    OCR1A = ignitionSchedule1.endCompare;

  } else if (ignitionSchedule1.status == SCHED_RUNNING) {
    // Faísca!
    ignitionSchedule1.status = SCHED_OFF;
    endCoil1Charge();

    // Incrementa contador de ignições
    currentStatus.ignitionCount++;

    // Verifica se ign3 está pendente
    if (ignitionSchedule3.status == SCHED_PENDING) {
      uint16_t now = TCNT1;
      if (ignitionSchedule3.startCompare > now) {
        OCR1A = ignitionSchedule3.startCompare;
      } else {
        ignitionSchedule3.status = SCHED_RUNNING;
        beginCoil3Charge();
        OCR1A = ignitionSchedule3.endCompare;
      }
    }
    return;
  }

  // Processa Ignition Schedule 3
  if (ignitionSchedule3.status == SCHED_PENDING) {
    ignitionSchedule3.status = SCHED_RUNNING;
    beginCoil3Charge();
    OCR1A = ignitionSchedule3.endCompare;

  } else if (ignitionSchedule3.status == SCHED_RUNNING) {
    ignitionSchedule3.status = SCHED_OFF;
    endCoil3Charge();
    currentStatus.ignitionCount++;
  }
}

// ISR para Compare Match B (Fuel/Ign Channel 2)
ISR(TIMER1_COMPB_vect) {
  // CRÍTICO: Mesma lógica do Channel A
  // Prioridade: Fuel > Ignition

  // Processa Fuel Schedule 2
  if (fuelSchedule2.status == SCHED_PENDING) {
    // Inicia injeção
    fuelSchedule2.status = SCHED_RUNNING;
    openInjector2();

    // Agenda fim da injeção
    OCR1B = fuelSchedule2.endCompare;
    return;  // Ignição aguarda próximo ciclo

  } else if (fuelSchedule2.status == SCHED_RUNNING) {
    // Termina injeção
    fuelSchedule2.status = SCHED_OFF;
    closeInjector2();

    // Se ignição está pendente, agenda agora
    if (ignitionSchedule2.status == SCHED_PENDING) {
      uint16_t now = TCNT1;
      if (ignitionSchedule2.startCompare > now) {
        OCR1B = ignitionSchedule2.startCompare;
      } else {
        // Já passou o timing, executa imediatamente
        ignitionSchedule2.status = SCHED_RUNNING;
        beginCoil2Charge();
        OCR1B = ignitionSchedule2.endCompare;
      }
    }
    return;
  }

  // Processa Ignition Schedule 2 (apenas se fuel não estiver ativo)
  if (ignitionSchedule2.status == SCHED_PENDING) {
    // Inicia dwell
    ignitionSchedule2.status = SCHED_RUNNING;
    beginCoil2Charge();

    // Agenda faísca
    OCR1B = ignitionSchedule2.endCompare;

  } else if (ignitionSchedule2.status == SCHED_RUNNING) {
    // Faísca!
    ignitionSchedule2.status = SCHED_OFF;
    endCoil2Charge();

    // Incrementa contador de ignições
    currentStatus.ignitionCount++;
  }
}
