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

  if (millis() - SdCardTimer >= SD_CARD_TIME)
  {
    uint32_t Time = millis();
    p = readPressure();
    t = readTemperature();
    light = analogReadVoltage(LDR);
    ax = readAccelX();
    ay = readAccelY();
    az = readAccelZ();
    gx = readGyroX();
    gy = readGyroY();
    gz = readGyroZ();
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








#define TEMPERATURE 0x00
#define PRESSURE 0x01
#define LATITUDE 0x02
#define LONGITUDE 0x03
#define ACCELERATION_X 0x04
#define ACCELERATION_Y 0x05
#define ACCELERATION_Z 0x06
#define GYRO_X 0x07
#define GYRO_Y 0x08
#define GYRO_Z 0x09
#define LIGHT 0x0A
#define BASEP 0x0B

appendFile(directory + String((int)initial) + ".csv", String(timeStamp) + ","+String(payload, 6) + "\r\n");
