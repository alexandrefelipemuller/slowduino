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
// Descomente UMA das opções abaixo:
//
#define BOARD_SLOWDUINO      // Arduino Uno/Nano (padrão, 2 canais, 1-4 cilindros)
//#define BOARD_SPEEDUINO_V04  // Speeduino v0.4 (Arduino Mega, 4 canais, 1-8 cilindros)

// ============================================================================
// DETECÇÃO AUTOMÁTICA DE PLACA (se nenhuma foi definida)
// ============================================================================
#if !defined(BOARD_SLOWDUINO) && !defined(BOARD_SPEEDUINO_V04)
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

// ============================================================================
// CONFIGURAÇÃO: SPEEDUINO v0.4 BOARD
// ============================================================================
#if defined(BOARD_SPEEDUINO_V04)

  #define BOARD_NAME "Speeduino v0.4 (Slowduino firmware - 3ch/6cyl max)"
  #define BOARD_MAX_CYLINDERS 6

  // NOTA: Firmware Slowduino usa apenas 3 canais (wasted spark/paired)
  //       Limitação: máximo 6 cilindros
  //       Usuários com motores 7-8 cilindros não podem usar este firmware

  // Entradas Digitais (Trigger)
  #define PIN_TRIGGER_PRIMARY   19  // Crank Input (VR1+) - INT2
  // PIN_TRIGGER_SECONDARY não usado (sem sensor de fase no Slowduino)

  // Saídas Digitais - Injeção (APENAS 3 canais usados)
  // Speeduino v0.4 usa drivers duplos (1/2 e 2/2 para cada canal)
  // Aqui mapeamos apenas o pino de controle principal (1/2)
  #define PIN_INJECTOR_1     8   // Injector 1 - Pin 1/2 (cil 1+4)
  #define PIN_INJECTOR_2     9   // Injector 2 - Pin 1/2 (cil 2+5)
  #define PIN_INJECTOR_3    10   // Injector 3 - Pin 1/2 (cil 3+6)
  // PIN_INJECTOR_4 não usado no firmware Slowduino

  // Saídas Digitais - Ignição (APENAS 3 canais usados)
  #define PIN_IGNITION_1    40   // Ignition 1 (cil 1+4)
  #define PIN_IGNITION_2    38   // Ignition 2 (cil 2+5)
  #define PIN_IGNITION_3    52   // Ignition 3 (cil 3+6)
  // PIN_IGNITION_4 não usado no firmware Slowduino

  // Saídas Digitais - Auxiliares (Proto Area - Speeduino 0.4.4b+)
  #define PIN_FUEL_PUMP     45   // Proto Area 3 - Fuel Pump
  #define PIN_FAN           47   // Proto Area 2 - Fan
  #define PIN_IDLE_VALVE    46   // Idle 2 / PWM Idle (pin 36/37)

  // Outras Entradas Digitais
  #define PIN_VSS           20   // Proto Area 5 - Clutch/VSS (adaptado)

  // Entradas Analógicas (Speeduino v0.4 pinout)
  #define PIN_CLT           A0   // Coolant (CLT) - pin 19
  #define PIN_IAT           A1   // Inlet Air Temp (IAT) - pin 20
  #define PIN_O2            A2   // O2 Sensor - pin 21
  #define PIN_TPS           A3   // TPS input - pin 22
  #define PIN_MAP           A4   // MAP Sensor - pin 11
  #define PIN_BAT           A5   // Bateria (não mapeado no v0.4 padrão, usando A5)
  #define PIN_OIL_PRESSURE  A6   // Pressão óleo (adaptação, não padrão v0.4)
  #define PIN_FUEL_PRESSURE A7   // Pressão combustível (adaptação, não padrão v0.4)

  // Capacidades da placa (limitadas pelo firmware Slowduino)
  // #undef BOARD_HAS_SECONDARY_TRIGGER  (não usado)
  // #undef BOARD_SUPPORTS_SEQUENTIAL    (não implementado)

// ============================================================================
// CONFIGURAÇÃO: SLOWDUINO (Arduino Uno/Nano)
// ============================================================================
#elif defined(BOARD_SLOWDUINO)

  #define BOARD_NAME "Slowduino (Uno/Nano)"
  #define BOARD_MAX_CYLINDERS 6

  // Entradas Digitais (TRIGGER PRECISA DE INT0 - SOMENTE D2 NO UNO/NANO!)
  #define PIN_TRIGGER_PRIMARY   2   // Sensor de rotação (crank) - INT0 (D2)
  // NOTA: PIN_TRIGGER_SECONDARY (D3) REMOVIDO - não usaremos sensor de fase
  //       Wasted spark é suficiente para até 6 cilindros (3 canais)

  // Saídas Digitais - Ignição (wasted spark para 1-6 cilindros)
  #define PIN_IGNITION_1      4   // Ignição 1 (cilindros 1+4)
  #define PIN_IGNITION_2      5   // Ignição 2 (cilindros 2+5)
  #define PIN_IGNITION_3      3   // Ignição 3 (cilindros 3+6)

  // Saídas Digitais - Injeção (wasted paired para 1-6 cilindros)
  #define PIN_INJECTOR_1     10   // Bico 1 (cilindros 1+4)
  #define PIN_INJECTOR_2     11   // Bico 2 (cilindros 2+5)
  #define PIN_INJECTOR_3      7   // Bico 3 (cilindros 3+6)

  // Saídas Digitais - Auxiliares
  #define PIN_FUEL_PUMP       6   // Relé da bomba de combustível
  #define PIN_FAN             8   // Ventoinha do radiador
  #define PIN_IDLE_VALVE      9   // Selenoide de marcha lenta (IAC - PWM)

  // Outras Entradas Digitais
  #define PIN_VSS            12   // Velocidade do veículo

  // Entradas Analógicas
  #define PIN_CLT             A0   // Temperatura do motor
  #define PIN_IAT             A1   // Temperatura do ar
  #define PIN_MAP             A2   // Pressão do coletor
  #define PIN_TPS             A3   // Posição da borboleta
  #define PIN_O2              A4   // Sonda Lambda
  #define PIN_BAT             A5   // Tensão da bateria
  #define PIN_OIL_PRESSURE    A6   // Pressão de óleo do motor
  #define PIN_FUEL_PRESSURE   A7   // Pressão da linha de combustível

  // Capacidades da placa
  // #undef BOARD_HAS_SECONDARY_TRIGGER  (não definido)
  // #undef BOARD_SUPPORTS_SEQUENTIAL    (não definido)

#endif

// ============================================================================
// CONFIGURAÇÕES DERIVADAS
// ============================================================================

// Define número de canais disponíveis (sempre 3 no firmware Slowduino)
#define BOARD_INJ_CHANNELS  3
#define BOARD_IGN_CHANNELS  3

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
