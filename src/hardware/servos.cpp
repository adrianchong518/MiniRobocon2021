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

void hardware::servos::setLeftState(uint8_t state) {
  switch (state) {
    case 0:
      hardware::servos::puttingLeftUpper.write(PUTTING_LEFT_UPPER_STARTING_POS);
      hardware::servos::puttingLeftLower.write(PUTTING_LEFT_LOWER_STARTING_POS);
      LOG_DEBUG("<Servos>\tPutting Left\tStarting Position");
      break;

    case 1:
      hardware::servos::puttingLeftUpper.write(PUTTING_LEFT_UPPER_HOLDING_POS);
      hardware::servos::puttingLeftLower.write(PUTTING_LEFT_LOWER_HOLDING_POS);
      LOG_DEBUG("<Servos>\tPutting Left\tHolding Position");
      break;

    case 2:
      hardware::servos::puttingLeftUpper.write(PUTTING_LEFT_UPPER_PUTTING_POS);
      hardware::servos::puttingLeftLower.write(PUTTING_LEFT_LOWER_PUTTING_POS);
      LOG_DEBUG("<Servos>\tPutting Left\tPutting Position");
      break;

    default:
      break;
  }
}

void hardware::servos::setRightState(uint8_t state) {
  switch (state) {
    case 0:
      hardware::servos::puttingRightUpper.write(
          PUTTING_RIGHT_UPPER_STARTING_POS);
      hardware::servos::puttingRightLower.write(
          PUTTING_RIGHT_LOWER_STARTING_POS);
      LOG_DEBUG("<Servos>\tPutting Right\tStarting Position");
      break;

    case 1:
      hardware::servos::puttingRightUpper.write(
          PUTTING_RIGHT_UPPER_HOLDING_POS);
      hardware::servos::puttingRightLower.write(
          PUTTING_RIGHT_LOWER_HOLDING_POS);
      LOG_DEBUG("<Servos>\tPutting Right\tHolding Position");
      break;

    case 2:
      hardware::servos::puttingRightUpper.write(
          PUTTING_RIGHT_UPPER_PUTTING_POS);
      hardware::servos::puttingRightLower.write(
          PUTTING_RIGHT_LOWER_PUTTING_POS);
      LOG_DEBUG("<Servos>\tPutting Right\tPutting Position");
      break;

    default:
      break;
  }
}