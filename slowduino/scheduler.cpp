/**
 * @file scheduler.cpp
 * @brief Implementação do sistema de scheduling
 */

#include "scheduler.h"

#if !defined(__AVR__)
#include <HardwareTimer.h>
#endif

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

#if defined(__AVR__)

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

#else

// ============================================================================
// PORTE STM32: "Timer1" implementado em cima de um HardwareTimer de 16 bits
// ============================================================================
// TIM2 no F103 é alimentado a 72MHz (clock APB1 x2). Prescaler 1152 dá
// 72MHz/1152 = 62.5kHz -> 16us/tick, EXATAMENTE o mesmo tick do AVR (ver
// US_TO_TIMER1 em config.h), então nenhum outro arquivo precisa mudar.
// Os canais 1 e 2 do TIM2 são usados em modo "Output Compare" sem pino
// associado (NC) - servem só para gerar interrupção de compare, igual
// OCR1A/OCR1B no AVR. O contador roda livre (não reseta no compare, igual
// modo Normal do AVR) porque não usamos PWM/reset-on-match.
static HardwareTimer schedTimer(TIM2);

static void schedTimerCompareA_ISR();
static void schedTimerCompareB_ISR();

void setupTimer1() {
  schedTimer.pause();
  schedTimer.setPrescaleFactor(1152);
  schedTimer.setOverflow(0x10000, TICK_FORMAT);  // wrap em 65536 ticks (16 bits)

  schedTimer.setMode(1, TIMER_OUTPUT_COMPARE, NC);
  schedTimer.setMode(2, TIMER_OUTPUT_COMPARE, NC);
  schedTimer.setCaptureCompare(1, 0xFFFF, TICK_COMPARE_FORMAT);
  schedTimer.setCaptureCompare(2, 0xFFFF, TICK_COMPARE_FORMAT);
  schedTimer.attachInterrupt(1, schedTimerCompareA_ISR);
  schedTimer.attachInterrupt(2, schedTimerCompareB_ISR);

  schedTimer.refresh();
  schedTimer.resume();
}

uint16_t getTimer1Count() {
  return (uint16_t)schedTimer.getCount(TICK_FORMAT);
}

void setTimer1CompareA(uint16_t value) {
  schedTimer.setCaptureCompare(1, value, TICK_COMPARE_FORMAT);
}

void setTimer1CompareB(uint16_t value) {
  schedTimer.setCaptureCompare(2, value, TICK_COMPARE_FORMAT);
}

