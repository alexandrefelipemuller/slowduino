/**
 * @file scheduler.h
 * @brief Sistema de agendamento de eventos de injeção e ignição
 *
 * Usa Timer1 (16-bit) para agendar aberturas/fechamentos de injetores
 * e carga/descarga de bobinas com precisão de microsegundos
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>
#include "globals.h"
#include "config.h"

// ============================================================================
// ESTRUTURAS DE SCHEDULE
// ============================================================================

enum ScheduleStatus {
  SCHED_OFF,       // Inativo
  SCHED_PENDING,   // Agendado, aguardando início
  SCHED_RUNNING    // Em execução
};

struct FuelSchedule {
  volatile ScheduleStatus status;
  volatile uint16_t startCompare;     // Valor OCR para início
  volatile uint16_t endCompare;       // Valor OCR para fim
  volatile uint16_t duration;         // Duração em ticks do timer
  volatile uint8_t channel;           // Canal (1 ou 2)
};

struct IgnitionSchedule {
  volatile ScheduleStatus status;
  volatile uint16_t startCompare;     // Início do dwell (carga)
  volatile uint16_t endCompare;       // Fim do dwell (faísca)
  volatile uint16_t duration;         // Duração do dwell em ticks
  volatile uint8_t channel;           // Canal (1 ou 2)
};

// Schedules globais
extern volatile FuelSchedule fuelSchedule1;
extern volatile FuelSchedule fuelSchedule2;
extern volatile IgnitionSchedule ignitionSchedule1;
extern volatile IgnitionSchedule ignitionSchedule2;

// ============================================================================
// FUNÇÕES DE INICIALIZAÇÃO
// ============================================================================

/**
 * @brief Inicializa sistema de scheduler
 *
 * Configura Timer1 e pinos de saída
 */
void schedulerInit();

/**
 * @brief Configura Timer1 para scheduler
 *
 * Modo CTC, prescaler 8 (0.5us por tick)
 * Habilita interrupções de Compare Match
 */
void setupTimer1();

// ============================================================================
// FUNÇÕES DE AGENDAMENTO DE INJEÇÃO
// ============================================================================

/**
 * @brief Agenda evento de injeção
 *
 * @param schedule Ponteiro para struct de schedule
 * @param startTime Tempo de início (microsegundos a partir de agora)
 * @param duration Duração da injeção (microsegundos)
 * @param channel Canal do injetor (1 ou 2)
 */
void setFuelSchedule(volatile FuelSchedule* schedule, uint16_t startTime, uint16_t duration, uint8_t channel);

/**
 * @brief Cancela schedule de injeção
 */
void clearFuelSchedule(volatile FuelSchedule* schedule);

// ============================================================================
// FUNÇÕES DE AGENDAMENTO DE IGNIÇÃO
// ============================================================================

/**
 * @brief Agenda evento de ignição
 *
 * @param schedule Ponteiro para struct de schedule
 * @param startTime Tempo para iniciar dwell (microsegundos a partir de agora)
 * @param duration Duração do dwell (microsegundos)
 * @param channel Canal da bobina (1 ou 2)
 */
void setIgnitionSchedule(volatile IgnitionSchedule* schedule, uint16_t startTime, uint16_t duration, uint8_t channel);

/**
 * @brief Cancela schedule de ignição
 */
void clearIgnitionSchedule(volatile IgnitionSchedule* schedule);

// ============================================================================
// CONTROLE DE INJETORES (DIRETO)
// ============================================================================

/**
 * @brief Abre injetor 1
 */
inline void openInjector1() {
  digitalWrite(PIN_INJECTOR_1, HIGH);
}

/**
 * @brief Fecha injetor 1
 */
inline void closeInjector1() {
  digitalWrite(PIN_INJECTOR_1, LOW);
}

/**
 * @brief Abre injetor 2
 */
inline void openInjector2() {
  digitalWrite(PIN_INJECTOR_2, HIGH);
}

/**
 * @brief Fecha injetor 2
 */
inline void closeInjector2() {
  digitalWrite(PIN_INJECTOR_2, LOW);
}

// ============================================================================
// CONTROLE DE IGNIÇÃO (DIRETO)
// ============================================================================

/**
 * @brief Inicia carga da bobina 1 (dwell)
 */
inline void beginCoil1Charge() {
  if (configPage2.ignInvert) {
    digitalWrite(PIN_IGNITION_1, LOW);   // Invertido
  } else {
    digitalWrite(PIN_IGNITION_1, HIGH);  // Normal
  }
}

/**
 * @brief Termina carga da bobina 1 (faísca)
 */
inline void endCoil1Charge() {
  if (configPage2.ignInvert) {
    digitalWrite(PIN_IGNITION_1, HIGH);
  } else {
    digitalWrite(PIN_IGNITION_1, LOW);
  }
}

/**
 * @brief Inicia carga da bobina 2
 */
inline void beginCoil2Charge() {
  if (configPage2.ignInvert) {
    digitalWrite(PIN_IGNITION_2, LOW);
  } else {
    digitalWrite(PIN_IGNITION_2, HIGH);
  }
}

/**
 * @brief Termina carga da bobina 2
 */
inline void endCoil2Charge() {
  if (configPage2.ignInvert) {
    digitalWrite(PIN_IGNITION_2, HIGH);
  } else {
    digitalWrite(PIN_IGNITION_2, LOW);
  }
}

// ============================================================================
// UTILITÁRIOS
// ============================================================================

/**
 * @brief Retorna contador atual do Timer1
 */
inline uint16_t getTimer1Count() {
  return TCNT1;
}

/**
 * @brief Define valor de compare do Timer1 Channel A
 */
inline void setTimer1CompareA(uint16_t value) {
  OCR1A = value;
}

/**
 * @brief Define valor de compare do Timer1 Channel B
 */
inline void setTimer1CompareB(uint16_t value) {
  OCR1B = value;
}

#endif // SCHEDULER_H
