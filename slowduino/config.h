/**
 * @file config.h
 * @brief Configurações, defines e constantes do Slowduino
 *
 * Arquivo central de configuração do firmware
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ============================================================================
// TAMANHO DAS TABELAS
// ============================================================================
#define TABLE_SIZE_X        16   // Eixo X (RPM) - 16 pontos
#define TABLE_SIZE_Y        16   // Eixo Y (MAP/TPS) - 16 pontos

// ============================================================================
// CONSTANTES DE TIMING
// ============================================================================

// Timer1 - 16 bits, usado para scheduler de injeção e ignição
// Prescaler 8: 16MHz / 8 = 2MHz -> 0.5µs por tick
// Máximo: 65536 * 0.5µs = 32.768ms
#define TIMER1_PRESCALER    8
#define TIMER1_RESOLUTION   0.5  // microsegundos por tick (não usado diretamente, apenas doc)

// Conversão de microsegundos para ticks do Timer1
#define US_TO_TIMER1(us)    ((us) * 2)

// Conversão de ticks para microsegundos
#define TIMER1_TO_US(ticks) ((ticks) / 2)

// ============================================================================
// CONSTANTES DE SENSORES
// ============================================================================

// Filtros IIR - valores maiores = mais filtro (mais lento)
// Formula: newValue = (input * (256-alpha) + oldValue * alpha) / 256
#define FILTER_MAP          20   // MAP: resposta rápida
#define FILTER_TPS          50   // TPS: média
#define FILTER_CLT         180   // CLT: muito filtrado (lento)
#define FILTER_IAT         180   // IAT: muito filtrado (lento)
#define FILTER_O2          128   // O2: média-alta
#define FILTER_BAT         128   // Bateria: média-alta
#define FILTER_OIL_PRESS   100   // Pressão óleo: média
#define FILTER_FUEL_PRESS  100   // Pressão combustível: média

// Limites de ADC (10-bit: 0-1023)
#define ADC_MIN             0
#define ADC_MAX          1023

// Referência ADC (mV)
#define ADC_VREF         5000    // 5V

// Divisor de tensão da bateria (R1=10K, R2=1K5 -> 14.5V = ~1.87V no ADC)
// Bateria = (ADC * VREF / 1024) * (R1+R2) / R2
// Com R1=10K, R2=1K5: multiplicador = 7.67
#define BAT_MULTIPLIER    767    // * 100 para evitar float

// ============================================================================
// CONSTANTES DE MOTOR
// ============================================================================

// RPM
#define RPM_MIN              50   // RPM mínimo considerado válido
#define RPM_MAX            8000   // RPM máximo
#define CRANK_RPM           400   // Abaixo disso = partida

// Timeout para perda de sincronismo (ms)
#define SYNC_TIMEOUT       1000   // 1 segundo sem dente = perda de sync

// ============================================================================
// CONSTANTES DE INJEÇÃO
// ============================================================================

// Limites de pulsewidth (microsegundos)
#define INJ_MIN_PW          500   // 0.5ms mínimo
#define INJ_MAX_PW        20000   // 20ms máximo

// Ângulo de injeção padrão (graus BTDC)
#define INJ_ANGLE_DEFAULT   355   // 5 graus BTDC

// ============================================================================
// CONSTANTES DE IGNIÇÃO
// ============================================================================

// Limites de avanço (graus BTDC)
#define IGN_MIN_ADVANCE    -10    // 10 ATDC (retardo)
#define IGN_MAX_ADVANCE     45    // 45 BTDC

// Limites de dwell (microsegundos)
#define DWELL_MIN         1000    // 1ms mínimo
#define DWELL_MAX         8000    // 8ms máximo
#define DWELL_DEFAULT     3000    // 3ms padrão

// ============================================================================
// CONSTANTES DE CORREÇÕES
// ============================================================================

// Base para correções percentuais
#define CORR_BASE          100

// Limites de correção total
#define CORR_MIN            50    // 50% = metade do combustível
#define CORR_MAX           200    // 200% = dobro do combustível

// After-Start Enrichment
#define ASE_DEFAULT_PCT    150    // 150% durante ASE
#define ASE_DEFAULT_COUNT   50    // 50 ignições

// Warm-Up Enrichment
#define WUE_MIN            100    // Sem enriquecimento
#define WUE_MAX            200    // Dobro

// Acceleration Enrichment
#define AE_THRESH_DEFAULT   10    // 10%/s de mudança no TPS
#define AE_PCT_DEFAULT     120    // 20% de enriquecimento

// ============================================================================
// CONFIGURAÇÕES DE COMUNICAÇÃO SERIAL
// ============================================================================

#define SERIAL_BAUD      115200   // Velocidade padrão TunerStudio
#define SERIAL_TIMEOUT      100   // Timeout de comando (ms)

// Buffer de comunicação
#define SERIAL_BUFFER_SIZE   64   // Bytes

// Comandos do protocolo TunerStudio simplificado
#define CMD_READ_REALTIME   'A'   // Lê dados em tempo real
#define CMD_READ_VE         'V'   // Lê tabela VE
#define CMD_READ_IGN        'I'   // Lê tabela Ignição
#define CMD_WRITE_VE        'W'   // Escreve tabela VE
#define CMD_WRITE_IGN       'X'   // Escreve tabela Ignição
#define CMD_BURN_EEPROM     'B'   // Salva configuração
#define CMD_GET_VERSION     'Q'   // Retorna versão
#define CMD_TEST_COMMS      'T'   // Teste de comunicação

// Respostas
#define RESP_OK             0x00
#define RESP_ERROR          0xFF

// ============================================================================
// LAYOUT DA EEPROM (1024 bytes)
// ============================================================================

#define EEPROM_VERSION_ADDR     0    // 1 byte - versão

// Tabela VE 16x16
#define EEPROM_VE_TABLE        10    // 256 bytes (values)
#define EEPROM_VE_AXIS_X      (EEPROM_VE_TABLE + 256)  // 32 bytes (16 × uint16_t RPM)
#define EEPROM_VE_AXIS_Y      (EEPROM_VE_AXIS_X + 32)  // 16 bytes (16 × uint8_t MAP)

// Tabela Ignição 16x16
#define EEPROM_IGN_TABLE      (EEPROM_VE_AXIS_Y + 16)  // 256 bytes (values)
#define EEPROM_IGN_AXIS_X     (EEPROM_IGN_TABLE + 256) // 32 bytes
#define EEPROM_IGN_AXIS_Y     (EEPROM_IGN_AXIS_X + 32) // 16 bytes

// Config pages
#define EEPROM_CONFIG1        (EEPROM_IGN_AXIS_Y + 16) // 128 bytes - fuel config
#define EEPROM_CONFIG2        (EEPROM_CONFIG1 + 128)   // 128 bytes - ignition config

// Tabelas de calibração
#define EEPROM_CLT_TABLE      (EEPROM_CONFIG2 + 128)   // 64 bytes (32 × int8_t temp)
#define EEPROM_IAT_TABLE      (EEPROM_CLT_TABLE + 64)  // 64 bytes (32 × int8_t temp)

// Reserva para expansão futura (22 bytes restantes)
#define EEPROM_SPARE          (EEPROM_IAT_TABLE + 64)

// ============================================================================
// FLAGS DE TIMER (Loop principal)
// ============================================================================

// Máscara de bits para controle de tempo no loop
extern volatile uint8_t loopTimerFlags;

#define TIMER_FLAG_4HZ        0      // 250ms - sensores lentos
#define TIMER_FLAG_15HZ       1      // ~67ms
#define TIMER_FLAG_30HZ       2      // ~33ms - sensores médios
#define TIMER_FLAG_200HZ      3      // 5ms
#define TIMER_FLAG_1KHZ       4      // 1ms - sensores rápidos

// ============================================================================
// MODOS DE OPERAÇÃO
// ============================================================================

// Injector layout
#define INJ_LAYOUT_PAIRED         0   // Wasted paired (2 canais)
#define INJ_LAYOUT_SEMI_SEQ       1   // Semi-sequential (4 canais - futuro)

// AE mode
#define AE_MODE_TPS               0   // Baseado em TPSdot
#define AE_MODE_MAP               1   // Baseado em MAPdot

// Trigger patterns
#define TRIGGER_MISSING_TOOTH     0   // Missing tooth (36-1, 60-2)
#define TRIGGER_BASIC_DIST        1   // Distribuidor básico (1 dente/rev)

// MAP sampling
#define MAP_SAMPLE_INSTANT        0   // Leitura instantânea
#define MAP_SAMPLE_AVERAGE        1   // Média do ciclo

// ============================================================================
// CONSTANTES DE AUXILIARES
// ============================================================================

// Ventoinha (Fan)
#define FAN_ON_TEMP         95    // Liga ventoinha em 95°C
#define FAN_OFF_TEMP        90    // Desliga em 90°C (histerese)

// Bomba de combustível
#define FUEL_PUMP_PRIME_MS  2000  // Prime de 2 segundos ao ligar

// Válvula de marcha lenta (IAC)
#define IAC_IDLE_RPM        850   // RPM alvo de marcha lenta
#define IAC_RPM_DEADBAND    50    // Banda morta ±50 RPM
#define IAC_STEP_SIZE       2     // Incremento de duty cycle (%)
#define IAC_MIN_DUTY        0     // Duty mínimo
#define IAC_MAX_DUTY        100   // Duty máximo

// Pressão de óleo e combustível (sensores 0-5V = 0-1000 kPa típico)
#define OIL_PRESS_MIN       50    // Pressão mínima óleo em idle (kPa)
#define FUEL_PRESS_MIN      250   // Pressão mínima combustível (kPa)

// ============================================================================
// DEBUG
// ============================================================================

// Descomente para ativar debug serial (consome RAM e tempo)
// #define DEBUG_ENABLED

#ifdef DEBUG_ENABLED
  #define DEBUG_PRINT(x)     Serial.print(x)
  #define DEBUG_PRINTLN(x)   Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

// ============================================================================
// VALORES PADRÃO INICIAIS
// ============================================================================

// Tabela VE padrão (16x16) - valores conservadores para primeiro start
// 50% VE em idle, 80% em carga média, 100% em alta carga
// Deve ser ajustado no TunerStudio conforme o motor
const uint8_t DEFAULT_VE_TABLE[TABLE_SIZE_Y][TABLE_SIZE_X] PROGMEM = {
  /*  20*/{ 45, 47, 50, 51, 52, 53, 54, 55, 55, 56, 57, 58, 59, 60, 61, 62 },
  /*  30*/{ 47, 50, 52, 53, 54, 55, 56, 57, 58, 59, 60, 62, 63, 64, 65, 66 },
  /*  40*/{ 50, 52, 54, 56, 57, 58, 59, 60, 61, 62, 64, 65, 66, 68, 69, 69 },
  /*  50*/{ 52, 54, 57, 59, 60, 62, 63, 64, 65, 67, 68, 69, 71, 72, 73, 74 },
  /*  60*/{ 54, 57, 59, 61, 63, 65, 66, 68, 70, 71, 73, 74, 75, 77, 78, 79 },
  /*  70*/{ 57, 59, 61, 64, 66, 68, 70, 71, 73, 75, 76, 78, 79, 80, 82, 83 },
  /*  80*/{ 59, 61, 64, 66, 68, 71, 73, 74, 76, 78, 79, 81, 82, 84, 85, 86 },
  /*  90*/{ 61, 64, 66, 68, 71, 73, 75, 77, 79, 81, 83, 85, 86, 87, 89, 90 },
  /* 100*/{ 64, 66, 68, 71, 73, 75, 78, 80, 82, 84, 86, 88, 90, 91, 92, 93 },
  /* 110*/{ 66, 68, 71, 73, 75, 78, 80, 82, 85, 87, 89, 91, 93, 94, 95, 96 },
  /* 120*/{ 68, 71, 73, 75, 78, 80, 82, 85, 87, 89, 92, 94, 95, 96, 97, 98 },
  /* 130*/{ 71, 73, 75, 77, 80, 82, 84, 87, 89, 91, 94, 96, 97, 98, 99,100 },
  /* 140*/{ 73, 75, 77, 79, 81, 83, 86, 88, 90, 92, 95, 97, 98, 99,100,101 },
  /* 150*/{ 75, 77, 78, 80, 82, 84, 87, 89, 91, 93, 96, 98, 99,100,101,102 },
  /* 160*/{ 77, 78, 79, 81, 83, 85, 88, 90, 92, 95, 97, 99,100,101,102,104 },
  /* 170*/{ 78, 79, 80, 82, 84, 87, 89, 91, 94, 96, 98,100,101,102,104,105 }
};

