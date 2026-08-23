/**
 * @file storage.cpp
 * @brief Implementação do gerenciamento de EEPROM
 */

#include "storage.h"
#include "tables.h"
#include <EEPROM.h>

// Forward declarations
void loadVETable();
void loadIgnTable();
void loadCalibrationTables();
void saveVETable();
void saveIgnTable();
void saveCalibrationTables();
void loadDefaultTables();
void loadDefaultCalibration();
static void enforceBoardLimits();
static void sanitizeConfigValues();

// ============================================================================
// INICIALIZAÇÃO
// ============================================================================

void storageInit() {
  // Verifica versão da EEPROM
  uint8_t storedVersion = eepromReadByte(EEPROM_VERSION_ADDR);

  if (storedVersion != EEPROM_DATA_VERSION) {
    // Primeira inicialização ou versão incompatível
    DEBUG_PRINTLN(F("EEPROM: Versão inválida ou primeira inicialização"));
    loadDefaults();
    sanitizeConfigValues();
    enforceBoardLimits();
    saveAllConfig();
  } else {
    // Versão OK, carrega configuração
    DEBUG_PRINTLN(F("EEPROM: Carregando configuração"));
    loadAllConfig();
    sanitizeConfigValues();
    enforceBoardLimits();
  }
}

// ============================================================================
// LOAD CONFIG
// ============================================================================

void loadAllConfig() {
  loadConfigPages();
  loadVETable();
  loadIgnTable();
  loadCalibrationTables();
}

void loadConfigPages() {
  // Carrega ConfigPage1 (fuel)
  uint8_t* p1 = (uint8_t*)&configPage1;
  for (uint16_t i = 0; i < sizeof(ConfigPage1); i++) {
    p1[i] = eepromReadByte(EEPROM_CONFIG1 + i);
  }

  // Carrega ConfigPage2 (ignition)
  uint8_t* p2 = (uint8_t*)&configPage2;
  for (uint16_t i = 0; i < sizeof(ConfigPage2); i++) {
    p2[i] = eepromReadByte(EEPROM_CONFIG2 + i);
  }
}

void loadVETable() {
  // Carrega valores da tabela
  for (uint8_t y = 0; y < TABLE_SIZE_Y; y++) {
    for (uint8_t x = 0; x < TABLE_SIZE_X; x++) {
      uint16_t addr = EEPROM_VE_TABLE + (y * TABLE_SIZE_X) + x;
      veTable.values[y][x] = eepromReadByte(addr);
    }
  }

  // Carrega eixo X (RPM)
  for (uint8_t i = 0; i < TABLE_SIZE_X; i++) {
    veTable.axisX[i] = eepromReadU16(EEPROM_VE_AXIS_X + (i * 2));
  }

  // Carrega eixo Y (MAP)
  for (uint8_t i = 0; i < TABLE_SIZE_Y; i++) {
    veTable.axisY[i] = eepromReadByte(EEPROM_VE_AXIS_Y + i);
  }
}

void loadIgnTable() {
  // Carrega valores da tabela
  for (uint8_t y = 0; y < TABLE_SIZE_Y; y++) {
    for (uint8_t x = 0; x < TABLE_SIZE_X; x++) {
      uint16_t addr = EEPROM_IGN_TABLE + (y * TABLE_SIZE_X) + x;
      ignTable.values[y][x] = eepromReadI8(addr);
    }
  }

  // Carrega eixo X (RPM)
  for (uint8_t i = 0; i < TABLE_SIZE_X; i++) {
    ignTable.axisX[i] = eepromReadU16(EEPROM_IGN_AXIS_X + (i * 2));
  }

  // Carrega eixo Y (MAP)
  for (uint8_t i = 0; i < TABLE_SIZE_Y; i++) {
    ignTable.axisY[i] = eepromReadByte(EEPROM_IGN_AXIS_Y + i);
  }
}

void loadCalibrationTables() {
  uint8_t* p = (uint8_t*)&calibrationConfig;
  for (uint16_t i = 0; i < sizeof(CalibrationConfig); i++) {
    p[i] = eepromReadByte(EEPROM_CALIBRATION + i);
  }
}

static void enforceBoardLimits() {
  if (configPage1.nCylinders == 0) {
    configPage1.nCylinders = 1;
  }

  if (configPage1.nCylinders > BOARD_MAX_CYLINDERS) {
    DEBUG_PRINT(F("Limite da placa atingido, ajustando cilindros para "));
    DEBUG_PRINTLN(BOARD_MAX_CYLINDERS);
    configPage1.nCylinders = BOARD_MAX_CYLINDERS;
  }
}

