# CanSat Satellite Firmware

Embedded firmware running on the CanSat payload.  
Responsible for sensor acquisition, GPS positioning, onboard SD logging, and telemetry transmission to the ground station.

## What it does
- Reads GPS position and sensor data during flight
- Logs telemetry to an SD card
- Sends telemetry packets to the ground station over radio
- Uses numeric field IDs shared with the ground station and map UI

## Files
- `satellite.ino` – main flight firmware
- `config.h` – telemetry IDs, pins, configuration
- `globals.*` – shared state
- `gps.*` – GPS parsing and coordinates
- `sd.*` – SD card logging
- `data_sender.*` – telemetry formatting and transmission

## Telemetry
Telemetry fields are transmitted using numeric IDs defined in `config.h`.  
These IDs must match the ground station firmware and Python map UI.

## Build
Open `satellite.ino` in Arduino IDE, select the correct board, install required libraries, and upload.

## Notes
Code is written for reliability during flight.  
Error handling is minimal to avoid blocking execution.
