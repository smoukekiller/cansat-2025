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
  GpsTime = millis();
  SdCardTimer = millis();

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
  if (millis() - SdCardTimer >= SD_CARD_TIME) {
    uint32_t timeStamp = millis();
    SdCardTimer = millis();
    // Read sensor values
    float t     = readTemperature();
    float p     = readPressure();
    float light = analogReadVoltage(LDR);
    float ax    = readAccelX();
    float ay    = readAccelY();
    float az    = readAccelZ();
    float gx    = readGyroX();
    float gy    = readGyroY();
    float gz    = readGyroZ();

    // Append each sensor's value to its respective file using defined constants for file names
    appendFile(directory + String((int)TEMPERATURE) + ".csv", String(timeStamp) + "," + String(t, 6) + "\r\n");
    appendFile(directory + String((int)PRESSURE)    + ".csv", String(timeStamp) + "," + String(p, 6) + "\r\n");
    appendFile(directory + String((int)LIGHT)       + ".csv", String(timeStamp) + "," + String(light, 6) + "\r\n");
    appendFile(directory + String((int)ACCELERATION_X) + ".csv", String(timeStamp) + "," + String(ax, 6) + "\r\n");
    appendFile(directory + String((int)ACCELERATION_Y) + ".csv", String(timeStamp) + "," + String(ay, 6) + "\r\n");
    appendFile(directory + String((int)ACCELERATION_Z) + ".csv", String(timeStamp) + "," + String(az, 6) + "\r\n");
    appendFile(directory + String((int)GYRO_X)       + ".csv", String(timeStamp) + "," + String(gx, 6) + "\r\n");
    appendFile(directory + String((int)GYRO_Y)       + ".csv", String(timeStamp) + "," + String(gy, 6) + "\r\n");
    appendFile(directory + String((int)GYRO_Z)       + ".csv", String(timeStamp) + "," + String(gz, 6) + "\r\n");
  }

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
