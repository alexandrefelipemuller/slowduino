/**
 * @file fuel.h
 * @brief Calculos de injecao - port C/HC08 da branch tiny (fuel.h)
 */

#ifndef FUEL_H
#define FUEL_H

#include <stdint.h>

uint16_t calculateInjection(void);
uint8_t  getVE(void);
uint16_t calculateCorrections(void);

uint8_t correctionWUE(void);
uint8_t correctionASE(void);
uint8_t correctionAE(void);
uint8_t correctionCLT(void);
uint8_t correctionBattery(void);

void updateEngineStatus(void);
void startASE(void);
void decrementASE(void);

#endif /* FUEL_H */
