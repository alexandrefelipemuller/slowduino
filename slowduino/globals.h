/**
 * @file globals.h
 * @brief Estruturas de dados globais e definições do Slowduino
 *
 * ECU minimalista para ATmega328p (Arduino Uno/Nano)
 * Baseado na Speeduino, adaptado para limitações de memória
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

// ============================================================================
// VERSÃO DO FIRMWARE
// ============================================================================
#define SLOWDUINO_VERSION "0.1.0"
#define EEPROM_DATA_VERSION 1

// ============================================================================
// MAPEAMENTO DE PINOS (Arduino Uno/Nano)
// ============================================================================

// Saídas Digitais
#define PIN_INJECTOR_1      2   // Bico 1 (cilindros 1+4 em wasted paired)
#define PIN_INJECTOR_2      3   // Bico 2 (cilindros 2+3 em wasted paired)
#define PIN_IGNITION_1      4   // Ignição 1 (cilindros 1+4)
#define PIN_IGNITION_2      5   // Ignição 2 (cilindros 2+3)
#define PIN_FAN             8   // Ventoinha do radiador
#define PIN_IDLE_VALVE      9   // Selenoide de marcha lenta (IAC)
#define PIN_FUEL_PUMP      10   // Relé da bomba de combustível

// Entradas Digitais
#define PIN_TRIGGER_PRIMARY   6   // Sensor de rotação (crank) - INT0
#define PIN_TRIGGER_SECONDARY 7   // Sensor de fase (cam) - futuro
#define PIN_VSS              12   // Velocidade do veículo

// Futuro uso
#define PIN_SPARE_1         11

// Entradas Analógicas
#define PIN_CLT             A0   // Temperatura do motor
#define PIN_IAT             A1   // Temperatura do ar
#define PIN_MAP             A2   // Pressão do coletor
#define PIN_TPS             A3   // Posição da borboleta
#define PIN_O2              A4   // Sonda Lambda
#define PIN_BAT             A5   // Tensão da bateria
#define PIN_OIL_PRESSURE    A6   // Pressão de óleo do motor
#define PIN_FUEL_PRESSURE   A7   // Pressão da linha de combustível

// ============================================================================
// CONSTANTES DE CONVERSÃO
// ============================================================================
#define MICROS_PER_SEC      1000000UL
#define MICROS_PER_MIN      60000000UL
#define MILLIS_PER_SEC      1000

// Offset de temperatura para tabelas (permite temperaturas negativas)
#define TEMP_OFFSET         40

// ============================================================================
// ESTRUTURA DE STATUS ATUAL (RAM)
// ============================================================================
struct Statuses {
  // Motor
  uint16_t RPM;                // Rotações por minuto
  uint16_t RPMdiv100;          // RPM / 100 (para economia de cálculo)
  bool hasSync;                // Motor sincronizado com trigger

  // Sensores analógicos (valores brutos ADC 0-1023)
  uint16_t mapADC;
  uint16_t tpsADC;
  uint16_t cltADC;
  uint16_t iatADC;
  uint16_t o2ADC;
  uint16_t batADC;
  uint16_t oilPressADC;
  uint16_t fuelPressADC;

  // Sensores convertidos (valores físicos)
  uint8_t  MAP;                // Pressão kPa (0-255)
  uint8_t  TPS;                // Posição borboleta % (0-100)
  int8_t   coolant;            // Temperatura motor °C (-40 a +215)
  int8_t   IAT;                // Temperatura ar °C (-40 a +215)
  uint8_t  O2;                 // Lambda % (0-255, 100 = lambda 1.0)
  uint8_t  battery10;          // Tensão bateria * 10 (ex: 145 = 14.5V)
  uint8_t  oilPressure;        // Pressão óleo kPa (0-1000 kPa)
  uint8_t  fuelPressure;       // Pressão combustível kPa (0-1000 kPa)

  // Combustível
  uint16_t PW1;                // Pulsewidth injetor 1 (microsegundos)
  uint16_t PW2;                // Pulsewidth injetor 2
  uint8_t  VE;                 // Volumetric Efficiency % (0-255)
  uint16_t corrections;        // Correções acumuladas (base 100)

  // Ignição
  int8_t   advance;            // Avanço de ignição (graus BTDC)
  uint16_t dwell;              // Tempo de carga da bobina (microsegundos)

  // Correções individuais (para debug/tuning)
  uint8_t  wueCorrection;      // Warm-Up Enrichment %
  uint8_t  aseCorrection;      // After-Start Enrichment %
  uint8_t  aeCorrection;       // Accel Enrichment %
  uint8_t  cltCorrection;      // CLT correction %
  uint8_t  batCorrection;      // Battery correction %

  // Estado do motor
  uint8_t  engineStatus;       // Flags de estado (bit field)

  // Auxiliares (outputs)
  bool     fanActive;          // Ventoinha ativa
  bool     fuelPumpActive;     // Bomba de combustível ativa
  uint8_t  idleValveDuty;      // Duty cycle válvula marcha lenta (0-100%)

  // Tempo
  uint32_t secl;               // Segundos desde power-on
  uint32_t runSecs;            // Segundos de funcionamento (RPM > 0)

  // TPS rate of change
  int16_t  TPSdot;             // Taxa de mudança TPS (%/s)
  uint8_t  TPSlast;            // TPS anterior

  // Contadores
  uint32_t loopCount;          // Contador de loops (debug)
  uint16_t ignitionCount;      // Contador de ignições
};

// Flags de engineStatus
#define ENGINE_CRANK        0  // Bit 0: Motor em partida
#define ENGINE_RUN          1  // Bit 1: Motor funcionando
#define ENGINE_ASE          2  // Bit 2: After-Start Enrichment ativo
#define ENGINE_WARMUP       3  // Bit 3: Aquecimento ativo
#define ENGINE_ACC          4  // Bit 4: Aceleração detectada
#define ENGINE_DEC          5  // Bit 5: Desaceleração detectada

extern struct Statuses currentStatus;

// ============================================================================
// CONFIGURAÇÃO DE COMBUSTÍVEL (EEPROM)
// ============================================================================
struct ConfigPage1 {
  // Configuração do motor
  uint8_t  nCylinders;         // Número de cilindros (1-4)
  uint8_t  injectorLayout;     // 0=Paired, 1=Semi-Sequential

  // Required fuel
  uint16_t reqFuel;            // Required fuel em microsegundos (base para cálculo de PW)
  uint8_t  divider;            // Número de squirts por ciclo (1 ou 2)
  uint16_t injOpen;            // Tempo de abertura do injetor (microsegundos)

  // Calibração TPS
  uint8_t  tpsMin;             // ADC em 0% (0-255 mapeado de 0-1023)
  uint8_t  tpsMax;             // ADC em 100%
  uint8_t  tpsFilter;          // Constante de filtro (0-240)

  // Calibração MAP
  uint8_t  mapMin;             // kPa em ADC mínimo
  uint8_t  mapMax;             // kPa em ADC máximo
  uint8_t  mapSample;          // 0=Instantâneo, 1=Média ciclo
  uint8_t  mapFilter;          // Constante de filtro

  // Warm-Up Enrichment (6 pontos)
  uint8_t  wueBins[6];         // Temperaturas (-40 a +100°C)
  uint8_t  wueValues[6];       // Enriquecimento % (100-200)

  // After-Start Enrichment
  uint8_t  asePct;             // % de enriquecimento (100-200)
  uint8_t  aseCount;           // Número de ciclos (ignições)

  // Acceleration Enrichment
  uint8_t  aeMode;             // 0=TPS, 1=MAP
  uint8_t  aeThresh;           // Threshold para ativar (%/s ou kPa/s)
  uint8_t  aePct;              // % de enriquecimento
  uint8_t  aeTime;             // Duração (ms * 10)

  // Priming pulse
  uint8_t  primePulse;         // Pulso de prime (ms * 10)

  // Cranking
  uint8_t  crankRPM;           // RPM máximo para considerar cranking

  // Misc
  uint8_t  stoich;             // Razão estequiométrica * 10 (ex: 147 = 14.7:1)

  // Reserva para expansão futura
  uint8_t  spare[10];

} __attribute__((packed));

extern struct ConfigPage1 configPage1;

// ============================================================================
// CONFIGURAÇÃO DE IGNIÇÃO (EEPROM)
// ============================================================================
struct ConfigPage2 {
  // Trigger
  uint8_t  triggerPattern;     // 0=Missing Tooth, 1=Basic Distributor
  uint8_t  triggerTeeth;       // Dentes totais (ex: 36 para 36-1)
  uint8_t  triggerMissing;     // Dentes faltantes (ex: 1 para 36-1)
  uint8_t  triggerAngle;       // Ângulo do dente #1 ATDC

  // Dwell
  uint16_t dwellRun;           // Dwell em funcionamento (microsegundos)
  uint16_t dwellCrank;         // Dwell em partida (microsegundos)
  uint16_t dwellLimit;         // Limite máximo (proteção)

  // Timing
  int8_t   crankAdvance;       // Avanço durante partida (graus)

  // Rev Limiter
  uint8_t  revLimitRPM;        // RPM / 100 (ex: 60 = 6000 RPM)

  // Idle
  uint8_t  idleAdvance;        // Avanço adicional em idle (graus)
  uint8_t  idleRPM;            // RPM de idle / 10 (ex: 80 = 800 RPM)

  // CLT advance correction (4 pontos)
  int8_t   cltAdvBins[4];      // Temperaturas
  int8_t   cltAdvValues[4];    // Avanço adicional (graus, pode ser negativo)

  // Ignition output
  uint8_t  ignInvert;          // 0=Normal, 1=Invertido

  // Reserva
  uint8_t  spare[15];

} __attribute__((packed));

extern struct ConfigPage2 configPage2;

// ============================================================================
// MACROS ÚTEIS
// ============================================================================

// Manipulação de bits
#define BIT_SET(var, bit)    ((var) |= (1 << (bit)))
#define BIT_CLEAR(var, bit)  ((var) &= ~(1 << (bit)))
#define BIT_CHECK(var, bit)  ((var) & (1 << (bit)))
#define BIT_TOGGLE(var, bit) ((var) ^= (1 << (bit)))

// Conversão rápida de ADC 10-bit para 8-bit
#define ADC_10_TO_8(x)  ((x) >> 2)

// Percentual (evita overflow em multiplicação)
#define PERCENT(val, pct) (((uint32_t)(val) * (pct)) / 100)

// Map rápido (assumindo range específico)
inline uint16_t fastMap(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif // GLOBALS_H
