/**
 * @file board_uno.h
 * @brief Pinagem e capacidades: Slowduino (Arduino Uno/Nano, ATmega328p)
 *
 * Incluído apenas por board_config.h. Contrato que toda placa deve cumprir
 * está documentado em board.h.
 */

#ifndef BOARD_UNO_H
#define BOARD_UNO_H

  #define BOARD_NAME "Slowduino (Uno/Nano)"
  // ATmega328p só dispõe de 2 comparadores → padrão geral de 2 canais de ignição (4 cilindros wasted)
  #define BOARD_MAX_CYLINDERS 4
  #define BOARD_INJ_CHANNELS  3
  #define BOARD_IGN_CHANNELS  2

  // Entradas Digitais (TRIGGER PRECISA DE INT0 - SOMENTE D2 NO UNO/NANO!)
  #define PIN_TRIGGER_PRIMARY   2   // Sensor de rotação (crank) - INT0 (D2)
  // NOTA: PIN_TRIGGER_SECONDARY (D3) REMOVIDO - sem sensor de fase (wasted spark 2 canais)

  // Saídas Digitais - Ignição (wasted spark para motores 1-4 cilindros)
  #define PIN_IGNITION_1      4   // Ignição 1 (cilindros 1+4)
  #define PIN_IGNITION_2      5   // Ignição 2 (cilindros 2+3)
  // D3 fica disponível (ex: ign kill, tach, auxiliar)

  // Saídas Digitais - Injeção (2 bancos principais + canal auxiliar)
  #define PIN_INJECTOR_1     10   // Bico 1 (cilindros 1+4)
  #define PIN_INJECTOR_2     11   // Bico 2 (cilindros 2+3)
  #define PIN_INJECTOR_3      7   // Bico auxiliar / staging

  // Saídas Digitais - Auxiliares
  #define PIN_FUEL_PUMP       6   // Relé da bomba de combustível
  #define PIN_FAN             8   // Ventoinha do radiador
  #define PIN_IDLE_VALVE      9   // Selenoide de marcha lenta (IAC - PWM) = PB1

  // ATENÇÃO: D9 é OC1A. NUNCA usar analogWrite() neste pino!
  // analogWrite(9, v) do core Arduino faz sbi(TCCR1A, COM1A1) e escreve
  // OCR1A = v - e OCR1A é o compare absoluto que o scheduler usa para
  // agendar a ignição/injeção do canal 1 (scheduler.cpp). Isso destrói o
  // timing de faísca. O PWM do IAC é gerado por software na ISR do Timer2
  // (auxiliaries.cpp), que não toca em nenhum registrador do Timer1.
  #define IDLE_PIN_HIGH()     (PORTB |= (1 << PB1))
  #define IDLE_PIN_LOW()      (PORTB &= ~(1 << PB1))

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


#endif // BOARD_UNO_H
