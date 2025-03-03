#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

//some configs
#define ROTATION_TIME 50 //time in milleseconds that it takes to turn 1 degree
#define PANIC_MODE_TIME 2000    //time in milliseconds that takes the station to go into panic mode after not receiving data
#define PANIC_MODE_SPEED 30     //time in milliseconds that takes to turn 1 degree 
#define PANIC_MODE_DEGREE 45    //vertical angle that the ground station will hold during the panic mode 
#define RADIO_KEY 28            //radio key of the cansat
#define BASE_SERVO_PIN 26
#define ANTENNA_SERVO_PIN 27

//important constants
#define R 6371
#define TO_RAD (3.1415926536 / 180)
#define to_degree (180 / 3.1415926536)

//coordinates of the ground station
#define base_lon 21.608592
#define base_lat 63.094071

//identification bytes
#define TEMPERATURE 0x00
#define PRESSURE    0x01
#define LATITUDE    0x02
#define LONGITUDE   0x03
#define ACCELERATION_X 0x04
#define ACCELERATION_Y 0x05
#define ACCELERATION_Z 0x06
#define GYRO_X 0x07
#define GYRO_Y 0x08
#define GYRO_Z 0x09
#define LIGHT 0x0A
#define BASEB 0x0B

#endif
