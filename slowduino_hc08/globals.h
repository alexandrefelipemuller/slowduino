/**
 * @file globals.h
 * @brief Estruturas de dados globais - port C puro (SDCC/HC08) da branch tiny
 *
 * Copia funcional de slowduino/globals.h (branch tiny), convertida para C99
 * (sem __attribute__((packed)) - HC08 nao precisa: nucleo 8-bit sem
 * requisito de alinhamento, cada campo ocupa exatamente seu tamanho).
 * Tamanhos conferidos com sizeof() no boot (ver main.c).
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <stdbool.h>

#define MICROS_PER_SEC 1000000UL
#define TEMP_OFFSET    40

struct Statuses {
  uint16_t RPM;
  bool     hasSync;
  uint16_t mapADC, tpsADC, cltADC, iatADC, o2ADC, batADC, oilPressADC, fuelPressADC;
  uint8_t  MAP, TPS;
  int8_t   coolant, IAT;
  uint8_t  O2, afrTarget, battery10, oilPressure, fuelPressure;
  uint16_t PW1, PW2, PW3;
  uint8_t  VE;
  uint16_t corrections;
  int8_t   advance;
  uint16_t dwell;
  uint8_t  wueCorrection, batCorrection;
  uint8_t  engineStatus, protectionStatus;
  bool     fanActive, fuelPumpActive;
  uint8_t  idleValveDuty;
  uint16_t CLIdleTarget;
  uint8_t  idleTaper;
  uint32_t secl, runSecs;
  int16_t  TPSdot;
  uint8_t  TPSlast;
};
extern struct Statuses currentStatus;

#define ENGINE_CRANK   0
#define ENGINE_RUN     1
#define ENGINE_ASE     2
#define ENGINE_WARMUP  3
#define ENGINE_ACC     4
#define ENGINE_DEC     5

struct ConfigPage1 {
  uint8_t  nCylinders;
  uint16_t reqFuel, injOpen;
  uint8_t  tpsMin, tpsMax, tpsFilter;
  uint8_t  mapMin, mapMax, mapFilter;
  uint8_t  wueBins[6], wueValues[6];
  uint8_t  asePct, aseCount;
  uint8_t  aeMode, aeThresh, aePct;
  uint8_t  primePulse;
  uint8_t  crankRPM;
  uint8_t  oilPressureProtEnable, oilPressureProtThreshold, oilPressureProtHysteresis, oilPressureProtDelay;
};
extern struct ConfigPage1 configPage1;

struct ConfigPage2 {
  uint8_t  triggerPattern, triggerTeeth, triggerMissing;
  uint16_t dwellRun, dwellCrank, dwellLimit;
  int8_t   crankAdvance;
  uint8_t  revLimitRPM;
  int8_t   cltAdvBins[4], cltAdvValues[4];
  uint8_t  ignInvert, triggerEdge;
  uint8_t  engineProtectEnable, engineProtectRPM, engineProtectRPMHysteresis;
  uint8_t  iacAlgorithm, idleFreq;
  int8_t   iacBins[4];
  uint8_t  iacOLPWMVal[4], iacCLValues[4];
  int8_t   iacCrankBins[4];
  uint8_t  iacCrankDuty[4];
  uint8_t  idleKP, idleKI, idleKD;
  uint8_t  iacCLminValue, iacCLmaxValue, idleTaperTime, iacTPSlimit;
  uint8_t  idleAdvEnabled, idleAdvTPS, idleAdvRPM;
  uint8_t  idleAdvBins[4];
  int8_t   idleAdvValues[4];
};
extern struct ConfigPage2 configPage2;

#define BIT_SET(var, bit)    ((var) |= (1 << (bit)))
#define BIT_CLEAR(var, bit)  ((var) &= ~(1 << (bit)))
#define BIT_CHECK(var, bit)  ((var) & (1 << (bit)))

/* Equivalente a noInterrupts()/interrupts() do Arduino core. ATENCAO: os
 * mnemonicos do HC08 tem o sentido "invertido" do nome AVR - SEI (Set
 * Interrupt mask) DESLIGA interrupcoes, CLI (Clear Interrupt mask) LIGA.
 * Estes wrappers existem exatamente para nao ter que lembrar disso em
 * cada call site (o codigo portado chama noInterrupts()/interrupts() com
 * o mesmo nome e semantica que tinha no AVR). */
static inline void noInterrupts(void) { __asm sei __endasm; }
static inline void interrupts(void)   { __asm cli __endasm; }

#endif /* GLOBALS_H */
