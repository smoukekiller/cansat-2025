#include "data_processing.h"
#include "globals.h"
#include "config.h"

#include <Arduino.h>
#include <string.h>

void onBinaryDataReceived(const uint8_t *data, int len) {
  float payload;
  uint32_t timestamp;
  uint8_t initializer = data[0];
  memcpy(&timestamp, &data[1], 4);
  memcpy(&payload, &data[5], 4);

  //sends data to PC
  Serial.println(String(initializer) + " " + String(timestamp) + " " + String(payload, 6));

  //writes important data down
  switch (data[0])
  {
    case PRESSURE:
      p = payload;
      break;
    case LATITUDE:
      latitude = payload;
      break;
    case LONGITUDE:
      longitude = payload;
      break;
  }

  last_package_recieve_time = millis(); // Update last package receive time when data arrives
}
