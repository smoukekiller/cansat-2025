#include "panic_mode.h"
#include "globals.h"
#include "config.h"
#include <Arduino.h>

bool CheckForPanic() {
  if ((millis() - last_package_recieve_time) >= PANIC_MODE_TIME) return true;
  return false;
}

void WriteServosPanic() {
  // Example panic mode logic (you can expand this as needed)
  if ((millis() - panic_mode_timer) >= (PANIC_MODE_SPEED)) {
    
    antennaservo.write(panic_mode_angle);
    panic_mode_timer = millis();
  }
}
