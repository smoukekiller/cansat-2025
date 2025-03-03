#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <ESP32Servo.h>

// Declare variables as extern so that they can be defined in globals.cpp
extern Servo baseservo, antennaservo;

extern bool panic_mode_reversed;
extern uint8_t panic_mode_angle;
extern uint64_t panic_mode_timer;
extern uint64_t last_package_recieve_time;
extern uint64_t RotatingTimer;
extern int wanted_angle_base;
extern int wanted_angle_antenna;
extern int current_angle_base;
extern int current_angle_antenna;

extern float base_p;
extern double longitude;
extern double altbar;
extern double latitude;
extern double delta_x;
extern double delta_y;
extern float t;
extern float p;
extern float ax;
extern float ay;
extern float az;
extern float gx;
extern float gy;
extern float gz;
extern float light;

#endif