#endif

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
  uint16_t currentCount = getTimer1Count();
  schedule->startCompare = currentCount + startTicks;
  schedule->endCompare = schedule->startCompare + durationTicks;
  schedule->duration = durationTicks;
  schedule->channel = channel;
  schedule->status = SCHED_PENDING;

  // Configura compare register apropriado
  if (channel == 1 || channel == 3) {
    // Canais 1 e 3 compartilham o compare A
    setTimer1CompareA(schedule->startCompare);
  } else {
    // Canal 2 usa o compare B
    setTimer1CompareB(schedule->startCompare);
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
// HELPERS PARA ISRs DE IGNIÇÃO
// ============================================================================

// NOTA: setCompare é um ponteiro de função (setTimer1CompareA/B) em vez de
// um ponteiro cru para o registrador (OCR1A/OCR1B) - isso é o que permite
// esta lógica ser idêntica no AVR e no porte STM32 (scheduler.h expõe as
// mesmas duas funções nos dois casos).
static inline void handleIgnitionChannel(volatile IgnitionSchedule* schedule,
                                         void (*beginCharge)(),
                                         void (*endCharge)(),
                                         void (*setCompare)(uint16_t)) {
  if (schedule->status == SCHED_PENDING) {
    schedule->status = SCHED_RUNNING;
    beginCharge();
    setCompare(schedule->endCompare);

    // Mesma corrida do wraparound documentada em armIgnitionCompare(), mas
    // no fim do dwell: se o contador já passou de endCompare quando
    // escrevemos o compare, o match só dispararia ~1s depois (volta do
    // contador de 16 bits), deixando a bobina carregando esse tempo todo.
    if ((int16_t)(getTimer1Count() - schedule->endCompare) >= 0) {
      schedule->status = SCHED_OFF;
      endCharge();
    }
    return;
  }

  if (schedule->status == SCHED_RUNNING) {
    schedule->status = SCHED_OFF;
    endCharge();
  }
}

// Timer1 (ou seu equivalente no porte) roda livre (free-running, não reseta
// no compare match). Entre calcular startCompare e escrever o compare, o
// contador pode já ter avançado além do alvo (ex: interrupções atrasadas).
// Se isso acontecer, o compare match só dispararia ~1s depois, na próxima
// volta do contador de 16 bits, perdendo o evento de ignição. Detecta a
// corrida e processa na hora.
static inline void armIgnitionCompare(volatile IgnitionSchedule* schedule,
                                      void (*beginCharge)(),
                                      void (*endCharge)(),
                                      void (*setCompare)(uint16_t)) {
  setCompare(schedule->startCompare);

  // Cast para int16_t faz a subtração respeitar o wraparound do contador
  if ((int16_t)(getTimer1Count() - schedule->startCompare) >= 0) {
    handleIgnitionChannel(schedule, beginCharge, endCharge, setCompare);
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

  // NOTA: startTime pequeno demais (ex: 0, quando o dwell não cabe antes do
  // ângulo de faísca) NÃO deve descartar o evento - o clamp abaixo
  // (startTicks < minTicks) já resolve isso disparando o dwell no menor
  // atraso seguro, com duração proporcionalmente reduzida se preciso.
  // Descartar aqui apagava a faísca inteira nesses casos.

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

  uint16_t currentCount = getTimer1Count();
  uint16_t startTicks16 = (uint16_t)startTicks;
  uint16_t durationTicks16 = (uint16_t)durationTicks;

  schedule->startCompare = currentCount + startTicks16;
  schedule->endCompare = schedule->startCompare + durationTicks16;
  schedule->duration = durationTicks16;
  schedule->channel = channel;

  schedule->status = SCHED_PENDING;

  if (channel == 1) {
    // Canal 1 usa o compare A
    armIgnitionCompare(schedule, beginCoil1Charge, endCoil1Charge, setTimer1CompareA);
  } else {
    // Canal 2 usa o compare B
    armIgnitionCompare(schedule, beginCoil2Charge, endCoil2Charge, setTimer1CompareB);
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
// ISRs DO TIMER1 - APENAS IGNIÇÃO (Alta Precisão)
// ============================================================================
// NOTA: Injeção agora é feita por polling no loop (precisão relaxada OK)
//       Ignição usa compare match (~±20µs após quantização de 16µs)

#if defined(__AVR__)

// ISR para Compare Match A (Ignition Channel 1)
ISR(TIMER1_COMPA_vect) {
  handleIgnitionChannel(&ignitionSchedule1, beginCoil1Charge, endCoil1Charge, setTimer1CompareA);
}

// ISR para Compare Match B (Ignition Channel 2)
ISR(TIMER1_COMPB_vect) {
  handleIgnitionChannel(&ignitionSchedule2, beginCoil2Charge, endCoil2Charge, setTimer1CompareB);
}

#else

// Equivalentes no porte STM32 (chamadas pelo HardwareTimer, anexadas em
// setupTimer1() acima).
static void schedTimerCompareA_ISR() {
  handleIgnitionChannel(&ignitionSchedule1, beginCoil1Charge, endCoil1Charge, setTimer1CompareA);
}

static void schedTimerCompareB_ISR() {
  handleIgnitionChannel(&ignitionSchedule2, beginCoil2Charge, endCoil2Charge, setTimer1CompareB);
}

#endif
