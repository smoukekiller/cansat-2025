#include "globals.h"

Servo baseservo, antennaservo;
SoftwareSerial gpsPort(18, 16);
NMEAGPS gps;

bool panic_mode_reversed = false;
uint8_t panic_mode_angle = 0;
uint64_t panic_mode_timer;
uint64_t RotatingTimer;
uint64_t last_package_recieve_time = 0;
int wanted_angle_base = 0;
int wanted_angle_antenna = 0;
int current_angle_base = 0;
int current_angle_antenna = 0;

float base_p;

double longitude = 21.607290149524736, longitude_base = 21.603956;
double altbar = 0;
double latitude = 63.094387760941004, latitude_base = 63.091125;
double delta_x;
double delta_y;
float t;
float p;
float ax;
float ay;
float az;
float gx;
float gy;
float gz;
float light;
