#include <Arduino.h>
#include <Wire.h>

#include "hardware/hardware.h"
#include "control/control.h"

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

  LOG_DEBUG("<Main> Ready");
}

unsigned long start, end;
void loop() {
  start = micros();
  hardware::loop();
  control::loop();
  end = micros();
  LOG_INFO("<Main>\tTime Taken:\t" + String(end - start) + "\tus");
}