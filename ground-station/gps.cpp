#include "gps.h"
#include "globals.h"
#include <Arduino.h>

void writegps() {
  while (gps.available(gpsPort)) {
    gps_fix fix = gps.read();
    if (fix.valid.location) {
      latitude_base = fix.latitude();
      longitude_base = fix.longitude();
      float altitude = fix.altitude();
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
