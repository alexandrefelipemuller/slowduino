# Overview

## What is Slowduino?
Slowduino is a super low-cost, open-source engine control firmware inspired by Speeduino and tailored for humble AVR hardware. It runs on ATmega328p boards (Uno/Nano) while keeping the protocol, tuning workflow, and feature set that Speeduino users expect. The project is aimed at hobbyists, educators, and tuners who want a trustworthy ECU without buying expensive hardware.

## Why Slowduino?
- **Pocket-friendly build**: fits in an Uno or Nano and still controls fuel, spark, sensors, fan, pump, and idle without proprietary components.
- **Speeduino-compatible tuning**: uses the same 16×16 VE/Ignition maps, CRC-aware protocol, and TunerStudio pages so you can drop it into an existing workflow.
- **Deterministic control**: scheduler in the ISR keeps timing error below 20 µs for ignition and injection events even at 8 000 RPM.
- **Rich sensor suite**: supports MAP, TPS, CLT, IAT, O2, fuel/ oil pressure, as well as fan, pump, and IAC outputs.
- **Modern protections**: RPM cuts and oil-pressure monitoring (inspired by Speeduino) help prevent runaway conditions on basic hardware.

## Compatibility snapshot
| Option | MCU | Cylinders | Trigger | Notes |
|--------|-----|-----------|---------|-------|
| Slowduino PCB | ATmega328p | 1-4 (wasted) | Missing tooth or distributor | Fits Uno/Nano; 3 injector channels (2 banks + aux).
| Speeduino v0.4 board | ATmega2560 | 1-4 | Same as Speeduino firmware | Uses only 2 ignition comparators; good for protocol verification.

Slowduino is the short path between a cheap AVR board and a living, breathing engine.
