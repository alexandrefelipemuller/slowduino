#include "protections.h"

// ---------------------------------------------------------------------------
// Corte de RPM (padrão Speeduino: engineProtectType + hardCutType)
// ---------------------------------------------------------------------------
// O loop principal só calcula a PORCENTAGEM de corte (0-100). Quem decide
// evento a evento (cada disparo do trigger, um canal por vez) é
// protectionCutEvent(), chamada na ISR do trigger.
volatile uint8_t cutPercent = 0;
static bool fullCutLatched = false;
static uint8_t rngState = 0xA5;          // xorshift8, período 255
static uint8_t fuelCutPrev = 0;          // bit por canal: combustível cortado no evento anterior

static void updateRpmCut() {
  uint16_t limit = (uint16_t)configPage2.revLimitRPM * 100;
  if (configPage2.engineProtectEnable && configPage2.engineProtectRPM > 0) {
    uint16_t pLimit = (uint16_t)configPage2.engineProtectRPM * 100;
    if (limit == 0 || pLimit < limit) limit = pLimit;
  }

  uint16_t rpm = currentStatus.RPM;
  uint8_t pct = 0;

  if (limit == 0 || configPage2.engineProtectType == PROTECT_CUT_OFF) {
    fullCutLatched = false;
  } else if (configPage2.hardCutType == HARD_CUT_ROLLING) {
    fullCutLatched = false;
    if (rpm >= limit) {
      pct = 100;
    } else {
      // Delta negativo (RPM/10 abaixo do limite). Começa a cortar em
      // limite + delta[0]*10, como a Speeduino.
      int16_t delta = ((int16_t)rpm - (int16_t)limit) / 10;
      const int8_t* bins = configPage2.rollingProtRPMDelta;
      const uint8_t* vals = configPage2.rollingProtCutPercent;
      if (delta >= bins[0]) {
        if (delta >= bins[3]) {
          pct = vals[3];
        } else {
          pct = vals[0];
          for (uint8_t i = 0; i < 3; i++) {
            if (delta >= bins[i] && delta < bins[i + 1]) {
              int16_t span = (int16_t)bins[i + 1] - bins[i];
              if (span > 0) {
                pct = (uint8_t)((int16_t)vals[i] +
                      (((int16_t)vals[i + 1] - (int16_t)vals[i]) * (delta - bins[i])) / span);
              }
              break;
            }
          }
        }
        if (pct > 100) pct = 100;
      }
    }
  } else {
    // Corte total com histerese
    uint16_t hyst = (uint16_t)configPage2.engineProtectRPMHysteresis * 100;
    uint16_t release = (limit > hyst) ? (limit - hyst) : 0;
    if (fullCutLatched) {
      if (rpm <= release) fullCutLatched = false;
    } else if (rpm >= limit) {
      fullCutLatched = true;
    }
    if (fullCutLatched) pct = 100;
  }

  cutPercent = pct;
}

// Chamada na ISR do trigger, uma vez por evento, com o canal (0/1) do
// evento. Retorna máscara: CUT_FUEL_BIT = não injeta, CUT_IGN_BIT = sem faísca.
// Combustível: sorteado por evento. Ignição:
//  - só ignição / só combustível: sorteio direto;
//  - ambos: a faísca é cortada um evento DEPOIS do combustível do mesmo
//    canal (a faísca queima o que foi injetado no evento anterior), então
//    nunca há faísca sem mistura nem mistura sem faísca por mais de um ciclo.
uint8_t protectionCutEvent(uint8_t ch) {
  uint8_t pct = cutPercent;
  uint8_t type = configPage2.engineProtectType;
  uint8_t chBit = (uint8_t)(1 << ch);
  uint8_t prev = fuelCutPrev & chBit;

  if (pct == 0 && prev == 0) return 0;   // caminho rápido (maioria dos eventos)

  bool cut = false;
  if (pct >= 100) {
    cut = true;
  } else if (pct > 0) {
    uint8_t x = rngState;
    x ^= x << 7; x ^= x >> 5; x ^= x << 3;
    rngState = x;
    cut = (((uint16_t)x * 100) >> 8) < pct;
  }

  uint8_t result = 0;
  if (type == PROTECT_CUT_BOTH) {
    if (cut) { result |= CUT_FUEL_BIT; fuelCutPrev |= chBit; }
    else     { fuelCutPrev &= (uint8_t)~chBit; }
    if (prev) result |= CUT_IGN_BIT;
  } else if (cut) {
    if (type == PROTECT_CUT_FUEL) result |= CUT_FUEL_BIT;
    else if (type == PROTECT_CUT_IGN) result |= CUT_IGN_BIT;
  }
  return result;
}

static bool oilLatched = false;
static uint8_t oilLowCounter = 0;

void protectionProcess() {
  uint8_t mask = 0;

  updateRpmCut();
  if (cutPercent > 0) {
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
