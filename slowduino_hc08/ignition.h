/**
 * @file ignition.h
 * @brief Calculos de ignicao (avanco e dwell) - port C/HC08 da branch tiny
 */

#ifndef IGNITION_H
#define IGNITION_H

#include <stdint.h>
#include <stdbool.h>

int8_t   calculateAdvance(void);
uint16_t calculateDwell(void);

int8_t getBaseAdvance(void);
int8_t applyAdvanceCorrections(int8_t baseAdvance);
int8_t correctionCLTAdvance(void);
bool   isIdleAdvanceActive(void);
int8_t correctionIdleAdvance(void);
int8_t applyRevLimiter(int8_t advance);

#endif /* IGNITION_H */
