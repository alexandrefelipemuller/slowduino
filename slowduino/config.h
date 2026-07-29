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
#define TABLE_SIZE_X        12   // Eixo X (RPM) - 12 pontos (era 16 - branch ms1, corte de RAM)
#define TABLE_SIZE_Y        12   // Eixo Y (MAP/TPS) - 12 pontos (era 16 - branch ms1, corte de RAM)

// ============================================================================
// CONSTANTES DE TIMING
// ============================================================================

// Timer1 - 16 bits, usado para scheduler de injeção e ignição
// Prescaler 256: 16MHz / 256 = 62.5kHz -> 16µs por tick
// Máximo: 65536 * 16µs = 1.048s (cobre cranking lento sem overflow)
#define TIMER1_PRESCALER    256
#define TIMER1_RESOLUTION   16.0  // microsegundos por tick (não usado diretamente, apenas doc)

// Conversão de microsegundos para ticks do Timer1
#define US_TO_TIMER1(us)    ((uint16_t)((us) / 16))

#define TIMER1_TO_US(ticks) ((uint32_t)(ticks) * 16U)

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

// Closed-loop O2 (EGO) - escala 0-200 ≈ 0-1V narrowband
#define EGO_TYPE_OFF            0   // Sem correção
#define EGO_TYPE_NARROW         1   // Narrowband 0-1V
#define EGO_TYPE_WIDE           2   // Reservado / futuro

#define EGO_ALGO_DISABLED       0
#define EGO_ALGO_SIMPLE         1

#define EGO_DELAY_DEFAULT      30   // Segundos após motor ligado
#define EGO_TEMP_DEFAULT       60   // °C mínimo do motor
#define EGO_RPM_DEFAULT        15   // RPM / 100
#define EGO_TPS_MAX_DEFAULT    40   // TPS máximo (%)
#define EGO_MIN_DEFAULT        40   // Leituras fora disso ignoradas
#define EGO_MAX_DEFAULT       160
#define EGO_LIMIT_DEFAULT      10   // +/- %
#define EGO_STEP_DEFAULT        1   // % por iteração
#define EGO_IGN_EVENTS_DEFAULT  4   // Nº de ignições por passo
#define EGO_TARGET_DEFAULT    100   // Alvo (~lambda 1.0)
#define EGO_HYST_DEFAULT        5   // Banda morta ao redor do alvo

// ============================================================================
// CONFIGURAÇÕES DE COMUNICAÇÃO SERIAL
// ============================================================================

#define SERIAL_BAUD      115200   // Velocidade padrão TunerStudio
#define SERIAL_TIMEOUT      100   // Timeout de comando (ms)

// Buffer de comunicação
// BRANCH ms1: 64->24. Payload máximo do protocolo moderno cai de 58 para
// 18 bytes (SERIAL_BUFFER_SIZE-6); comandos simples (W/single value) cabem
// à vontade, mas chunk-writes de tabela precisam ser feitos em pedaços
// pequenos pela ferramenta de tuning - outra razão para este branch exigir
// um .ini/configuração de chunk size próprios.
#define SERIAL_BUFFER_SIZE   24   // Bytes

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

// BRANCH ms1: tabelas 12x12 (era 16x16) - offsets recalculados para o
// tamanho real, sem os ~248 bytes de EEPROM que antes ficavam vagos entre
// o fim dos valores e o início dos eixos.
// Tabela VE 12x12
#define EEPROM_VE_TABLE        10    // 144 bytes (values, 12x12)
#define EEPROM_VE_AXIS_X      (EEPROM_VE_TABLE + (TABLE_SIZE_X * TABLE_SIZE_Y))  // 24 bytes (12 × uint16_t RPM)
#define EEPROM_VE_AXIS_Y      (EEPROM_VE_AXIS_X + (TABLE_SIZE_X * 2))            // 12 bytes (12 × uint8_t MAP)

