/**
 * @file storage.cpp
 * @brief Implementação do gerenciamento de EEPROM
 */

#include "storage.h"
#include "tables.h"
#include <EEPROM.h>
#include <string.h>

// Forward declarations
void loadVETable();
void loadIgnTable();
void loadCalibrationTables();
void loadAFRTable();
void saveVETable();
void saveIgnTable();
void saveCalibrationTables();
void saveAFRTable();
void loadDefaultTables();
static void loadDefaultAFRTable();
static void enforceBoardLimits();
static void sanitizeConfigValues();

static constexpr uint16_t AFR_VALUES_LEN = TABLE_SIZE_X * TABLE_SIZE_Y;
static constexpr uint16_t AFR_AXIS_X_LEN = TABLE_SIZE_X * sizeof(uint16_t);
static constexpr uint16_t AFR_AXIS_Y_LEN = TABLE_SIZE_Y;
static constexpr uint16_t AFR_STORAGE_TOTAL = AFR_VALUES_LEN + AFR_AXIS_X_LEN + AFR_AXIS_Y_LEN;
static constexpr uint16_t AFR_STORAGE_CHUNK_P1 = 80;
static constexpr uint16_t AFR_STORAGE_CHUNK_P2 = 104;
static constexpr uint16_t AFR_STORAGE_CHUNK_EXT = AFR_STORAGE_TOTAL - AFR_STORAGE_CHUNK_P1 - AFR_STORAGE_CHUNK_P2;
static_assert(AFR_STORAGE_CHUNK_EXT <= EEPROM_AFR_STORAGE_LEN, "AFR chunk externo excede área reservada");
static_assert((AFR_STORAGE_CHUNK_P1 + AFR_STORAGE_CHUNK_P2 + AFR_STORAGE_CHUNK_EXT) == AFR_STORAGE_TOTAL, "Chunks AFR inconsistentes");

static void readAfrStorage(uint8_t* buffer);
static void writeAfrStorage(const uint8_t* buffer);
static bool isAfrStorageBlank(const uint8_t* buffer, uint16_t len);

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
  loadAFRTable();
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

void loadAFRTable() {
  uint8_t buffer[AFR_STORAGE_TOTAL];
  readAfrStorage(buffer);

  if (isAfrStorageBlank(buffer, AFR_STORAGE_TOTAL)) {
    loadDefaultAFRTable();
    return;
  }

  uint16_t idx = 0;
  for (uint8_t y = 0; y < TABLE_SIZE_Y; y++) {
    for (uint8_t x = 0; x < TABLE_SIZE_X; x++) {
      afrTable.values[y][x] = buffer[idx++];
    }
  }

  for (uint8_t i = 0; i < TABLE_SIZE_X; i++) {
    uint16_t rpm = buffer[idx++] | ((uint16_t)buffer[idx++] << 8);
    afrTable.axisX[i] = rpm;
  }

  for (uint8_t i = 0; i < TABLE_SIZE_Y; i++) {
    afrTable.axisY[i] = buffer[idx++];
  }
}

void loadCalibrationTables() {
  // TODO: implementar quando tivermos tabelas de calibração CLT/IAT
  // Por enquanto usaremos valores calculados direto
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

  if (configPage1.egoType > EGO_TYPE_WIDE) {
    configPage1.egoType = EGO_TYPE_OFF;
  }

  if (configPage1.egoAlgorithm > EGO_ALGO_SIMPLE) {
    configPage1.egoAlgorithm = EGO_ALGO_SIMPLE;
  }

  if (configPage1.egoIgnEvents == 0) {
    configPage1.egoIgnEvents = 1;
  }

  if (configPage1.egoMax < configPage1.egoMin) {
    configPage1.egoMax = configPage1.egoMin;
  }

  if (configPage1.egoLimit > 100) {
    configPage1.egoLimit = 100;
  }

  if (configPage1.egoStep == 0) {
    configPage1.egoStep = 1;
  }

  if (configPage1.oilPressureProtThreshold > 250) {
    configPage1.oilPressureProtThreshold = 250;
  }

  if (configPage1.oilPressureProtHysteresis > 250) {
    configPage1.oilPressureProtHysteresis = 250;
  }

  if (configPage1.oilPressureProtDelay > 40) {
    configPage1.oilPressureProtDelay = 40;
  }

  if ((configPage2.engineProtectCutType & ~(ENGINE_PROTECT_CUT_FUEL | ENGINE_PROTECT_CUT_SPARK)) != 0) {
    configPage2.engineProtectCutType = ENGINE_PROTECT_CUT_FUEL | ENGINE_PROTECT_CUT_SPARK;
  }

  if (configPage2.engineProtectRPMHysteresis > configPage2.engineProtectRPM) {
    configPage2.engineProtectRPMHysteresis = configPage2.engineProtectRPM;
  }
}

