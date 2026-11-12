/**
 * @file board_config.h
 * @brief Configurações de hardware específicas por placa
 *
 * Define pinagem e recursos disponíveis para diferentes placas:
 * - Arduino Uno/Nano (ATmega328p) - pinagem original Slowduino
 * - Speeduino v0.4 (Arduino Mega) - pinagem compatível com hardware oficial
 */

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <Arduino.h>

// ============================================================================
// SELEÇÃO DE HARDWARE
// ============================================================================
//
// Descomente UMA das opções abaixo, OU defina via build flag do compilador
// (ex: "-DBOARD_SPEEDUINO_V04") sem tocar neste arquivo.
//
// Guardado com #ifndef para um -DBOARD_SPEEDUINO_V04 externo funcionar sem
// também deixar BOARD_SLOWDUINO definido ao mesmo tempo.
#if !defined(BOARD_SPEEDUINO_V04) && !defined(BOARD_STM32_BLUEPILL)
#define BOARD_SLOWDUINO      // Arduino Uno/Nano (padrão, 2 canais, 1-4 cilindros)
#endif
//#define BOARD_SPEEDUINO_V04  // Speeduino v0.4 (Arduino Mega, 4 canais, 1-8 cilindros)
//#define BOARD_STM32_BLUEPILL // STM32F103C8T6 "Blue Pill" (2 canais, 1-4 cilindros)

// ============================================================================
// DETECÇÃO AUTOMÁTICA DE PLACA (se nenhuma foi definida)
// ============================================================================
#if !defined(BOARD_SLOWDUINO) && !defined(BOARD_SPEEDUINO_V04) && !defined(BOARD_STM32_BLUEPILL)
  // Default para Arduino Uno/Nano
  #define BOARD_SLOWDUINO
#endif

// ============================================================================
// VALIDAÇÃO DE PLATAFORMA
// ============================================================================
#if defined(BOARD_SPEEDUINO_V04)
  // Speeduino v0.4 REQUER Arduino Mega (ATmega2560)
  #if !defined(__AVR_ATmega2560__) && !defined(__AVR_ATmega1280__)
    #error "BOARD_SPEEDUINO_V04 requer Arduino Mega (ATmega2560/1280)"
  #endif
#endif

#if defined(BOARD_SLOWDUINO)
  // Slowduino REQUER Arduino Uno/Nano (ATmega328p)
  #if !defined(__AVR_ATmega328P__) && !defined(__AVR_ATmega168__)
    #warning "BOARD_SLOWDUINO otimizado para ATmega328p/168 (Uno/Nano)"
  #endif
#endif

#if defined(BOARD_STM32_BLUEPILL)
  #if !defined(STM32F1xx) && !defined(ARDUINO_ARCH_STM32)
    #error "BOARD_STM32_BLUEPILL requer o core Arduino_Core_STM32 (platform ststm32)"
  #endif
#endif

// ============================================================================
// PINAGEM E CAPACIDADES DA PLACA SELECIONADA
// ============================================================================
#if defined(BOARD_SPEEDUINO_V04)
  #include "board_speeduino_v04.h"
#elif defined(BOARD_SLOWDUINO)
  #include "board_uno.h"
#elif defined(BOARD_STM32_BLUEPILL)
  #include "board_bluepill.h"
#endif

// ============================================================================
// CONFIGURAÇÕES DERIVADAS
// ============================================================================

// Define número de canais disponíveis (sempre 3 no firmware Slowduino)
#if !defined(BOARD_INJ_CHANNELS) || !defined(BOARD_IGN_CHANNELS)
  #error "BOARD_INJ_CHANNELS e BOARD_IGN_CHANNELS devem ser definidos pela placa selecionada"
#endif

// ============================================================================
// INFORMAÇÕES DE DEBUG
// ============================================================================

// Macro para imprimir informações da placa no boot
#define PRINT_BOARD_INFO() \
  do { \
    Serial.print(F("Board: ")); \
    Serial.println(F(BOARD_NAME)); \
    Serial.print(F("Max Cylinders: ")); \
    Serial.println(BOARD_MAX_CYLINDERS); \
    Serial.print(F("Inj Channels: ")); \
    Serial.println(BOARD_INJ_CHANNELS); \
    Serial.print(F("Ign Channels: ")); \
    Serial.println(BOARD_IGN_CHANNELS); \
  } while(0)

#endif // BOARD_CONFIG_H