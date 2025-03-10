# CanSat Competition 2025 - CurbAllSpace Team

This repository contains the code base for the **CurbAllSpace** team's entry in the **CanSat 2025** competition.

---

## Project Structure

```plaintext
cansat-2025/
├── map/                 # Python script for data processing and display
│   └──                  # Run on a laptop, uses tkintermapview library
├── satellite/           # Code for the satellite's ESP board
│   └──                  # Collects and transmits data to the ground station
└── ground-station/      # Manages data reception and hardware control
    └──                  # Controls servos for antenna adjustment
