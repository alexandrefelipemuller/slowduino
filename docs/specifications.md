# Technical Specifications

## Supported Hardware
- **Slowduino (ATmega328p Uno/Nano/Pro Mini)**: 16 MHz clock, 32 KB flash, 2 KB RAM, 1 KB EEPROM; firmware ~22 KB flash, ~1.1 KB RAM.
- **Speeduino v0.4 board (ATmega2560)**: Same codebase runs for testing/protocol validation; still limited to two ignition outputs and four cylinders.
- **Trigger**: Missing-tooth wheels (36-1, 60-2, etc.) or basic distributor pulses with configurable edge (Rising/Falling/Both).

## Sensors & Actuators
- High-speed I/O for MAP, TPS, CLT (NTC), IAT (NTC), narrowband O2, battery, fuel pressure, and oil pressure sensors.
- Outputs for two ignition channels (wasted spark), three injector channels (two primary banks + optional aux), fan, pump, and idle air control.
- RPM calculation derived from revolution time with 16 µs timer resolution; triggers permit <0.3° error at 8 000 RPM.

## Tables and Corrections
- **VE Table & Ignition Table**: 16×16 grids with independent RPM (X) and MAP (Y) axes; bilinear interpolation in integer math.
- **Fuel corrections**: Warm-up enrichment (6-point), ASE, acceleration enrichment (TPSdot), CLT, and battery compensation.
- **Ignition corrections**: CLT advance (4-point), idle advance, rev limiter (TTL-based soft cut), and dwell protection.
- **Closed-loop O2**: Simple EGO algorithm modeled after Speeduino, using page 5 AFR targets, with configurable delay, RPM/TPS window, and hysteresis.

## Timing and Scheduling
- Timer1 run at 62.5 kHz (16 µs ticks); injection scheduling happens in the trigger ISR with a 90° BTDC offset and polling loop for actual injector control (±100 µs accuracy).
- Ignition dwell computed per revolution; scheduler enforces max 50 % of a revolution and guards against scheduling events that are too close.
- MSP (loop) tasks run at 4 Hz (slow sensors & auxiliaries), 15 Hz (RPM/state), and 30 Hz (fast sensors) to balance responsiveness and CPU load.

## EEPROM Layout
| Offset | Bytes | Contents |
|--------|-------|----------|
| 0 | 1 | EEPROM version ID |
| 10 | 256 | VE table values |
| 266 | 32 | VE RPM axis (16 × uint16) |
| 298 | 16 | VE MAP axis (16 × uint8) |
| 314 | 256 | Ignition table values |
| 570 | 32 | Ignition RPM axis |
| 602 | 16 | Ignition MAP axis |
| 618 | 128 | ConfigPage1 (fuel & sensors) |
| 746 | 128 | ConfigPage2 (ignition & protection) |
| 874 | 64 | Reserved CLT table area |
| 938 | 64 | Reserved IAT table area |
| 1002+ | ~22 | Expansion (AFR, spare)

Slowduino keeps the EEPROM layout aligned with Speeduino so TunerStudio and the Speeduino toolchain can read/write data directly.
