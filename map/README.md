# CanSat Map UI (Ground Station)

Small Python/Tkinter tool used in the CanSat ground station to visualize live telemetry on a map and log received values to CSV.

## What it does
- Reads telemetry from the ESP32 ground station over USB serial (default: `/dev/ttyUSB0`, 115200 baud)
- Expects lines in the format: (field_id) (timestamp) (value)
- Displays:
- CanSat position (lat/lon)
- Ground station position (lat/lon)
- Telemetry values in a sidebar
- Distance between CanSat and ground station (haversine)
- Logs each field to CSV

## Run
```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
python3 main.py
