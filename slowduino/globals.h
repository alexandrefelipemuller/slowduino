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
#include "board_config.h"  // Configuração de hardware (Slowduino ou Speeduino v0.4)

// ============================================================================
// VERSÃO DO FIRMWARE
// ============================================================================
#define SLOWDUINO_VERSION "0.2.1-multi"
#define EEPROM_DATA_VERSION 3

// ============================================================================
// MAPEAMENTO DE PINOS
// ============================================================================
// NOTA: Pinos agora definidos em board_config.h
// Descomente BOARD_SPEEDUINO_V04 em board_config.h para usar pinagem Speeduino v0.4
// Ou deixe BOARD_SLOWDUINO (padrão) para Arduino Uno/Nano

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
  uint8_t  afrTarget;          // AFR target (same scale as O2)
  uint8_t  battery10;          // Tensão bateria * 10 (ex: 145 = 14.5V)
  uint8_t  oilPressure;        // Pressão óleo kPa (0-1000 kPa)
  uint8_t  fuelPressure;       // Pressão combustível kPa (0-1000 kPa)

  // Combustível (2 bancos principais + canal auxiliar opcional)
  uint16_t PW1;                // Pulsewidth injetor 1 (microsegundos) - bancadas 1+4
  uint16_t PW2;                // Pulsewidth injetor 2 - bancadas 2+3 (motores 4c)
  uint16_t PW3;                // Pulsewidth auxiliar (staged / nitro / boost)
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
  uint8_t  egoCorrection;      // Closed-loop O2 correction %

  // Estado do motor
  uint8_t  engineStatus;       // Flags de estado (bit field)
  uint8_t  protectionStatus;   // Bits de proteção (RPM/óleo)

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
  uint8_t  nCylinders;         // Número de cilindros (1-4, 2 canais wasted)
  uint8_t  injectorLayout;     // 0=Wasted Paired (fixo, sem sensor de fase)

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

  // Closed-loop O2 (EGO)
  uint8_t  egoType;            // 0=Off, 1=Narrowband, 2=Wide
  uint8_t  egoAlgorithm;       // 0=Disabled, 1=Simple
  uint8_t  egoDelay;           // Delay pós-partida (segundos)
  uint8_t  egoTemp;            // CLT mínimo (°C)
  uint8_t  egoRPM;             // RPM mínimo / 100
  uint8_t  egoTPSMax;          // TPS máximo %
  uint8_t  egoMin;             // Leitura mínima válida
  uint8_t  egoMax;             // Leitura máxima válida
  uint8_t  egoLimit;           // Limite de correção (+/- %)
  uint8_t  egoStep;            // Passo de correção (% por ciclo)
  uint8_t  egoIgnEvents;       // Nº de ignições entre ajustes
  uint8_t  egoTarget;          // Leitura alvo (mesma escala de O2)
  uint8_t  egoHysteresis;      // Banda morta ao redor do alvo

  // Proteção de pressão de óleo
  uint8_t  oilPressureProtEnable;     // 0=Off, 1=On
  uint8_t  oilPressureProtThreshold;  // Limite (0-250 scale)
  uint8_t  oilPressureProtHysteresis; // Histeresis
  uint8_t  oilPressureProtDelay;      // Delay ticks
  // Reserva para compatibilidade com Speeduino (página 1 = 128 bytes)
  uint8_t  spare[76];

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

  // Trigger edge (como na Speeduino)
  uint8_t  triggerEdge;        // 0=Rising, 1=Falling, 2=Both (CHANGE)

  // Proteções adicionais do motor
  uint8_t  engineProtectEnable;         // 0=Off, 1=On
  uint8_t  engineProtectRPM;            // RPM / 100
  uint8_t  engineProtectRPMHysteresis;  // RPM / 100
  uint8_t  engineProtectCutType;        // Bitmask: 1=fuel, 2=spark

  // Reserva para compatibilidade com Speeduino (página 2 = 288 bytes)
  // ConfigPage2 atual: 28 bytes
  // Padding necessário: 128 - 28 = 100 bytes
  uint8_t  spare[100];

} __attribute__((packed));

extern struct ConfigPage2 configPage2;

static_assert(sizeof(ConfigPage1) == 128, "ConfigPage1 deve ocupar 128 bytes");
static_assert(sizeof(ConfigPage2) == 128, "ConfigPage2 deve ocupar 128 bytes");

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

// Protections
#define PROTECTION_RPM_BIT 0x01
#define PROTECTION_OIL_BIT 0x02

#define ENGINE_PROTECT_CUT_FUEL  0x01
#define ENGINE_PROTECT_CUT_SPARK 0x02

// Protections
#define PROTECTION_RPM_BIT 0x01
#define PROTECTION_OIL_BIT 0x02

#define ENGINE_PROTECT_CUT_FUEL  0x01
#define ENGINE_PROTECT_CUT_SPARK 0x02

// Map rápido (assumindo range específico)
inline uint16_t fastMap(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif // GLOBALS_H
