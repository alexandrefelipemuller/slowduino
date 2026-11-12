#include "protections.h"

static bool rpmLatched = false;
static bool oilLatched = false;
static uint8_t oilLowCounter = 0;

void protectionProcess() {
  uint8_t mask = 0;

  if (configPage2.engineProtectEnable && configPage2.engineProtectRPM > 0) {
    uint16_t limit = (uint16_t)configPage2.engineProtectRPM * 100;
    uint16_t hyst = (uint16_t)configPage2.engineProtectRPMHysteresis * 100;
    uint16_t release = (limit > hyst) ? (limit - hyst) : 0;

    if (rpmLatched) {
      if (currentStatus.RPM <= release) {
        rpmLatched = false;
      }
    } else if (currentStatus.RPM >= limit) {
      rpmLatched = true;
    }
  } else {
    rpmLatched = false;
  }

  if (rpmLatched) {
    mask |= PROTECTION_RPM_BIT;
  }

  if (configPage1.oilPressureProtEnable && configPage1.oilPressureProtThreshold > 0) {
    uint8_t threshold = configPage1.oilPressureProtThreshold;
    uint8_t hyst = configPage1.oilPressureProtHysteresis;
    uint16_t releaseLimit = (uint16_t)threshold + hyst;
    if (releaseLimit > 250) {
      releaseLimit = 250;
    }
    uint8_t releaseThreshold = (uint8_t)releaseLimit;
    uint8_t delayTicks = (configPage1.oilPressureProtDelay == 0) ? 1 : configPage1.oilPressureProtDelay;

    if (oilLatched) {
      if (currentStatus.oilPressure > releaseThreshold) {
        oilLatched = false;
        oilLowCounter = 0;
      }
    } else if (currentStatus.oilPressure <= threshold) {
      if (++oilLowCounter >= delayTicks) {
        oilLatched = true;
      }
    } else {
      oilLowCounter = 0;
    }
  } else {
    oilLatched = false;
    oilLowCounter = 0;
  }

  if (oilLatched) {
    mask |= PROTECTION_OIL_BIT;
  }

  currentStatus.protectionStatus = mask;
}

bool protectionRPMActive() {
  return (currentStatus.protectionStatus & PROTECTION_RPM_BIT) != 0;
}

bool protectionOilActive() {
  return (currentStatus.protectionStatus & PROTECTION_OIL_BIT) != 0;
}