static void sanitizeConfigValues() {
  if (configPage2.triggerEdge > TRIGGER_EDGE_BOTH) {
    configPage2.triggerEdge = TRIGGER_EDGE_BOTH;
  }

  // Evita divisão por zero em readO2() se a calibração vier zerada/corrompida
  // (ex: EEPROM nunca gravada antes desta feature, ou escrita inválida)
  if (calibrationConfig.o2Max <= calibrationConfig.o2Min) {
    calibrationConfig.o2Min = DEFAULT_O2_MIN;
    calibrationConfig.o2Max = DEFAULT_O2_MAX;
  }
}

// ============================================================================
// SAVE CONFIG
// ============================================================================

void saveAllConfig() {
  // Atualiza versão
  eepromWriteByte(EEPROM_VERSION_ADDR, EEPROM_DATA_VERSION);

  saveConfigPages();
  saveVETable();
  saveIgnTable();
  saveCalibrationTables();

  DEBUG_PRINTLN(F("EEPROM: Configuração salva"));
}

void saveConfigPages() {
  // Salva ConfigPage1
  const uint8_t* p1 = (const uint8_t*)&configPage1;
  for (uint16_t i = 0; i < sizeof(ConfigPage1); i++) {
    eepromWriteByte(EEPROM_CONFIG1 + i, p1[i]);
  }

  // Salva ConfigPage2
  const uint8_t* p2 = (const uint8_t*)&configPage2;
  for (uint16_t i = 0; i < sizeof(ConfigPage2); i++) {
    eepromWriteByte(EEPROM_CONFIG2 + i, p2[i]);
  }
}

void saveVETable() {
  // Salva valores
  for (uint8_t y = 0; y < TABLE_SIZE_Y; y++) {
    for (uint8_t x = 0; x < TABLE_SIZE_X; x++) {
      uint16_t addr = EEPROM_VE_TABLE + (y * TABLE_SIZE_X) + x;
      eepromWriteByte(addr, veTable.values[y][x]);
    }
  }

  // Salva eixo X
  for (uint8_t i = 0; i < TABLE_SIZE_X; i++) {
    eepromWriteU16(EEPROM_VE_AXIS_X + (i * 2), veTable.axisX[i]);
  }

  // Salva eixo Y
  for (uint8_t i = 0; i < TABLE_SIZE_Y; i++) {
    eepromWriteByte(EEPROM_VE_AXIS_Y + i, veTable.axisY[i]);
  }
}

void saveIgnTable() {
  // Salva valores
  for (uint8_t y = 0; y < TABLE_SIZE_Y; y++) {
    for (uint8_t x = 0; x < TABLE_SIZE_X; x++) {
      uint16_t addr = EEPROM_IGN_TABLE + (y * TABLE_SIZE_X) + x;
      eepromWriteI8(addr, ignTable.values[y][x]);
    }
  }

  // Salva eixo X
  for (uint8_t i = 0; i < TABLE_SIZE_X; i++) {
    eepromWriteU16(EEPROM_IGN_AXIS_X + (i * 2), ignTable.axisX[i]);
  }

  // Salva eixo Y
  for (uint8_t i = 0; i < TABLE_SIZE_Y; i++) {
    eepromWriteByte(EEPROM_IGN_AXIS_Y + i, ignTable.axisY[i]);
  }
}

void saveCalibrationTables() {
  const uint8_t* p = (const uint8_t*)&calibrationConfig;
  for (uint16_t i = 0; i < sizeof(CalibrationConfig); i++) {
    eepromWriteByte(EEPROM_CALIBRATION + i, p[i]);
  }
}

// ============================================================================
// DEFAULTS
// ============================================================================

