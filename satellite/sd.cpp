#include "globals.h"
#include "config.h"
#include "CanSatNeXT.h"
#include <Arduino.h>
#include <string.h>
// Constants for data identifiers
//#define TEMPERATURE 0x00
//#define PRESSURE 0x01
//#define LATITUDE 0x02
//#define LONGITUDE 0x03
//#define ACCELERATION_X 0x04
//#define ACCELERATION_Y 0x05
//#define ACCELERATION_Z 0x06
//#define GYRO_X 0x07
//#define GYRO_Y 0x08
//#define GYRO_Z 0x09
//#define LIGHT 0x0A
//#define BASEP 0x0B
bool init_sd()
{
  if (SDCardPresent())
  {
    int counter = 0;
    String filename;
    while (1)
    {
      filename = "/" + String(counter) + "/" + String("init.txt");
      bool flag = fileExists(filename);
      if (!flag)
      {
        directory = "/" + String(counter) + "/";
        newDir("/" + String(counter));
        writeFile(filename, "1");
        for (int i = 0; i < 12; i++)
        {
          writeFile(directory + String(i) + ".csv", "timestamp,data\r\n");
        }
        return true;
      }
      counter++;
    }
  }
  else return false;
}
