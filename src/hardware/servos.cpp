#include "hardware/servos.h"

#include "constants.h"
#include "hardware/interface.h"
#include "control/control.h"

Servo hardware::servos::puttingServo;

void hardware::servos::init() {
  LOG_DEBUG("<Servos>\tInitialising...");

  puttingServo.attach(PIN_PUTTING_SERVO);

  hardware::interface::lcd.setCursor(19, 2);
  hardware::interface::lcd.print("0");
}

void hardware::servos::startingPosition() {
  LOG_INFO("<Servos>\tSetting default positions");

  puttingServo.write(PUTTING_STARTING_POS);
}

void hardware::servos::setState(uint8_t state) {
  hardware::interface::lcd.setCursor(19, 2);
  switch (state) {
    case 0:
      puttingServo.write(PUTTING_STARTING_POS);
      hardware::interface::lcd.print(0);
      LOG_DEBUG("<Servos>\tPutting Left\tStarting Position");
      break;

    case 1:
      puttingServo.write(PUTTING_HOLDING_POS);
      hardware::interface::lcd.print(1);
      LOG_DEBUG("<Servos>\tPutting Left\tHolding Position");
      break;

    case 2:
      puttingServo.write(PUTTING_PUTTING_POS);
      hardware::interface::lcd.print(2);
      LOG_DEBUG("<Servos>\tPutting Left\tPutting Position");
      break;

    default:
      break;
  }
}