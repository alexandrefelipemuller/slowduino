# Communication & Debug

## TunerStudio Protocol (Modern + Legacy)
- **Baud rate**: 115200 bps
- **Commands**: `Q` (version), `A` (realtime data), `V`/`I` (read VE/Ign tables), `W`/`X` (write VE/Ign), `B` (burn EEPROM), `T` (test comms).
- **Realtime struct**: the firmware sends `Statuses` as defined in `globals.h` (RPM, MAP, TPS, coolant, IAT, battery10, PW1, advance, VE, protections, etc.).
- **CRC32 aware**: page writes match the Speeduino framing so TunerStudio treats Slowduino as a normal Speeduino device.

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
