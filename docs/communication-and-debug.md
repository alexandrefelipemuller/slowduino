# Communication & Debug

## TunerStudio Protocol (Modern + Legacy)
- **Baud rate**: 115200 bps
- **Commands**: `Q` (version), `A` (realtime data), `V`/`I` (read VE/Ign tables), `W`/`X` (write VE/Ign), `B` (burn EEPROM), `T` (test comms).
- **Realtime struct**: the firmware sends `Statuses` as defined in `globals.h` (RPM, MAP, TPS, coolant, IAT, battery10, PW1, advance, VE, protections, etc.).
- **CRC32 aware**: page writes match the Speeduino framing so TunerStudio treats Slowduino as a normal Speeduino device.

## Idle Control Offsets

The repository ships no `.ini`, so these offsets are what you need to expose
idle control in your own TunerStudio definition. They live in **page 4**
(`configPage2`), served byte-by-byte by `readPageByte`/`writePageByte`.

| Offset | Field | Type | Scale / notes |
|--------|-------|------|---------------|
| 12 | `idleAdvance` | S08 | Legacy, no longer used in the advance calculation |
| 13 | `idleRPM` | U08 | Reserved (the live target comes from `iacCLValues`) |
| 28 | `iacAlgorithm` | U08 | 0 = None, 1 = PWM open loop, 2 = PWM OL+CL |
| 29 | `idleFreq` | U08 | Hz / 2 (80 = 160 Hz) |
| 30-33 | `iacBins[4]` | S08 | Coolant °C, shared axis for the next two curves |
| 34-37 | `iacOLPWMVal[4]` | U08 | Open-loop duty % |
| 38-41 | `iacCLValues[4]` | U08 | Closed-loop target RPM / 10 |
| 42-45 | `iacCrankBins[4]` | S08 | Coolant °C during cranking |
| 46-49 | `iacCrankDuty[4]` | U08 | Cranking duty % |
| 50 | `idleKP` | U08 | Gain × 1/16 |
| 51 | `idleKI` | U08 | Gain × 1/16 |
| 52 | `idleKD` | U08 | Gain × 1/16 (default 0) |
| 53 | `iacCLminValue` | U08 | Minimum closed-loop duty % |
| 54 | `iacCLmaxValue` | U08 | Maximum closed-loop duty % |
| 55 | `idleTaperTime` | U08 | Crank-to-run taper, tenths of a second |
| 56 | `iacTPSlimit` | U08 | TPS % above which the PID integral resets |
| 57 | `idleAdvEnabled` | U08 | 0 = Off, 1 = Added, 2 = Switched |
| 58 | `idleAdvTPS` | U08 | Max TPS % for idle advance |
| 59 | `idleAdvRPM` | U08 | Max RPM / 100 for idle advance |
| 60-63 | `idleAdvBins[4]` | U08 | (target − actual) RPM / 10 |
| 64-67 | `idleAdvValues[4]` | S08 | Advance in degrees (may be negative) |

Realtime log fields use the same offsets as Speeduino: **38** = `idleLoad`
(valve duty %) and **92** = `CLIdleTarget` (target RPM / 10).

Bumping `EEPROM_DATA_VERSION` to 4 reseeds these defaults on first boot after
flashing.

## Debugging Tools
- Enable `#define DEBUG_ENABLED` in `config.h` to see diagnostics such as `RPM`, `Sync`, `MAP`, `TPS`, `CLT`, `PW`, and `advance` once every second.
- The `Serial` output helps correlate sensor readings with fuel and spark calculations.
- `LED_BUILTIN` (pin D13) can be repurposed for revolution heartbeat if you need a visible sync signal.
- TX/RX LEDs blink whenever the serial buffer is active.

## Common Diagnostic Scenarios
| Symptom | Checks |
|---------|--------|
| Engine won’t sync | Verify trigger wheel/pin wiring, ensure `triggerTeeth` & `missing` match the physical wheel, check signal shape with an oscilloscope, adjust debounce filtering if needed. |
| Injectors stay off | Confirm driver wiring, test the injector pins with a simple LED/test load, double-check `reqFuel` value and injector drivers. |
| No spark | Validate coil driver wiring, confirm `configPage2.ignInvert` matches your hardware, ensure dwell is between 3-6 ms and rev limiter isn’t trimming it. |
| O2 loop never activates | Wait until coolant warms past `egoTemp`, RPM above `egoRPM`, TPS below `egoTPSMax`, and the narrowband reading remains within `egoMin`/`egoMax`. |

## Protections Feedback
- `statuses.protectionStatus` reports active protections (RPM, oil pressure).
- `engineProtectCutType` allows you to choose fuel cut, spark cut, or both so you know what each bit means when monitoring.

Use these bits in your logging/tuning sessions to understand when the ECU is protecting itself vs. simply running in closed loop.
