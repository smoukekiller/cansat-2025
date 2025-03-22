#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <NMEAGPS.h>

// Declare global variables and objects
extern SoftwareSerial gpsPort;
extern NMEAGPS gps;

extern float base_p;
extern float latitude, longitude;
extern uint32_t PrimaryDataTimer, SecondaryDataTimer, GpsTime, SdCardTimer;
extern bool flag;
extern float ta, t, p, ax, ay, az, gx, gy, gz, light;
extern String directory;

#endif
