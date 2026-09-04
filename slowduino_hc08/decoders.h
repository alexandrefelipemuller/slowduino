/**
 * @file decoders.h
 * @brief Decoders de trigger wheel - port C/HC08 da branch tiny
 *
 * DIFERENCA DE HARDWARE REAL (nao e so troca de registrador):
 * o AVR usa attachInterrupt() em INT0, que suporta RISING/FALLING/CHANGE.
 * O pino dedicado IRQ do GP32 (cap. 9 do datasheet) SO detecta borda de
 * DESCIDA (MODE=0) ou descida+nivel baixo (MODE=1) - nao existe RISING nem
 * CHANGE nesse pino. Por isso:
 *   - configPage2.triggerEdge = FALLING -> suportado (MODE=0)
 *   - RISING ou BOTH (CHANGE)           -> NAO suportado no pino IRQ.
 *     Precisaria investigar o modulo KBI (Keyboard Interrupt, cap. 10,
 *     Port A) como alternativa - NAO feito ainda, nao adivinhar.
 * Isso significa: triggerEdgesPerTooth so cobre o caso de 1 borda por
 * dente aqui (o caso de 2 bordas/dente do CHANGE do AVR nao se aplica).
 */

#ifndef DECODERS_H
#define DECODERS_H

#include <stdint.h>
#include <stdbool.h>

struct TriggerState {
  volatile uint32_t toothLastToothTime;
  volatile uint32_t toothLastMinusOneTime;
  volatile uint32_t revolutionTime;
  volatile uint32_t toothOneTime;

  volatile uint8_t toothCurrentCount;
  volatile uint8_t toothTotalCount;
  volatile uint8_t triggerActualTeeth;

  volatile uint32_t curGap;
  volatile uint32_t lastGap;
  volatile bool     hasSync;
  volatile uint8_t  syncLossCounter;

  volatile uint16_t RPM;
  volatile uint32_t toothPeriod;

  uint8_t  triggerTeeth;
  uint8_t  triggerMissing;
  uint16_t triggerFilterTime;
  uint16_t toothAngle;
};

extern volatile struct TriggerState triggerState;
extern volatile uint8_t revolutionCounter;

void triggerInit(void);
void triggerSetup_MissingTooth(void);
void triggerSetup_BasicDistributor(void);

void calculateRPM(void);
void checkSyncLoss(void);

uint32_t angleToTime(uint16_t angle);
uint16_t timeToAngle(uint32_t time);
uint16_t getCrankAngle(void);

void attachTriggerInterrupt(void);
void resetTriggerState(void);

#endif /* DECODERS_H */
