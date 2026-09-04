/**
 * @file scheduler.h
 * @brief Scheduler de ignicao - port C/HC08 da branch tiny (scheduler.cpp)
 *
 * Mantem a MESMA logica/estrutura do AVR de proposito (nao simplificada
 * para "um timer por canal"), para preservar reversibilidade entre as
 * duas arquiteturas:
 *   - TIM1 canal 0 (T1CH0) ~ equivalente a OCR1A/Compare A no AVR (ignicao 1)
 *   - TIM1 canal 1 (T1CH1) ~ equivalente a OCR1B/Compare B no AVR (ignicao 2)
 *   - TIM2 fica livre (igual ao Timer2 do AVR, reservado pra IAC no futuro)
 *
 * PENDENCIAS EM ABERTO (nao adivinhadas - ver comentarios inline):
 *   - Config de MS0A/ELS0A ("software compare only") extraida da Table 17-3
 *     do datasheet, mas a leitura da tabela teve uma ambiguidade real -
 *     PRECISA ser validada no simulador antes de confiar que a interrupcao
 *     de compare realmente dispara.
 *   - Prescaler do TIM1 assume clock de barramento de 8MHz (mesma ressalva
 *     de timebase.h) - ajustar US_TO_TIMER1 se o clock real for diferente.
 *   - Mapeamento de pino das bobinas (PTA0/PTA1) e PLACEHOLDER - trocar
 *     pelos pinos reais da placa MS1/Slowduino-HC08 quando definidos.
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>
#include "mc68hc908gp32_sfr.h"

typedef enum { SCHED_OFF, SCHED_PENDING, SCHED_RUNNING } ScheduleStatus;

typedef struct {
  volatile ScheduleStatus status;
  volatile uint16_t startCompare;
  volatile uint16_t endCompare;
  volatile uint16_t duration;
  volatile uint8_t  channel;
} IgnitionSchedule;

extern volatile IgnitionSchedule ignitionSchedule1;
extern volatile IgnitionSchedule ignitionSchedule2;

/* 1 tick = 8us com prescaler /64 e bus clock de 8MHz (PLACEHOLDER, ver nota
 * acima). Equivalente ao US_TO_TIMER1 de scheduler.h no AVR (que da 16us). */
#define US_TO_TIMER1(us) ((uint16_t)((us) / 8))

void schedulerInit(void);

/* Mesma assinatura/semantica de setIgnitionSchedule()/clearIgnitionSchedule()
 * do AVR (scheduler.cpp da branch tiny) - startTime/duration em microsegundos. */
void setIgnitionSchedule(volatile IgnitionSchedule *schedule, uint32_t startTime,
                          uint16_t duration, uint8_t channel);
void clearIgnitionSchedule(volatile IgnitionSchedule *schedule);

static inline uint16_t getTimer1Count(void) {
  return (uint16_t)((T1CNTH << 8) | T1CNTL);
}

/* ==========================================================================
 * INJECAO VIA POLLING - identico ao scheduler.h/.c do AVR (branch tiny)
 * ========================================================================== */
typedef struct {
  bool isScheduled;
  bool isOpen;
  uint32_t openTime;
  uint32_t closeTime;
} InjectorPollingState;

extern InjectorPollingState injector1Polling;
extern InjectorPollingState injector2Polling;
extern InjectorPollingState injector3Polling;

void scheduleInjectorPolling(InjectorPollingState *injState, uint32_t startDelay, uint16_t pulseWidth);
void processInjectorPolling(void);

#endif /* SCHEDULER_H */
