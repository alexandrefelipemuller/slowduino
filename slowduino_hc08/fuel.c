/**
 * @file fuel.c
 * @brief Implementacao dos calculos de combustivel - port 1:1 de fuel.cpp
 */

#include "fuel.h"
#include "globals.h"
#include "config.h"
#include "tables.h"

static uint8_t aseCounter = 0;
static uint8_t aseValue = 100;

uint16_t calculateInjection(void) {
  uint8_t ve = getVE();
  uint16_t corrections;
  uint32_t pw;

  currentStatus.VE = ve;

  corrections = calculateCorrections();
  currentStatus.corrections = corrections;

  pw = (uint32_t)configPage1.reqFuel;
  pw = (pw * ve) / 100;
  pw = (pw * currentStatus.MAP) / 100;
  pw = (pw * corrections) / 100;

  pw += configPage1.injOpen;

  if (pw < INJ_MIN_PW) pw = INJ_MIN_PW;
  if (pw > INJ_MAX_PW) pw = INJ_MAX_PW;

  currentStatus.PW1 = (uint16_t)pw;
  currentStatus.PW2 = (uint16_t)pw;
  currentStatus.PW3 = (uint16_t)pw;

  return (uint16_t)pw;
}

uint8_t getVE(void) {
  int16_t ve = getTableValue(&veTable, currentStatus.MAP, currentStatus.RPM);
  if (ve < 0) ve = 0;
  if (ve > 255) ve = 255;
  return (uint8_t)ve;
}

uint16_t calculateCorrections(void) {
  uint16_t total = 100;
  uint8_t wue, ase, clt, bat, ae;

  wue = correctionWUE();
  currentStatus.wueCorrection = wue;
  total = (uint16_t)PERCENT(total, wue);

  ase = correctionASE();
  total = (uint16_t)PERCENT(total, ase);

  clt = correctionCLT();
  total = (uint16_t)PERCENT(total, clt);

  bat = correctionBattery();
  currentStatus.batCorrection = bat;
  total = (uint16_t)PERCENT(total, bat);

  ae = correctionAE();
  total += ae;

  if (total < CORR_MIN) total = CORR_MIN;
  if (total > CORR_MAX) total = CORR_MAX;

  return total;
}

uint8_t correctionWUE(void) {
  int8_t temp = currentStatus.coolant;
  uint8_t i;

  if (!BIT_CHECK(currentStatus.engineStatus, ENGINE_WARMUP)) {
    return 100;
  }

  for (i = 0; i < 5; i++) {
    if (temp >= configPage1.wueBins[i] && temp < configPage1.wueBins[i + 1]) {
      int8_t t1 = configPage1.wueBins[i];
      int8_t t2 = configPage1.wueBins[i + 1];
      uint8_t v1 = configPage1.wueValues[i];
      uint8_t v2 = configPage1.wueValues[i + 1];
      return (uint8_t)(v1 + (int32_t)(temp - t1) * (v2 - v1) / (t2 - t1));
    }
  }

  if (temp < configPage1.wueBins[0]) {
    return configPage1.wueValues[0];
  }
  return configPage1.wueValues[5];
}

uint8_t correctionASE(void) {
  if (!BIT_CHECK(currentStatus.engineStatus, ENGINE_ASE)) {
    return 100;
  }
  return aseValue;
}

void startASE(void) {
  aseCounter = configPage1.aseCount;
  aseValue = configPage1.asePct;
  BIT_SET(currentStatus.engineStatus, ENGINE_ASE);
}

void decrementASE(void) {
  if (aseCounter > 0) {
    aseCounter--;

    if (configPage1.aseCount > 0) {
      uint16_t step = (uint16_t)(configPage1.asePct - 100) / configPage1.aseCount;
      aseValue = (uint8_t)(aseValue - step);

      if (aseValue <= 100) {
        aseValue = 100;
        BIT_CLEAR(currentStatus.engineStatus, ENGINE_ASE);
      }
    }
  } else {
    aseValue = 100;
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_ASE);
  }
}

uint8_t correctionAE(void) {
  if (configPage1.aeMode != AE_MODE_TPS) {
    return 0;
  }

  if (currentStatus.TPSdot > configPage1.aeThresh) {
    uint8_t ae;
    BIT_SET(currentStatus.engineStatus, ENGINE_ACC);

    ae = (uint8_t)(configPage1.aePct - 100);

    if (currentStatus.TPSdot > ((int16_t)configPage1.aeThresh * 3)) {
      ae = (uint8_t)(ae * 2);
    }

    return ae;
  }

  BIT_CLEAR(currentStatus.engineStatus, ENGINE_ACC);
  return 0;
}

uint8_t correctionCLT(void) {
  if (currentStatus.coolant > 100) {
    int8_t reduction = (int8_t)((currentStatus.coolant - 100) / 5);
    if (reduction > 5) reduction = 5;
    return (uint8_t)(100 - reduction);
  }
  return 100;
}

uint8_t correctionBattery(void) {
  uint8_t voltage = currentStatus.battery10;

  if (voltage < 110) {
    return 110;
  } else if (voltage < 120) {
    return 105;
  } else if (voltage > 150) {
    return 97;
  }
  return 100;
}

void updateEngineStatus(void) {
  static bool firstRun = true;

  if (currentStatus.RPM > 0 && currentStatus.RPM < ((uint16_t)configPage1.crankRPM * 10)) {
    BIT_SET(currentStatus.engineStatus, ENGINE_CRANK);
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_RUN);
  } else if (currentStatus.RPM >= ((uint16_t)configPage1.crankRPM * 10)) {
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_CRANK);
    BIT_SET(currentStatus.engineStatus, ENGINE_RUN);

    if (firstRun) {
      startASE();
      firstRun = false;
    }
  } else {
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_CRANK);
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_RUN);
  }

  if (currentStatus.coolant < 60) {
    BIT_SET(currentStatus.engineStatus, ENGINE_WARMUP);
  } else {
    BIT_CLEAR(currentStatus.engineStatus, ENGINE_WARMUP);
  }
}
