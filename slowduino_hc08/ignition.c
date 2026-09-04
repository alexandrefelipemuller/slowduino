/**
 * @file ignition.c
 * @brief Implementacao dos calculos de ignicao - port 1:1 de ignition.cpp
 */

#include "ignition.h"
#include "globals.h"
#include "config.h"
#include "tables.h"

int8_t calculateAdvance(void) {
  int8_t advance;

  if (BIT_CHECK(currentStatus.engineStatus, ENGINE_CRANK)) {
    return configPage2.crankAdvance;
  }

  advance = getBaseAdvance();
  advance = applyAdvanceCorrections(advance);
  advance = applyRevLimiter(advance);

  if (advance < IGN_MIN_ADVANCE) advance = IGN_MIN_ADVANCE;
  if (advance > IGN_MAX_ADVANCE) advance = IGN_MAX_ADVANCE;

  return advance;
}

int8_t getBaseAdvance(void) {
  int16_t advance = getTableValue(&ignTable, currentStatus.MAP, currentStatus.RPM);
  return (int8_t)advance;
}

int8_t applyAdvanceCorrections(int8_t baseAdvance) {
  int8_t corrected = baseAdvance;

  corrected = (int8_t)(corrected + correctionCLTAdvance());

  if (isIdleAdvanceActive()) {
    if (configPage2.idleAdvEnabled == IDLE_ADV_SWITCHED) {
      corrected = correctionIdleAdvance();
    } else {
      corrected = (int8_t)(corrected + correctionIdleAdvance());
    }
  }

  return corrected;
}

bool isIdleAdvanceActive(void) {
  if (configPage2.idleAdvEnabled == IDLE_ADV_OFF) return false;
  if (currentStatus.RPM == 0) return false;

  if (currentStatus.TPS > configPage2.idleAdvTPS) return false;
  if (currentStatus.RPM > ((uint16_t)configPage2.idleAdvRPM * 100U)) return false;

  return true;
}

int8_t correctionCLTAdvance(void) {
  int8_t temp = currentStatus.coolant;
  uint8_t i;

  for (i = 0; i < 3; i++) {
    if (temp >= configPage2.cltAdvBins[i] && temp < configPage2.cltAdvBins[i + 1]) {
      int8_t t1 = configPage2.cltAdvBins[i];
      int8_t t2 = configPage2.cltAdvBins[i + 1];
      int8_t v1 = configPage2.cltAdvValues[i];
      int8_t v2 = configPage2.cltAdvValues[i + 1];

      return (int8_t)(v1 + (int32_t)(temp - t1) * (v2 - v1) / (t2 - t1));
    }
  }

  if (temp < configPage2.cltAdvBins[0]) {
    return configPage2.cltAdvValues[0];
  }
  return configPage2.cltAdvValues[3];
}

int8_t correctionIdleAdvance(void) {
  int16_t delta = (int16_t)currentStatus.CLIdleTarget - (int16_t)currentStatus.RPM;
  if (delta < 0) delta = 0;

  return lookupCurveI8(configPage2.idleAdvBins, configPage2.idleAdvValues, 4, (int16_t)(delta / 10));
}

int8_t applyRevLimiter(int8_t advance) {
  uint16_t limitRPM = (uint16_t)configPage2.revLimitRPM * 100;

  if (currentStatus.RPM >= limitRPM) {
    static bool cutState = false;
    cutState = !cutState;

    if (cutState) {
      return IGN_MIN_ADVANCE;
    }
  }

  return advance;
}

uint16_t calculateDwell(void) {
  uint16_t dwell;

  if (BIT_CHECK(currentStatus.engineStatus, ENGINE_CRANK)) {
    dwell = configPage2.dwellCrank;
  } else {
    dwell = configPage2.dwellRun;
  }

  if (dwell > configPage2.dwellLimit) {
    dwell = configPage2.dwellLimit;
  }

  if (dwell < DWELL_MIN) dwell = DWELL_MIN;
  if (dwell > DWELL_MAX) dwell = DWELL_MAX;

  return dwell;
}
