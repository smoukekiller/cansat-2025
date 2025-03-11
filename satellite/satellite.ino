#include "config.h"
#include "globals.h"
#include "data_sender.h"
#include "gps.h"
#include "sd.h"



#include <NMEAGPS.h>
#include "CanSatNeXT.h"
void setup() {
  Serial.begin(115200);
  gpsPort.begin(9600);
  CanSatInit(RADIO_KEY);
  delay(500);
  init_sd();

  SecondaryDataTimer = millis();
  PrimaryDataTimer = millis();

  // Calculate base pressure
  float sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += readPressure();
    delay(500);
    Serial.println(sum);
  }
  base_p = sum / 5;
}

void loop() {
  writegps();

  if (millis() - PrimaryDataTimer >= PRIMARY_DATA_TIME) {
    PrimaryDataTimer = millis();
    Serial.println("PDATA");
    SendPressure();
    SendLatitude();
    SendLongitude();
  }

  if (millis() - SecondaryDataTimer >= SECONDARY_DATA_TIME) {
    Serial.println("SDATA");
    SecondaryDataTimer = millis();
    SendLight();
    SendBaseP();
    SendTemperature();
    SendGyro();
  }
}
