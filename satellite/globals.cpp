#include "globals.h"

// Define global variables and objects
SoftwareSerial gpsPort(33, 32);
NMEAGPS gps;

float base_p;
float latitude, longitude;
uint32_t PrimaryDataTimer = 0;
uint32_t SecondaryDataTimer = 0;
uint32_t GpsTime = 0;
bool flag = false;
float ta = 0, t = 0, p = 0, ax = 0, ay = 0, az = 0, gx = 0, gy = 0, gz = 0, light = 0;
