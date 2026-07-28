# Performance & Roadmap

## Resource Usage
| Resource | Used | Available | % |
|----------|------|-----------|----|
| Flash | ~21.5 KB | 32 KB | 67% |
| RAM | ~1 464 B | 2 048 B | 71% |
| EEPROM | ~1 000 B | 1 024 B | 97% |

Measured with `avr-size` on an `atmega328p` build (`-Os -ffunction-sections
-fdata-sections -Wl,--gc-sections`). EEPROM is the tight resource: the idle
control parameters were added inside the existing `ConfigPage2` padding, so
they cost **zero** extra EEPROM.

### Interrupt budget
| Source | Rate | Cost |
|--------|------|------|
| Timer1 compare A/B | per ignition/injection event | scheduler, highest priority |
| Timer0 overflow | ~977 Hz | Arduino core (`millis()`) |
| Timer2 compare A | ~3968 Hz | idle PWM, ~2 us (~0.7% CPU), disabled at 0%/100% duty |

The idle PWM ISR can delay a Timer1 ignition compare by at most ~2 us, well
inside the +/-20 us scheduling tolerance.

Slowduino deliberately leaves headroom for tuning, logging, and future sensors while still fitting on the tiniest AVR.

## Known Limitations
- Shares the same 16×16 tables and protocol as Speeduino but lacks CAN, VVT, launch control, and boost control.
- Max four cylinders due to the two ignition comparators available even on the Mega board.
- No sequential injection mode yet, although the polling scheme supports wasted-paired fueling with an auxiliary injector.
- Closed-loop tuning relies on a narrowband O2 sensor only (Wideband support is planned).

## Roadmap
- **v0.2 (current)**: fan, pump, oil/fuel pressure sensors, priming pulse, Simple EGO AFR table, RPM/oil protection, and Speeduino-style idle control (PWM open loop + closed-loop PID, cranking duty, crank-to-run taper, interpolated idle advance) driven by a dedicated Timer2 software PWM.
- **v0.3**: sequential injection, cam sensor sync, full AFR target table, refined logging and diagnostics.
- **v0.4+**: optional SD-based datalogger, richer TunerStudio INI compatibility, basic launch control, investigating ATmega2560 variants with more comparators for 6‑cylinder engines.

## Why it matters
Slowduino gives you a production-ready ECU stack you can flash onto any Uno/Nano. It’s a fantastic base for experimental engines, classroom projects, or cheap aftermarket replacements.
