/**
 * @file globals.cpp
 * @brief Instanciação de variáveis globais
 */

#include "globals.h"

// Instancia struct de status atual (RAM)
struct Statuses currentStatus;

// Instancia config pages (RAM, carregadas da EEPROM no boot)
struct ConfigPage1 configPage1;
struct ConfigPage2 configPage2;

// Flag de timer para controle de frequência do loop
volatile uint8_t loopTimerFlags = 0;