void loadDefaults() {
  DEBUG_PRINTLN(F("Carregando valores padrão"));

  // ---- ConfigPage1 (Fuel) ----
  configPage1.nCylinders = 4;
  configPage1.reqFuel = 10000;            // 10ms base
  configPage1.injOpen = 1000;             // 1ms deadtime

  // TPS
  configPage1.tpsMin = 20;                // ~2% do ADC
  configPage1.tpsMax = 235;               // ~92% do ADC
  configPage1.tpsFilter = FILTER_TPS;

  // MAP
  configPage1.mapMin = 20;                // 20 kPa
  configPage1.mapMax = 105;               // 105 kPa (atmosférico)
  configPage1.mapFilter = FILTER_MAP;

  // WUE (Warm-Up Enrichment)
  const int8_t wueBins[] = {-40, -20, 0, 20, 40, 60};        // Temperaturas
  const uint8_t wueVals[] = {180, 160, 140, 120, 110, 100};  // % enriquecimento
  for (uint8_t i = 0; i < 6; i++) {
    configPage1.wueBins[i] = wueBins[i];
    configPage1.wueValues[i] = wueVals[i];
  }

  // ASE (After-Start Enrichment)
  configPage1.asePct = ASE_DEFAULT_PCT;
  configPage1.aseCount = ASE_DEFAULT_COUNT;

  // AE (Accel Enrichment)
  configPage1.aeMode = AE_MODE_TPS;
  configPage1.aeThresh = AE_THRESH_DEFAULT;
  configPage1.aePct = AE_PCT_DEFAULT;

  // Priming
  configPage1.primePulse = 50;            // 5.0ms

  // Cranking
  configPage1.crankRPM = CRANK_RPM / 10;  // Dividido por 10 para economizar espaço

  // stoich e todo o cluster de defaults do closed-loop O2 (EGO) removidos -
  // eram escritos aqui mas fuel.cpp não tem nenhuma lógica de EGO
  // implementada (grep por "ego" no projeto não acha nada em fuel.cpp nem
  // sensors.cpp), então esses campos nunca eram lidos por nada. Este bloco
  // também estava duplicado (defaults de EGO e de proteção de óleo
  // apareciam duas vezes seguidas) - removida a duplicata junto.

  // Oil pressure protection defaults (disabled)
  configPage1.oilPressureProtEnable = 0;
  configPage1.oilPressureProtThreshold = 40;
  configPage1.oilPressureProtHysteresis = 4;
  configPage1.oilPressureProtDelay = 2;

  // ---- ConfigPage2 (Ignition) ----
  configPage2.triggerPattern = TRIGGER_MISSING_TOOTH;
  configPage2.triggerTeeth = 36;
  configPage2.triggerMissing = 1;
  configPage2.triggerEdge = TRIGGER_EDGE_BOTH;  // Mesmo comportamento anterior (CHANGE)

  // Dwell
  configPage2.dwellRun = DWELL_DEFAULT;
  configPage2.dwellCrank = 4000;          // 4ms durante partida (mais tempo)
  configPage2.dwellLimit = DWELL_MAX;

  // Timing
  configPage2.crankAdvance = 10;          // 10° BTDC durante partida

  // Rev limiter
  configPage2.revLimitRPM = 60;           // 6000 RPM

  // ---- Válvula de marcha lenta (IAC) ----
  configPage2.iacAlgorithm = IAC_ALGORITHM_PWM_OLCL;
  configPage2.idleFreq = 80;              // 160 Hz (resolução de duty ~4%)

  // Curvas por temperatura. O alvo quente de 850 RPM preserva o
  // comportamento do antigo IAC_IDLE_RPM.
  const int8_t  iacBins[]     = {-10, 20, 50, 85};   // °C
  const uint8_t iacOLPWM[]    = { 60, 45, 30, 22};   // Duty open loop %
  const uint8_t iacCLTargets[]= {130, 110, 95,  85}; // Alvo RPM / 10
  const int8_t  iacCrankBins[]= {-10, 20, 50, 85};   // °C
  const uint8_t iacCrankDuty[]= { 85, 70, 55, 45};   // Duty na partida %
  for (uint8_t i = 0; i < 4; i++) {
    configPage2.iacBins[i]      = iacBins[i];
    configPage2.iacOLPWMVal[i]  = iacOLPWM[i];
    configPage2.iacCLValues[i]  = iacCLTargets[i];
    configPage2.iacCrankBins[i] = iacCrankBins[i];
    configPage2.iacCrankDuty[i] = iacCrankDuty[i];
  }

  // PID conservador. KD fica em 0: a 15Hz o RPM é ruidoso o bastante para o
  // termo derivativo atrapalhar mais do que ajudar.
  configPage2.idleKP = 8;                 // ~5% de duty por 100 RPM de erro
  configPage2.idleKI = 4;
  configPage2.idleKD = 0;

  configPage2.iacCLminValue = 10;         // Faixa útil da válvula (%)
  configPage2.iacCLmaxValue = 90;
  configPage2.idleTaperTime = 30;         // 3,0 s de transição partida->run
  configPage2.iacTPSlimit = 5;            // Acima de 5% de TPS, reseta a integral

  // ---- Idle advance ----
  configPage2.idleAdvEnabled = IDLE_ADV_ADDED;
  configPage2.idleAdvTPS = 5;             // Só com borboleta fechada
  configPage2.idleAdvRPM = 15;            // Até 1500 RPM

  // Eixo = quanto o RPM está abaixo do alvo, em dezenas (0 a 200 RPM)
  const uint8_t idleAdvBins[]   = {0, 5, 10, 20};
  const int8_t  idleAdvValues[] = {0, 3,  6, 10};   // Graus adicionais
  for (uint8_t i = 0; i < 4; i++) {
    configPage2.idleAdvBins[i]   = idleAdvBins[i];
    configPage2.idleAdvValues[i] = idleAdvValues[i];
  }

  // CLT advance correction (4 pontos)
  const int8_t cltBins[] = {-20, 0, 40, 80};
  const int8_t cltVals[] = {5, 3, 0, -2};    // Mais avanço em frio
  for (uint8_t i = 0; i < 4; i++) {
    configPage2.cltAdvBins[i] = cltBins[i];
    configPage2.cltAdvValues[i] = cltVals[i];
  }

  // Ignition output
  configPage2.ignInvert = 0;              // Normal (active low)

  // Engine protection defaults (bloco duplicado removido; engineProtectCutType
  // também removido, nunca era lido por nada)
  configPage2.engineProtectEnable = 0;
  configPage2.engineProtectRPM = 70;
  configPage2.engineProtectRPMHysteresis = 3;

  // ---- Tabelas VE e Ignição ----
  loadDefaultTables();

  // ---- Calibração CLT/IAT/O2 ----
  loadDefaultCalibration();
}

