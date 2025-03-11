#include "data_sender.h"
#include "globals.h"
#include "config.h"
#include "CanSatNeXT.h"
#include <Arduino.h>
#include <string.h>

void SendPackage(char initial, uint32_t timeStamp, float payload) {
  char dataArray[1 + 4 + 4];
  dataArray[0] = initial;

  appendFile(directory + String((int)initial) + ".csv", String(timeStamp) + ","+String(payload, 6) + "\r\n");
//  Serial.println(directory + String((int)initial) + ".csv");
//  Serial.println(String(timeStamp) + ","+String(payload, 6) + "\r\n");
//  Serial.println(initial);
  memcpy(&dataArray[1], &timeStamp, 4);
  memcpy(&dataArray[5], &payload, 4);
  sendData(dataArray, 9);
  Serial.println(initial, HEX);
}

void SendPressure() {
  uint32_t Time = millis();
  p = readPressure();
  SendPackage(PRESSURE, Time, p);
}

void SendTemperature() {
  uint32_t Time = millis();
  t = readTemperature();
  SendPackage(TEMPERATURE, Time, t);
}

void SendLatitude() {
  uint32_t Time = millis();
  SendPackage(LATITUDE, GpsTime, latitude);
}

void SendLongitude() {
  SendPackage(LONGITUDE, GpsTime, longitude);
}

void SendBaseP() {
  uint32_t Time = millis();
  SendPackage(BASEP, Time, base_p);
}

void SendLight() {
  uint32_t Time = millis();
  light = analogReadVoltage(LDR);
  SendPackage(LIGHT, Time, light);
}

void SendGyro() {
  uint32_t Time = millis();
  ax = readAccelX();
  ay = readAccelY();
  az = readAccelZ();
  gx = readGyroX();
  gy = readGyroY();
  gz = readGyroZ();

  SendPackage(ACCELERATION_X, Time, ax);
  SendPackage(ACCELERATION_Y, Time, ay);
  SendPackage(ACCELERATION_Z, Time, az);
  SendPackage(GYRO_X, Time, gx);
  SendPackage(GYRO_Y, Time, gy);
  SendPackage(GY2O_Z, Time, gz);
}
