#include "hardware/hardware.h"

#include "constants.h"

hardware::Motor hardware::wheelFL(PIN_WHEEL_FL_INA, PIN_WHEEL_FL_INB,
                                  PIN_WHEEL_FL_PWM);
hardware::Motor hardware::wheelFR(PIN_WHEEL_FR_INA, PIN_WHEEL_FR_INB,
                                  PIN_WHEEL_FR_PWM);
hardware::Motor hardware::wheelBL(PIN_WHEEL_BL_INA, PIN_WHEEL_BL_INB,
                                  PIN_WHEEL_BL_PWM);
hardware::Motor hardware::wheelBR(PIN_WHEEL_BR_INA, PIN_WHEEL_BR_INB,
                                  PIN_WHEEL_BR_PWM);
hardware::Mecanum hardware::mecanum(&wheelFL, &wheelFR, &wheelBL, &wheelBR);

bool hardware::isHardwareLoopUpdating = true;

void hardware::init() {
  LOG_INFO("<Hardware>\tInit Start...");

  // interface::init();
  sensors::init();
  // encoders::init();
  servos::init();
  controller::init();

  LOG_INFO("<Hardware>\tInit Complete");
}

void hardware::calibrate() {
  LOG_INFO("<Hardware>\tCalibration Start...");

  // mecanum.findRotationOffset();

  LOG_INFO("<Hardware>\tCalibration Complete");
}

void hardware::startingPosition() {
  LOG_INFO("<Hardware>\tHoming Start...");

  servos::startingPosition();
  // encoders::startingPosition();

  LOG_INFO("<Hardware>\tHoming Complete");
}

void hardware::stopAll() {
  mecanum.stop();

  isHardwareLoopUpdating = false;
  LOG_INFO("<Hardware>\tStopped Loop");
}

void hardware::loop() {
  if (isHardwareLoopUpdating) {
    // encoders::loop();
    sensors::loop();
    mecanum.update();
    controller::loop();
  }
}
