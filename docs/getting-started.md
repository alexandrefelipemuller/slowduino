# Getting Started

## 1. Gather the Hardware
- ATmega328p board (Arduino Uno, Nano, or Pro Mini) or a Speeduino v0.4 Arduino Mega.
- MAP sensor (e.g. MPX4250) with 5 V supply.
- TPS potentiometer (5 kΩ) with mechanical stop switch.
- Two 10 kΩ NTC thermistors for CLT and IAT.
- Crankshaft position sensor (Hall or inductive) with a trigger wheel (36-1, 60-2, etc.).
- Oil and fuel pressure sensors (0-5 V output, 0-1000 kPa range).
- Injector drivers (ULN2003, MOSFET, or low-side transistors).
- Ignition drivers (BIP373 or equivalent) for two coils.
- Fan relay, pump relay, idle air control valve or PWM solenoid, and 5 V regulator with protection components.

## 2. Configure the Firmware
Before compiling, set the board type in `slowduino/board_config.h`:

```cpp
// For a Uno/Nano (Slowduino)
#define BOARD_SLOWDUINO
// #define BOARD_SPEEDUINO_V04

// Or for a Speeduino v0.4 Mega board
// #define BOARD_SLOWDUINO
#define BOARD_SPEEDUINO_V04
```

## 3. Uploading the Firmware
### Slowduino (Uno/Nano)
1. Open `slowduino.ino` in the Arduino IDE.
2. Select **Tools → Board → Arduino Uno** (or Nano/Pro Mini depending on your hardware).
3. Choose the correct COM port.
4. Click Upload.

### Speeduino v0.4 (Mega2560)
1. Switch the board definition as shown above.
2. Select **Arduino Mega 2560** in the IDE.
3. Upload via USB.

> ⚠️ The Slowduino build only drives two ignition channels and supports up to four cylinders; the Mega board is only used for protocol testing or hardware validation in this configuration.

## 4. First Power-Up
- The firmware will auto-load default tables and config values on first boot.
- It will wait for trigger sync before running fuel/ignition.
- The serial TX/RX LEDs blink as communication happens.

## 5. Basic Calibration
1. **TPS**: Set `tpsMin` with the throttle closed and `tpsMax` with wide-open throttle. Use TunerStudio or the calibration routine.
2. **MAP**: Validate the atmospheric reading (~100 kPa) with the engine off.
3. **Trigger**: Define `triggerPattern`, `triggerTeeth`, `triggerMissing`, `triggerAngle`, and `triggerEdge` according to your wheel.
4. **Required Fuel**: Estimate using displacement and injector flow: `reqFuel = (displacement / cylinders) / injector_flow * 1000` (ms).

## 6. Trigger Configuration Tips
- Use Missing Tooth for wheels with gaps or Basic Distributor for a single pulse per revolution.
- Enter the total tooth count and missing tooth count (e.g., 36/1, 60/2) in TunerStudio — Slowduino uses the same fields as Speeduino.
- Adjust `triggerAngle` by finding the first sync tooth relative to TDC using a timing light.
- Choose the edge (Rising/Falling/Both) that matches your crank signal conditioner.
- Save/burn the configuration so the trigger ISR can detect gaps accurately and schedule fuel/ignition events.
