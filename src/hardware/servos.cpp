#include "hardware/servos.h"

#include "constants.h"
#include "hardware/interface.h"

Servo hardware::servos::puttingLeftUpper;
Servo hardware::servos::puttingLeftLower;
Servo hardware::servos::puttingRightUpper;
Servo hardware::servos::puttingRightLower;

void hardware::servos::init() {
  LOG_DEBUG("<Servos>\tInitialising...");

  puttingLeftUpper.attach(PIN_PUTTING_LEFT_UPPER);
  puttingLeftLower.attach(PIN_PUTTING_LEFT_LOWER);
  puttingRightUpper.attach(PIN_PUTTING_RIGHT_UPPER);
  puttingRightLower.attach(PIN_PUTTING_RIGHT_LOWER);
}

void hardware::servos::startingPosition() {
  LOG_INFO("<Servos>\tSetting default positions");

  puttingLeftUpper.write(PUTTING_LEFT_UPPER_STARTING_POS);
  puttingLeftLower.write(PUTTING_LEFT_LOWER_STARTING_POS);
  puttingRightUpper.write(PUTTING_RIGHT_UPPER_STARTING_POS);
  puttingRightLower.write(PUTTING_RIGHT_LOWER_STARTING_POS);
}
