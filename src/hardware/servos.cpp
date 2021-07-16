#include "hardware/servos.h"

#include "constants.h"
#include "hardware/interface.h"
#include "control/control.h"

Servo hardware::servos::puttingLeftUpper;
Servo hardware::servos::puttingLeftLower;
Servo hardware::servos::puttingRightUpper;
Servo hardware::servos::puttingRightLower;

void hardware::servos::init() {
  LOG_DEBUG("<Servos>\tInitialising...");

  puttingLeftUpper.attach(PIN_PUTTING_LEFT_UPPER);
  puttingLeftUpper.write(PUTTING_LEFT_UPPER_STARTING_POS);

  puttingLeftLower.attach(PIN_PUTTING_LEFT_LOWER);
  puttingLeftLower.write(PUTTING_LEFT_LOWER_STARTING_POS);

  puttingRightUpper.attach(PIN_PUTTING_RIGHT_UPPER);
  puttingRightUpper.write(PUTTING_RIGHT_UPPER_STARTING_POS);

  puttingRightLower.attach(PIN_PUTTING_RIGHT_LOWER);
  puttingRightLower.write(PUTTING_RIGHT_LOWER_STARTING_POS);

  hardware::interface::lcd.setCursor(17, 2);
  hardware::interface::lcd.print("0 0");
}

void hardware::servos::startingPosition() {
  LOG_INFO("<Servos>\tSetting default positions");

  puttingLeftUpper.write(PUTTING_LEFT_UPPER_STARTING_POS);
  puttingLeftLower.write(PUTTING_LEFT_LOWER_STARTING_POS);
  puttingRightUpper.write(PUTTING_RIGHT_UPPER_STARTING_POS);
  puttingRightLower.write(PUTTING_RIGHT_LOWER_STARTING_POS);
}

void hardware::servos::setState(uint8_t state) {
  switch (control::zone) {
    case control::Zone::RED:
      setLeftState(state);
      break;

    case control::Zone::BLUE:
      setRightState(state);
      break;
  }
}

void hardware::servos::setLeftState(uint8_t state) {
  hardware::interface::lcd.setCursor(17, 2);
  switch (state) {
    case 0:
      hardware::servos::puttingLeftUpper.write(PUTTING_LEFT_UPPER_STARTING_POS);
      hardware::servos::puttingLeftLower.write(PUTTING_LEFT_LOWER_STARTING_POS);
      hardware::interface::lcd.print(0);
      LOG_DEBUG("<Servos>\tPutting Left\tStarting Position");
      break;

    case 1:
      hardware::servos::puttingLeftUpper.write(PUTTING_LEFT_UPPER_HOLDING_POS);
      hardware::servos::puttingLeftLower.write(PUTTING_LEFT_LOWER_HOLDING_POS);
      hardware::interface::lcd.print(1);
      LOG_DEBUG("<Servos>\tPutting Left\tHolding Position");
      break;

    case 2:
      hardware::servos::puttingLeftUpper.write(PUTTING_LEFT_UPPER_PUTTING_POS);
      hardware::servos::puttingLeftLower.write(PUTTING_LEFT_LOWER_PUTTING_POS);
      hardware::interface::lcd.print(2);
      LOG_DEBUG("<Servos>\tPutting Left\tPutting Position");
      break;

    default:
      break;
  }
}

void hardware::servos::setRightState(uint8_t state) {
  hardware::interface::lcd.setCursor(19, 2);
  switch (state) {
    case 0:
      hardware::servos::puttingRightUpper.write(
          PUTTING_RIGHT_UPPER_STARTING_POS);
      hardware::servos::puttingRightLower.write(
          PUTTING_RIGHT_LOWER_STARTING_POS);
      hardware::interface::lcd.print(0);
      LOG_DEBUG("<Servos>\tPutting Right\tStarting Position");
      break;

    case 1:
      hardware::servos::puttingRightUpper.write(
          PUTTING_RIGHT_UPPER_HOLDING_POS);
      hardware::servos::puttingRightLower.write(
          PUTTING_RIGHT_LOWER_HOLDING_POS);
      hardware::interface::lcd.print(1);
      LOG_DEBUG("<Servos>\tPutting Right\tHolding Position");
      break;

    case 2:
      hardware::servos::puttingRightUpper.write(
          PUTTING_RIGHT_UPPER_PUTTING_POS);
      hardware::servos::puttingRightLower.write(
          PUTTING_RIGHT_LOWER_PUTTING_POS);
      hardware::interface::lcd.print(2);
      LOG_DEBUG("<Servos>\tPutting Right\tPutting Position");
      break;

    default:
      break;
  }
}