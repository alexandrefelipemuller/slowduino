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
#define TABLE_SIZE_X        8    // Eixo X (RPM) - 8 pontos
#define TABLE_SIZE_Y        8    // Eixo Y (MAP/TPS) - 8 pontos

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

// Tabela VE 8x8
#define EEPROM_VE_TABLE        10    // 64 bytes (values)
#define EEPROM_VE_AXIS_X       74    // 16 bytes (8 × uint16_t RPM)
#define EEPROM_VE_AXIS_Y       90    // 8 bytes (8 × uint8_t MAP)

// Tabela Ignição 8x8
#define EEPROM_IGN_TABLE      100    // 64 bytes (values)
#define EEPROM_IGN_AXIS_X     164    // 16 bytes (8 × uint16_t RPM)
#define EEPROM_IGN_AXIS_Y     180    // 8 bytes (8 × uint8_t MAP)

// Config pages
#define EEPROM_CONFIG1        200    // 128 bytes - fuel config
#define EEPROM_CONFIG2        328    // 128 bytes - ignition config

// Tabelas de calibração
#define EEPROM_CLT_TABLE      456    // 64 bytes (32 × int8_t temp)
#define EEPROM_IAT_TABLE      520    // 64 bytes (32 × int8_t temp)

// Reserva para expansão futura
#define EEPROM_SPARE          584    // 440 bytes livres

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

// Tabela VE padrão (8x8) - valores conservadores para primeiro start
// 50% VE em idle, 80% em carga média, 100% em alta carga
// Deve ser ajustado no TunerStudio conforme o motor
const uint8_t DEFAULT_VE_TABLE[TABLE_SIZE_Y][TABLE_SIZE_X] PROGMEM = {
  // RPM:  500   1000  1500  2000  3000  4000  5000  6000
  /*  20*/{ 45,   50,   52,   54,   56,   58,   60,   62 },  // MAP  20 kPa
  /*  40*/{ 50,   55,   58,   60,   62,   65,   68,   70 },  //      40 kPa
  /*  60*/{ 55,   60,   65,   68,   72,   75,   78,   80 },  //      60 kPa
  /*  80*/{ 60,   65,   70,   75,   78,   82,   85,   88 },  //      80 kPa
  /* 100*/{ 65,   70,   75,   80,   85,   90,   93,   95 },  //     100 kPa (WOT)
  /* 120*/{ 70,   75,   80,   85,   90,   95,   98,  100 },
  /* 140*/{ 75,   78,   82,   88,   92,   97,  100,  102 },
  /* 160*/{ 78,   80,   85,   90,   95,  100,  102,  105 }
};

// Eixos padrão da tabela VE
const uint16_t DEFAULT_VE_AXIS_X[TABLE_SIZE_X] PROGMEM = {
  500, 1000, 1500, 2000, 3000, 4000, 5000, 6000  // RPM
};

const uint8_t DEFAULT_VE_AXIS_Y[TABLE_SIZE_Y] PROGMEM = {
  20, 40, 60, 80, 100, 120, 140, 160  // MAP (kPa)
};

// Tabela de Ignição padrão (8x8) - graus BTDC
// Conservador: mais avanço em baixa carga, menos em alta
const int8_t DEFAULT_IGN_TABLE[TABLE_SIZE_Y][TABLE_SIZE_X] PROGMEM = {
  // RPM:  500   1000  1500  2000  3000  4000  5000  6000
  /*  20*/{ 15,   18,   22,   26,   30,   32,   34,   36 },  // MAP  20 kPa
  /*  40*/{ 12,   15,   18,   22,   26,   28,   30,   32 },  //      40 kPa
  /*  60*/{ 10,   12,   15,   18,   22,   24,   26,   28 },  //      60 kPa
  /*  80*/{  8,   10,   12,   15,   18,   20,   22,   24 },  //      80 kPa
  /* 100*/{  6,    8,   10,   12,   15,   17,   19,   21 },  //     100 kPa (WOT)
  /* 120*/{  5,    7,    9,   11,   14,   16,   18,   20 },
  /* 140*/{  4,    6,    8,   10,   13,   15,   17,   19 },
  /* 160*/{  3,    5,    7,    9,   12,   14,   16,   18 }
};

// Eixos padrão da tabela Ignição (mesmos da VE)
const uint16_t DEFAULT_IGN_AXIS_X[TABLE_SIZE_X] PROGMEM = {
  500, 1000, 1500, 2000, 3000, 4000, 5000, 6000  // RPM
};

const uint8_t DEFAULT_IGN_AXIS_Y[TABLE_SIZE_Y] PROGMEM = {
  20, 40, 60, 80, 100, 120, 140, 160  // MAP (kPa)
};

#endif // CONFIG_H