void loadDefaultCalibration() {
  for (uint8_t i = 0; i < CALIB_POINTS; i++) {
    calibrationConfig.cltAdcBins[i] = pgm_read_word(&DEFAULT_CLT_CALIB_ADC[i]);
    calibrationConfig.cltTempValues[i] = (int8_t)pgm_read_byte(&DEFAULT_CLT_CALIB_TEMP[i]);
    calibrationConfig.iatAdcBins[i] = pgm_read_word(&DEFAULT_IAT_CALIB_ADC[i]);
    calibrationConfig.iatTempValues[i] = (int8_t)pgm_read_byte(&DEFAULT_IAT_CALIB_TEMP[i]);
  }
  calibrationConfig.o2Min = DEFAULT_O2_MIN;
  calibrationConfig.o2Max = DEFAULT_O2_MAX;
}

void loadDefaultTables() {
  // Carrega tabela VE padrão do PROGMEM
  for (uint8_t y = 0; y < TABLE_SIZE_Y; y++) {
    for (uint8_t x = 0; x < TABLE_SIZE_X; x++) {
      veTable.values[y][x] = pgm_read_byte(&DEFAULT_VE_TABLE[y][x]);
    }
  }

  for (uint8_t i = 0; i < TABLE_SIZE_X; i++) {
    veTable.axisX[i] = pgm_read_word(&DEFAULT_VE_AXIS_X[i]);
  }

  for (uint8_t i = 0; i < TABLE_SIZE_Y; i++) {
    veTable.axisY[i] = pgm_read_byte(&DEFAULT_VE_AXIS_Y[i]);
  }

  // Carrega tabela Ignição padrão do PROGMEM
  for (uint8_t y = 0; y < TABLE_SIZE_Y; y++) {
    for (uint8_t x = 0; x < TABLE_SIZE_X; x++) {
      // Nota: DEFAULT_IGN_TABLE tem int8_t, mas lemos como byte
      ignTable.values[y][x] = (int8_t)pgm_read_byte(&DEFAULT_IGN_TABLE[y][x]);
    }
  }

  for (uint8_t i = 0; i < TABLE_SIZE_X; i++) {
    ignTable.axisX[i] = pgm_read_word(&DEFAULT_IGN_AXIS_X[i]);
  }

  for (uint8_t i = 0; i < TABLE_SIZE_Y; i++) {
    ignTable.axisY[i] = pgm_read_byte(&DEFAULT_IGN_AXIS_Y[i]);
  }
}

void resetEEPROM() {
  DEBUG_PRINTLN(F("RESET da EEPROM"));

  // Invalida versão
  eepromWriteByte(EEPROM_VERSION_ADDR, 0xFF);

  // Recarrega defaults
  loadDefaults();

  // Salva tudo
  saveAllConfig();
}

// ============================================================================
// FUNÇÕES AUXILIARES DE BAIXO NÍVEL
// ============================================================================

uint8_t eepromReadByte(uint16_t address) {
  return EEPROM.read(address);
}

bool eepromWriteByte(uint16_t address, uint8_t value) {
  uint8_t current = EEPROM.read(address);

  // Só escreve se valor for diferente (prolonga vida da EEPROM)
  if (current != value) {
    EEPROM.write(address, value);
    return true;
  }
  return false;
}

uint16_t eepromReadU16(uint16_t address) {
  // Little-endian
  uint16_t value = EEPROM.read(address);
  value |= (uint16_t)EEPROM.read(address + 1) << 8;
  return value;
}

void eepromWriteU16(uint16_t address, uint16_t value) {
  eepromWriteByte(address, value & 0xFF);
  eepromWriteByte(address + 1, (value >> 8) & 0xFF);
}

int8_t eepromReadI8(uint16_t address) {
  return (int8_t)EEPROM.read(address);
}

void eepromWriteI8(uint16_t address, int8_t value) {
  eepromWriteByte(address, (uint8_t)value);
}
