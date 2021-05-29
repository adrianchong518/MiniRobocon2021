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

void loop() {
  hardware::loop();
  control::loop();
}