#ifndef PROTECTIONS_H
#define PROTECTIONS_H

#include "../data/globals.h"

#define CUT_FUEL_BIT 0x01
#define CUT_IGN_BIT  0x02

extern volatile uint8_t cutPercent;   // 0-100, calculado no loop

void protectionProcess();
uint8_t protectionCutEvent(uint8_t ch);   // ISR: máscara de corte do evento
bool protectionRPMActive();
bool protectionOilActive();

#endif // PROTECTIONS_H