// Tabela Ignição 12x12
#define EEPROM_IGN_TABLE      (EEPROM_VE_AXIS_Y + TABLE_SIZE_Y)                  // 144 bytes (values)
#define EEPROM_IGN_AXIS_X     (EEPROM_IGN_TABLE + (TABLE_SIZE_X * TABLE_SIZE_Y)) // 24 bytes
#define EEPROM_IGN_AXIS_Y     (EEPROM_IGN_AXIS_X + (TABLE_SIZE_X * 2))           // 12 bytes

// Config pages (52 e 68 bytes - sem o spare[] que só existia para casar com
// o layout de página do Speeduino, que esta branch não segue mais)
#define EEPROM_CONFIG1        (EEPROM_IGN_AXIS_Y + TABLE_SIZE_Y) // 52 bytes - fuel config
#define EEPROM_CONFIG2        (EEPROM_CONFIG1 + 52)              // 68 bytes - ignition config

// Área auxiliar para AFR target (usa espaço antes reservado para CLT/IAT)
#define EEPROM_AFR_STORAGE    (EEPROM_CONFIG2 + 68)    // 120 bytes usados para AFR
#define EEPROM_AFR_STORAGE_LEN 120

// Reserva para expansão futura (restante da EEPROM)
#define EEPROM_SPARE          (EEPROM_AFR_STORAGE + EEPROM_AFR_STORAGE_LEN)
#if EEPROM_SPARE > 1024
#error "Layout EEPROM ultrapassa 1024 bytes"
#endif

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

// Trigger edges (compatível com Speeduino)
#define TRIGGER_EDGE_RISING       0
#define TRIGGER_EDGE_FALLING      1
#define TRIGGER_EDGE_BOTH         2

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
// Os parâmetros de tuning agora vivem em ConfigPage2 (EEPROM/TunerStudio).
// O que sobra aqui é a mecânica do PWM por software.

// Algoritmos (configPage2.iacAlgorithm)
#define IAC_ALGORITHM_NONE      0   // Sem controle de válvula
#define IAC_ALGORITHM_PWM_OL    1   // PWM open loop (tabela por CLT)
#define IAC_ALGORITHM_PWM_OLCL  2   // PWM open loop + PID de malha fechada

// Timer2 em CTC, prescaler 64 @16MHz = 4us por contagem.
// 63 contagens = 252us por tick -> ~3968Hz de taxa de ISR.
#define IDLE_PWM_TICK_DIVISOR   63
#define IDLE_PWM_TICK_HZ        3968UL

// Limites de frequência do PWM. O mínimo garante que o período em ticks caiba
// num uint8_t (3968/16 = 248); o máximo evita resolução de duty inutilizável.
#define IDLE_PWM_FREQ_MIN       16    // Hz
#define IDLE_PWM_FREQ_MAX       500   // Hz

// Anti-windup: acima de (alvo + esta janela) o motor não está em marcha lenta
#define IDLE_CL_RPM_WINDOW      500   // RPM

// Clamp do acumulador da integral (escala 1/256 -> ±100% de duty)
#define IDLE_INTEGRAL_LIMIT     25600L

// Idle advance (configPage2.idleAdvEnabled)
#define IDLE_ADV_OFF            0
#define IDLE_ADV_ADDED          1   // Soma ao avanço base
#define IDLE_ADV_SWITCHED       2   // Substitui o avanço base

// Pressão de óleo e combustível (sensores 0-5V = 0-1000 kPa típico)
#define OIL_PRESS_MIN       50    // Pressão mínima óleo em idle (kPa)
#define FUEL_PRESS_MIN      250   // Pressão mínima combustível (kPa)

// ============================================================================
// DEBUG
// ============================================================================

// Descomente para ativar debug serial (consome RAM e tempo)
//#define DEBUG_ENABLED

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

