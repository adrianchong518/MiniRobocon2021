#include <Arduino.h>

#include "hardware/hardware.h"
#include "control/control.h"

#define WAIT false

void setup() {
  Serial.begin(115200);

  hardware::init();

  while (WAIT && Serial.read() != '\n')
    ;
  hardware::calibrate();

  while (WAIT && Serial.read() != '\n')
    ;
  hardware::startingPosition();

  control::init();

  LOG_DEBUG("<Main> Ready");
}

void loop() {
  hardware::loop();
  control::loop();
}