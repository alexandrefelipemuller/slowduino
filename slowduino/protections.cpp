#include "protections.h"
#include "scheduler.h"

// Estado interno para manter latch das proteções
static bool rpmProtectionLatched = false;
static bool oilProtectionLatched = false;
static uint8_t oilLowCounter = 0;

static void cutFuelOutputs() {
  injector1Polling.isScheduled = false;
  injector2Polling.isScheduled = false;
  injector3Polling.isScheduled = false;

  if (injector1Polling.isOpen) {
    closeInjector1();
    injector1Polling.isOpen = false;
  }
  if (injector2Polling.isOpen) {
    closeInjector2();
    injector2Polling.isOpen = false;
  }
  if (injector3Polling.isOpen) {
    closeInjector3();
    injector3Polling.isOpen = false;
  }
}

static void cutIgnitionOutputs() {
  clearIgnitionSchedule(&ignitionSchedule1);
  clearIgnitionSchedule(&ignitionSchedule2);
}

void protectionProcess() {
  uint8_t protectionMask = 0;

  // ---- Proteção por RPM ----
  if (configPage2.engineProtectEnable && configPage2.engineProtectRPM > 0) {
    uint16_t rpmLimit = (uint16_t)configPage2.engineProtectRPM * 100;
    uint16_t rpmHyst = (uint16_t)configPage2.engineProtectRPMHysteresis * 100;
    uint16_t rpmRelease = (rpmLimit > rpmHyst) ? (rpmLimit - rpmHyst) : 0;

    if (rpmProtectionLatched) {
      if (currentStatus.RPM <= rpmRelease) {
        rpmProtectionLatched = false;
      }
    } else {
      if (currentStatus.RPM >= rpmLimit) {
        rpmProtectionLatched = true;
      }
    }
  } else {
    rpmProtectionLatched = false;
  }

  if (rpmProtectionLatched) {
    protectionMask |= PROTECTION_RPM_BIT;
  }

  // ---- Proteção por pressão de óleo ----
  if (configPage1.oilPressureProtEnable && configPage1.oilPressureProtThreshold > 0) {
    uint8_t threshold = configPage1.oilPressureProtThreshold;
    uint8_t hyst = configPage1.oilPressureProtHysteresis;
    uint16_t releaseLimit = (uint16_t)threshold + hyst;
    if (releaseLimit > 250) {
      releaseLimit = 250;
    }
    uint8_t releaseThreshold = (uint8_t)releaseLimit;
    uint8_t delayTicks = (configPage1.oilPressureProtDelay == 0)
                           ? 1
                           : configPage1.oilPressureProtDelay;

    if (oilProtectionLatched) {
      if (currentStatus.oilPressure > releaseThreshold) {
        oilProtectionLatched = false;
        oilLowCounter = 0;
      }
    } else {
      if (currentStatus.oilPressure <= threshold) {
        if (++oilLowCounter >= delayTicks) {
          oilProtectionLatched = true;
        }
      } else {
        oilLowCounter = 0;
      }
    }
  } else {
    oilProtectionLatched = false;
    oilLowCounter = 0;
  }

  if (oilProtectionLatched) {
    protectionMask |= PROTECTION_OIL_BIT;
  }

  // Atualiza status globale
  currentStatus.protectionStatus = protectionMask;

  // Aplica cortes conforme configuração
  if (protectionMask &&
      (configPage2.engineProtectCutType & ENGINE_PROTECT_CUT_FUEL)) {
    cutFuelOutputs();
  }

  if (protectionMask &&
      (configPage2.engineProtectCutType & ENGINE_PROTECT_CUT_SPARK)) {
    cutIgnitionOutputs();
  }
}

bool protectionFuelCutActive() {
  return (currentStatus.protectionStatus != 0) &&
         (configPage2.engineProtectCutType & ENGINE_PROTECT_CUT_FUEL);
}

bool protectionSparkCutActive() {
  return (currentStatus.protectionStatus != 0) &&
         (configPage2.engineProtectCutType & ENGINE_PROTECT_CUT_SPARK);
}