// Eixos padrão da tabela VE
const uint16_t DEFAULT_VE_AXIS_X[TABLE_SIZE_X] PROGMEM = {
   500, 1000, 1500, 2000, 2500, 3000, 3500, 4000,
  4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000
};

const uint8_t DEFAULT_VE_AXIS_Y[TABLE_SIZE_Y] PROGMEM = {
   20,  30,  40,  50,  60,  70,  80,  90,
  100, 110, 120, 130, 140, 150, 160, 170
};

// Tabela de Ignição padrão (16x16) - graus BTDC
// Conservador: mais avanço em baixa carga, menos em alta
const int8_t DEFAULT_IGN_TABLE[TABLE_SIZE_Y][TABLE_SIZE_X] PROGMEM = {
  /*  20*/{ 15, 16, 18, 20, 21, 23, 25, 27, 29, 30, 31, 32, 33, 34, 35, 36 },
  /*  30*/{ 14, 15, 16, 18, 20, 21, 23, 25, 27, 29, 29, 30, 31, 32, 33, 34 },
  /*  40*/{ 12, 14, 15, 16, 18, 20, 21, 23, 25, 27, 28, 29, 29, 30, 31, 32 },
  /*  50*/{ 11, 12, 14, 15, 16, 18, 20, 21, 23, 25, 26, 27, 28, 29, 29, 30 },
  /*  60*/{ 10, 11, 12, 14, 15, 16, 18, 20, 21, 23, 24, 25, 26, 27, 28, 29 },
  /*  70*/{  9, 10, 11, 12, 14, 15, 16, 18, 20, 21, 22, 23, 24, 25, 26, 27 },
  /*  80*/{  8,  9, 10, 11, 12, 14, 15, 16, 18, 19, 20, 21, 22, 23, 24, 25 },
  /*  90*/{  7,  8,  9, 10, 11, 12, 14, 15, 16, 18, 19, 19, 20, 21, 22, 23 },
  /* 100*/{  7,  7,  8,  9, 10, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22 },
  /* 110*/{  6,  7,  8,  9, 10, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21 },
  /* 120*/{  5,  6,  7,  8,  9, 10, 11, 12, 14, 15, 16, 17, 18, 18, 19, 20 },
  /* 130*/{  5,  6,  7,  8,  9, 10, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20 },
  /* 140*/{  4,  5,  6,  7,  8,  9, 10, 11, 13, 14, 15, 16, 17, 18, 18, 19 },
  /* 150*/{  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 },
  /* 160*/{  3,  4,  5,  6,  7,  8,  9, 10, 12, 13, 14, 15, 16, 17, 18, 18 },
  /* 170*/{  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18 }
};

// Eixos padrão da tabela Ignição (mesmos da VE)
const uint16_t DEFAULT_IGN_AXIS_X[TABLE_SIZE_X] PROGMEM = {
   500, 1000, 1500, 2000, 2500, 3000, 3500, 4000,
  4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000
};

const uint8_t DEFAULT_IGN_AXIS_Y[TABLE_SIZE_Y] PROGMEM = {
   20,  30,  40,  50,  60,  70,  80,  90,
  100, 110, 120, 130, 140, 150, 160, 170
};

#endif // CONFIG_H
