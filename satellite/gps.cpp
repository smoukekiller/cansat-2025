#include "gps.h"
#include "globals.h"
#include <Arduino.h>

void writegps() {
  while (gps.available(gpsPort)) {
    gps_fix fix = gps.read();
    if (fix.valid.location) {
      flag = true;
      latitude = fix.latitude();
      longitude = fix.longitude();
      float altitude = fix.altitude();
      GpsTime = millis();
      Serial.print("LA:");
      Serial.print(latitude, 6);
      Serial.print(",");
      Serial.print("LG:");
      Serial.print(longitude, 6);
      Serial.print(",");
      Serial.print("AL:");
      Serial.println(altitude, 6);
    }
  }
}