// BRANCH ms1: tabelas encolhidas de 16x16 para 12x12 para reduzir RAM.
// Valores reamostrados (bilinear) das tabelas 16x16 originais - ainda
// conservadores/genéricos, precisam ser ajustados no tuning software
// conforme o motor.
const uint8_t DEFAULT_VE_TABLE[TABLE_SIZE_Y][TABLE_SIZE_X] PROGMEM = {
  /*  20*/{ 45, 48, 51, 52, 53, 55, 55, 57, 58, 59, 61, 62},
  /*  34*/{ 48, 52, 54, 55, 57, 58, 59, 61, 63, 65, 66, 67},
  /*  47*/{ 51, 54, 58, 59, 61, 63, 64, 66, 68, 70, 71, 72},
  /*  61*/{ 54, 58, 61, 63, 66, 68, 71, 72, 74, 76, 78, 79},
  /*  75*/{ 58, 61, 64, 67, 70, 72, 75, 77, 79, 81, 83, 84},
  /*  88*/{ 61, 64, 67, 71, 74, 76, 79, 81, 84, 86, 88, 89},
  /* 102*/{ 64, 67, 71, 74, 77, 80, 83, 86, 88, 91, 92, 94},
  /* 115*/{ 67, 70, 73, 77, 80, 83, 86, 89, 92, 94, 96, 97},
  /* 129*/{ 71, 74, 76, 80, 83, 86, 89, 92, 96, 97, 98,100},
  /* 143*/{ 74, 76, 79, 81, 85, 88, 91, 94, 97, 99,100,101},
  /* 156*/{ 76, 78, 80, 83, 86, 89, 92, 96, 98,100,101,103},
  /* 170*/{ 78, 79, 81, 84, 88, 91, 94, 97,100,101,103,105}
};

// Eixos padrão da tabela VE (12 pontos, mesma faixa de antes: 500-8000 RPM, 20-170 kPa)
const uint16_t DEFAULT_VE_AXIS_X[TABLE_SIZE_X] PROGMEM = {
   500, 1182, 1864, 2545, 3227, 3909, 4591, 5273, 5955, 6636, 7318, 8000
};

const uint8_t DEFAULT_VE_AXIS_Y[TABLE_SIZE_Y] PROGMEM = {
   20,  34,  47,  61,  75,  88, 102, 115, 129, 143, 156, 170
};

// Tabela de Ignição padrão (12x12) - graus BTDC
const int8_t DEFAULT_IGN_TABLE[TABLE_SIZE_Y][TABLE_SIZE_X] PROGMEM = {
  /*  20*/{ 15, 17, 19, 21, 24, 27, 29, 31, 32, 33, 35, 36},
  /*  34*/{ 13, 15, 17, 19, 21, 24, 27, 28, 30, 30, 32, 33},
  /*  47*/{ 11, 13, 15, 17, 19, 21, 24, 26, 28, 29, 29, 31},
  /*  61*/{ 10, 11, 13, 15, 17, 19, 21, 23, 25, 26, 27, 29},
  /*  75*/{  8, 10, 11, 13, 15, 17, 19, 21, 22, 23, 25, 26},
  /*  88*/{  7,  9, 10, 11, 13, 15, 17, 19, 19, 21, 22, 23},
  /* 102*/{  7,  7,  9, 10, 11, 13, 15, 16, 18, 19, 20, 22},
  /* 115*/{  6,  7,  8, 10, 10, 12, 14, 16, 17, 18, 19, 20},
  /* 129*/{  5,  6,  8,  9, 10, 12, 13, 15, 16, 17, 19, 20},
  /* 143*/{  4,  5,  7,  8,  9, 11, 13, 14, 16, 17, 18, 19},
  /* 156*/{  3,  5,  6,  7,  9, 10, 12, 14, 15, 16, 18, 18},
  /* 170*/{  3,  4,  6,  7,  8, 10, 11, 13, 14, 15, 17, 18}
};

// Eixos padrão da tabela Ignição (mesmos da VE)
const uint16_t DEFAULT_IGN_AXIS_X[TABLE_SIZE_X] PROGMEM = {
   500, 1182, 1864, 2545, 3227, 3909, 4591, 5273, 5955, 6636, 7318, 8000
};

const uint8_t DEFAULT_IGN_AXIS_Y[TABLE_SIZE_Y] PROGMEM = {
   20,  34,  47,  61,  75,  88, 102, 115, 129, 143, 156, 170
};

// DEFAULT_AFR_TABLE removida (branch ms1): não tinha nenhuma referência no
// código - currentStatus.afrTarget é um escalar único, não uma tabela.

#endif // CONFIG_H
