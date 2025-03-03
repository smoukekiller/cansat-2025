#ifndef DATA_SENDER_H
#define DATA_SENDER_H
#include <Arduino.h>

void SendPackage(char initial, uint32_t timeStamp, float payload);
void SendPressure();
void SendTemperature();
void SendLatitude();
void SendLongitude();
void SendBaseP();
void SendLight();
void SendGyro();

#endif
