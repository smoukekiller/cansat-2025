# CanSat Competition 2025 – CurbAllSpace Team

Codebase for the CurbAllSpace team’s CanSat 2025 entry.

The project consists of three main components:
- Flight firmware running on the CanSat payload
- ESP32-based ground station firmware
- Python map UI for live telemetry visualization and logging

## Repository structure

- `satellite/`  
  Flight firmware for the CanSat payload (GPS, sensors, SD logging, telemetry)

- `ground-station/`  
  ESP32 ground station firmware (radio reception, GPS, antenna control)

- `map/`  
  Python/Tkinter map UI used on the laptop to visualize telemetry and log data

Each component contains its own README with details on functionality and usage.
