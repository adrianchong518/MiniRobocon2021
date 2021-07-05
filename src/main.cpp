#include <Arduino.h>
#include <Wire.h>

#include "hardware/hardware.h"
#include "control/control.h"

#define IS_TIMING

void setup() {
  Serial.begin(115200);
  Wire.begin();

  hardware::init();

  while (DEBUG && Serial.read() != '\n')
    ;
  hardware::calibrate();

  while (DEBUG && Serial.read() != '\n')
    ;
  hardware::startingPosition();

  control::init();

  LOG_INFO("<Main>\t\tReady");
}

#ifdef IS_TIMING
unsigned long start, end;
void loop() {
  start = micros();
  hardware::loop();
  control::loop();
  end = micros();
  LOG_INFO("<Main>\t\tTime Taken:\t" + String(end - start) + "\tus");
}
#else
unsigned long start, end;
void loop() {
  hardware::loop();
  control::loop();
}
#endif