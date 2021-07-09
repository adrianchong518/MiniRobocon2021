#include <Arduino.h>
#include <Wire.h>

#include "constants.h"
#include "hardware/hardware.h"
#include "control/control.h"
#include "utils/time.h"

// #define IS_TIMING

void setup() {
  Serial.begin(115200);
  Wire.begin();

  hardware::init();

  while (digitalRead(PIN_CONTROLLER_SWITCH_0) && Serial.read() != '\n')
    ;
  hardware::calibrate();

  while (digitalRead(PIN_CONTROLLER_SWITCH_0) && Serial.read() != '\n')
    ;
  hardware::startingPosition();

  while (digitalRead(PIN_CONTROLLER_SWITCH_0) && Serial.read() != '\n')
    ;
  control::init();

  while (digitalRead(PIN_CONTROLLER_SWITCH_0) && Serial.read() != '\n')
    ;
  LOG_INFO("<Main>\t\tReady");
  hardware::interface::lcd.setCursor(1, 3);
  hardware::interface::lcd.print("  Main Loop  ");
}

#ifdef IS_TIMING
unsigned long start, end;
void loop() {
  start = micros();
  time::preLoop();
  hardware::loop();
  control::loop();
  time::postLoop();
  end = micros();
  LOG_INFO("<Main>\t\tTime Taken:\t" + String(end - start) + "\tus");
}
#else
void loop() {
  time::preLoop();
  hardware::loop();
  control::loop();
  time::postLoop();
}
#endif