// ============================================================================
// SAVE CONFIG
// ============================================================================

void saveAllConfig() {
  // Atualiza versão
  eepromWriteByte(EEPROM_VERSION_ADDR, EEPROM_DATA_VERSION);

  saveAFRTable();
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

void saveAFRTable() {
  uint8_t buffer[AFR_STORAGE_TOTAL];
  uint16_t idx = 0;

  for (uint8_t y = 0; y < TABLE_SIZE_Y; y++) {
    for (uint8_t x = 0; x < TABLE_SIZE_X; x++) {
      buffer[idx++] = afrTable.values[y][x];
    }
  }

  for (uint8_t i = 0; i < TABLE_SIZE_X; i++) {
    uint16_t rpm = afrTable.axisX[i];
    buffer[idx++] = rpm & 0xFF;
    buffer[idx++] = (rpm >> 8) & 0xFF;
  }

  for (uint8_t i = 0; i < TABLE_SIZE_Y; i++) {
    buffer[idx++] = afrTable.axisY[i];
  }

  writeAfrStorage(buffer);
}

void saveCalibrationTables() {
  // TODO: implementar quando necessário
}

static void readAfrStorage(uint8_t* buffer) {
  uint16_t idx = 0;
  memcpy(buffer, configPage1.spare, AFR_STORAGE_CHUNK_P1);
  idx += AFR_STORAGE_CHUNK_P1;

  memcpy(buffer + idx, configPage2.spare, AFR_STORAGE_CHUNK_P2);
  idx += AFR_STORAGE_CHUNK_P2;

  for (uint16_t i = 0; i < AFR_STORAGE_CHUNK_EXT; i++) {
    buffer[idx + i] = eepromReadByte(EEPROM_AFR_STORAGE + i);
  }
}

static void writeAfrStorage(const uint8_t* buffer) {
  uint16_t idx = 0;
  memcpy(configPage1.spare, buffer, AFR_STORAGE_CHUNK_P1);
  idx += AFR_STORAGE_CHUNK_P1;

  memcpy(configPage2.spare, buffer + idx, AFR_STORAGE_CHUNK_P2);
  idx += AFR_STORAGE_CHUNK_P2;

  for (uint16_t i = 0; i < AFR_STORAGE_CHUNK_EXT; i++) {
    eepromWriteByte(EEPROM_AFR_STORAGE + i, buffer[idx + i]);
  }
}

static bool isAfrStorageBlank(const uint8_t* buffer, uint16_t len) {
  for (uint16_t i = 0; i < len; i++) {
    if (buffer[i] != 0xFF) {
      return false;
    }
  }
  return true;
}

// ============================================================================
// DEFAULTS
// ============================================================================

void loadDefaults() {
  DEBUG_PRINTLN(F("Carregando valores padrão"));

  // ---- ConfigPage1 (Fuel) ----
  configPage1.nCylinders = 4;
  configPage1.injectorLayout = INJ_LAYOUT_PAIRED;
  configPage1.reqFuel = 10000;            // 10ms base
  configPage1.divider = 1;                // 1 squirt por ciclo
  configPage1.injOpen = 1000;             // 1ms deadtime

  // TPS
  configPage1.tpsMin = 20;                // ~2% do ADC
  configPage1.tpsMax = 235;               // ~92% do ADC
  configPage1.tpsFilter = FILTER_TPS;

  // MAP
  configPage1.mapMin = 20;                // 20 kPa
  configPage1.mapMax = 105;               // 105 kPa (atmosférico)
  configPage1.mapSample = MAP_SAMPLE_INSTANT;
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
  configPage1.aeTime = 10;                // 100ms

  // Priming
  configPage1.primePulse = 50;            // 5.0ms

  // Cranking
  configPage1.crankRPM = CRANK_RPM / 10;  // Dividido por 10 para economizar espaço

  // Stoich
  configPage1.stoich = 147;               // 14.7:1 (gasolina)

  // Closed-loop O2 (malha fechada)
  configPage1.egoType = EGO_TYPE_OFF;
  configPage1.egoAlgorithm = EGO_ALGO_SIMPLE;
  configPage1.egoDelay = EGO_DELAY_DEFAULT;
  configPage1.egoTemp = EGO_TEMP_DEFAULT;
  configPage1.egoRPM = EGO_RPM_DEFAULT;
  configPage1.egoTPSMax = EGO_TPS_MAX_DEFAULT;
  configPage1.egoMin = EGO_MIN_DEFAULT;
  configPage1.egoMax = EGO_MAX_DEFAULT;
  configPage1.egoLimit = EGO_LIMIT_DEFAULT;
  configPage1.egoStep = EGO_STEP_DEFAULT;
  configPage1.egoIgnEvents = EGO_IGN_EVENTS_DEFAULT;
  configPage1.egoTarget = EGO_TARGET_DEFAULT;
  configPage1.egoHysteresis = EGO_HYST_DEFAULT;

  // Oil pressure protection defaults (disabled)
  configPage1.oilPressureProtEnable = 0;
  configPage1.oilPressureProtThreshold = 40;  // ~160 kPa
  configPage1.oilPressureProtHysteresis = 4;
  configPage1.oilPressureProtDelay = 2;       // ~500ms at 4Hz

  // ---- ConfigPage2 (Ignition) ----
  configPage2.triggerPattern = TRIGGER_MISSING_TOOTH;
  configPage2.triggerTeeth = 36;
  configPage2.triggerMissing = 1;
  configPage2.triggerAngle = 0;           // Calibrar depois
  configPage2.triggerEdge = TRIGGER_EDGE_BOTH;  // Mesmo comportamento anterior (CHANGE)

  // Dwell
  configPage2.dwellRun = DWELL_DEFAULT;
  configPage2.dwellCrank = 4000;          // 4ms durante partida (mais tempo)
  configPage2.dwellLimit = DWELL_MAX;

  // Timing
  configPage2.crankAdvance = 10;          // 10° BTDC durante partida

  // Rev limiter
  configPage2.revLimitRPM = 60;           // 6000 RPM

  // Idle
  configPage2.idleAdvance = 15;           // 15° BTDC em idle
  configPage2.idleRPM = 80;               // 800 RPM

  // CLT advance correction (4 pontos)
  const int8_t cltBins[] = {-20, 0, 40, 80};
  const int8_t cltVals[] = {5, 3, 0, -2};    // Mais avanço em frio
  for (uint8_t i = 0; i < 4; i++) {
    configPage2.cltAdvBins[i] = cltBins[i];
    configPage2.cltAdvValues[i] = cltVals[i];
  }

  // Ignition output
  configPage2.ignInvert = 0;              // Normal (active low)

  // Engine protection defaults (disabled)
  configPage2.engineProtectEnable = 0;
  configPage2.engineProtectRPM = 70;            // 7000 RPM (if enabled)
  configPage2.engineProtectRPMHysteresis = 3;  // ~300 RPM
  configPage2.engineProtectCutType = ENGINE_PROTECT_CUT_FUEL | ENGINE_PROTECT_CUT_SPARK;

  // ---- Tabelas VE e Ignição ----
  loadDefaultTables();
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

  loadDefaultAFRTable();
}

static void loadDefaultAFRTable() {
  for (uint8_t y = 0; y < TABLE_SIZE_Y; y++) {
    for (uint8_t x = 0; x < TABLE_SIZE_X; x++) {
      afrTable.values[y][x] = pgm_read_byte(&DEFAULT_AFR_TABLE[y][x]);
    }
  }

  for (uint8_t i = 0; i < TABLE_SIZE_X; i++) {
    afrTable.axisX[i] = pgm_read_word(&DEFAULT_VE_AXIS_X[i]);
  }

  for (uint8_t i = 0; i < TABLE_SIZE_Y; i++) {
    afrTable.axisY[i] = pgm_read_byte(&DEFAULT_VE_AXIS_Y[i]);
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
