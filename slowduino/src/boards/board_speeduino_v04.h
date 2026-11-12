/**
 * @file board_speeduino_v04.h
 * @brief Pinagem e capacidades: Speeduino v0.4 (Arduino Mega 2560)
 *
 * Incluído apenas por board_config.h. Contrato que toda placa deve cumprir
 * está documentado em board.h.
 */

#ifndef BOARD_SPEEDUINO_V04_H
#define BOARD_SPEEDUINO_V04_H

  #define BOARD_NAME "Speeduino v0.4 (Slowduino firmware - 2 ign ch / 4 cyl max)"
  #define BOARD_MAX_CYLINDERS 4
  #define BOARD_INJ_CHANNELS  3
  #define BOARD_IGN_CHANNELS  2

  // NOTA: Firmware Slowduino padronizado usa apenas 2 canais de ignição (wasted spark)
  //       Limitação: máximo 4 cilindros em qualquer placa

  // Entradas Digitais (Trigger)
  #define PIN_TRIGGER_PRIMARY   19  // Crank Input (VR1+) - INT2
  // PIN_TRIGGER_SECONDARY não usado (sem sensor de fase no Slowduino)

  // Saídas Digitais - Injeção (2 bancos + auxiliar)
  // Speeduino v0.4 usa drivers duplos (1/2 e 2/2 para cada canal)
  // Aqui mapeamos apenas o pino de controle principal (1/2)
  #define PIN_INJECTOR_1     8   // Injector 1 - Pin 1/2 (banco 1)
  #define PIN_INJECTOR_2     9   // Injector 2 - Pin 1/2 (banco 2)
  #define PIN_INJECTOR_3    10   // Injector auxiliar / staging
  // PIN_INJECTOR_4 não usado no firmware Slowduino

  // Saídas Digitais - Ignição (2 canais padronizados)
  #define PIN_IGNITION_1    40   // Ignition 1 (cil 1+4)
  #define PIN_IGNITION_2    38   // Ignition 2 (cil 2+3)
  // D52 permanece livre (pode virar ignição auxiliar em outro firmware)

  // Saídas Digitais - Auxiliares (Proto Area - Speeduino 0.4.4b+)
  #define PIN_FUEL_PUMP     45   // Proto Area 3 - Fuel Pump
  #define PIN_FAN           47   // Proto Area 2 - Fan
  #define PIN_IDLE_VALVE    46   // Idle 2 / PWM Idle (pin 36/37) = PL3

  // Acesso direto à porta do IAC, usado pela ISR de PWM do Timer2.
  // digitalWrite() custa ~4us e a ISR roda a 4kHz - caro demais.
  #define IDLE_PIN_HIGH()   (PORTL |= (1 << PL3))
  #define IDLE_PIN_LOW()    (PORTL &= ~(1 << PL3))

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


#endif // BOARD_SPEEDUINO_V04_H
