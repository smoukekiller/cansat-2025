#include "servo_control.h"
#include "globals.h"
#include "config.h"
#include <math.h>

double distance_calc(double lat1, double lng1, double lat2, double lng2) {
  double dx, dy, dz;
  lng1 -= lng2;
  lng1 *= TO_RAD;
  lat1 *= TO_RAD;
  lat2 *= TO_RAD;

  dz = sin(lat1) - sin(lat2);
  dx = cos(lng1) * cos(lat1) - cos(lat2);
  dy = sin(lng1) * cos(lat1);
  return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R * 1000; // *1000 for metres
}

//mid step in angle calculations, calculates distance between points
void CalculateDeltas() {
  delta_x = distance_calc(base_lat, base_lon, base_lat, longitude);
  delta_y = distance_calc(base_lat, base_lon, latitude, base_lon);

  if (base_lon > longitude) {
    delta_x = delta_x * -1;
  }

  if (base_lat > latitude) {
    delta_y = delta_y * -1;
  }
}

//writing to servos accordingly to coordinates
void WriteToServos()
{
  double anglvert;
  bool IsReversed = false;
  double dist = sqrt(delta_y * delta_y + delta_x * delta_x);
  if (dist <= 20 ) {
    wanted_angle_base = 90;
    wanted_angle_antenna = 90;
    //    baseservo.write(90);
    //    antennaservo.write(90);
  } else {
    if (dist != 0)
      anglvert = to_degree * atan(altbar / dist);
    else
      anglvert = 90;

    if (delta_x == 0) {
      if (delta_y >= 0) {
        wanted_angle_base = 90;
        //        baseservo.write(90);
        IsReversed = true;
      } else {
        wanted_angle_base = 90;
        //        baseservo.write(90);
        wanted_angle_antenna = 0;
        //        antennaservo.write(0);
      }
    } else {
      double angle = to_degree * atan(delta_y / delta_x);
      if (angle >= 0) {
        if (delta_x > 0) {
          wanted_angle_base = angle;
          //          baseservo.write(angle);
          IsReversed = true;
        } else {
          wanted_angle_base = angle;
          //          baseservo.write(angle);
          wanted_angle_antenna = 0;
          //          antennaservo.write(0);
        }
      } else {
        if (delta_x > 0) {
          wanted_angle_base = 180 + angle;
          //          baseservo.write(180 + angle);
          wanted_angle_antenna = 0;
          //          antennaservo.write(0);
        } else {
          wanted_angle_base = 180 + angle;
          //          baseservo.write(180 + angle);
          IsReversed = true;
        }
      }
    }

    if (IsReversed) anglvert = 180 - anglvert;
    wanted_angle_antenna = anglvert;
    //    antennaservo.write(anglvert);
  }
}

void slow_rotation()
{
  if (current_angle_base > wanted_angle_base)current_angle_base--;
  else if (current_angle_base < wanted_angle_base)current_angle_base++;
  baseservo.write(current_angle_base);
  if (current_angle_antenna > wanted_angle_antenna)current_angle_antenna--;
  else if (current_angle_antenna < wanted_angle_antenna)current_angle_antenna++;
  antennaservo.write(current_angle_antenna);
}
