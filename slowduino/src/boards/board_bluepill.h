/**
 * @file board_bluepill.h
 * @brief Pinagem e capacidades: STM32F103C8T6 "Blue Pill"
 *
 * Incluído apenas por board_config.h. Contrato que toda placa deve cumprir
 * está documentado em board.h.
 */

#ifndef BOARD_BLUEPILL_H
#define BOARD_BLUEPILL_H

  // O core STM32duino já define BOARD_NAME via linha de comando (nome da
  // placa do platformio.ini) - redefine para o nosso valor sem warning.
  #undef BOARD_NAME
  #define BOARD_NAME "STM32F103C8T6 Blue Pill (Slowduino porte)"
  #define BOARD_MAX_CYLINDERS 4
  #define BOARD_INJ_CHANNELS  3
  #define BOARD_IGN_CHANNELS  2

  // Entradas Digitais (Trigger). Qualquer pino GPIO serve de EXTI no STM32 -
  // ao contrário do Uno/Nano, não há limitação de "só D2".
  #define PIN_TRIGGER_PRIMARY   PA8

  // Saídas Digitais - Ignição (wasted spark para motores 1-4 cilindros)
  #define PIN_IGNITION_1       PA9    // Cilindros 1+4
  #define PIN_IGNITION_2       PA10   // Cilindros 2+3

  // Saídas Digitais - Injeção (2 bancos principais + canal auxiliar)
  #define PIN_INJECTOR_1       PB6    // Banco 1 (1+4)
  #define PIN_INJECTOR_2       PB7    // Banco 2 (2+3)
  #define PIN_INJECTOR_3       PB8    // Auxiliar / staging

  // Saídas Digitais - Auxiliares
  #define PIN_FUEL_PUMP        PB9
  #define PIN_FAN              PB5
  #define PIN_IDLE_VALVE       PB4    // PWM por software via TIM3 (auxiliaries.cpp)

  // Acesso "rápido" ao pino do IAC. No STM32, digitalWrite() já é bem mais
  // rápido que no AVR (escreve direto em GPIOx->BSRR por baixo dos panos),
  // então não precisamos de macro de porta bruta como no AVR.
  #define IDLE_PIN_HIGH()     digitalWrite(PIN_IDLE_VALVE, HIGH)
  #define IDLE_PIN_LOW()      digitalWrite(PIN_IDLE_VALVE, LOW)

  // Outras Entradas Digitais
  #define PIN_VSS              PB3

  // Entradas Analógicas (ADC1). PA2/PA3 ficam LIVRES de propósito: são a
  // USART2, que é o `Serial` padrão do variant genérico F103C8 quando a USB
  // CDC está desligada. analogRead() nesses pinos os coloca em modo analógico
  // e mata a UART (issue #4). MAP/TPS usam PB0/PB1 (ADC1 canais 8/9).
  #define PIN_CLT              PA0
  #define PIN_IAT              PA1
  #define PIN_MAP              PB0
  #define PIN_TPS              PB1
  #define PIN_O2               PA4
  #define PIN_BAT              PA5
  #define PIN_OIL_PRESSURE     PA6
  #define PIN_FUEL_PRESSURE    PA7


#endif // BOARD_BLUEPILL_H
