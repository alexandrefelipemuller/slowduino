# Performance & Roadmap

## Resource Usage
| Resource | Used | Available | % |
|----------|------|-----------|----|
| Flash | ~22 KB | 32 KB | 68% |
| RAM | ~1 100 B | 2 048 B | 53% |
| EEPROM | ~1 000 B | 1 024 B | 97% |

Slowduino deliberately leaves headroom for tuning, logging, and future sensors while still fitting on the tiniest AVR.

## Known Limitations
- Shares the same 16×16 tables and protocol as Speeduino but lacks CAN, VVT, launch control, and boost control.
- Max four cylinders due to the two ignition comparators available even on the Mega board.
- No sequential injection mode yet, although the polling scheme supports wasted-paired fueling with an auxiliary injector.
- Closed-loop tuning relies on a narrowband O2 sensor only (Wideband support is planned).

## Roadmap
- **v0.2 (current)**: fan, pump, IAC, oil/fuel pressure sensors, priming pulse, Simple EGO AFR table, RPM/oil protection.
- **v0.3**: sequential injection, cam sensor sync, full AFR target table, refined logging and diagnostics.
- **v0.4+**: optional SD-based datalogger, richer TunerStudio INI compatibility, basic launch control, investigating ATmega2560 variants with more comparators for 6‑cylinder engines.

## Why it matters
Slowduino gives you a production-ready ECU stack you can flash onto any Uno/Nano. It’s a fantastic base for experimental engines, classroom projects, or cheap aftermarket replacements.
