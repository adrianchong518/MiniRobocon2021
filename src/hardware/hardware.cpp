#include "hardware/hardware.h"

#include "constants.h"
#include "utils/time.h"

hardware::MotorLimited hardware::wheelFL(PIN_WHEEL_FL_INA, PIN_WHEEL_FL_INB,
                                         PIN_WHEEL_FL_PWM,
                                         MECANUM_PWM_CHANGE_LIMIT_PER_MS,
                                         MECANUM_PWM_CHANGE_LIMIT_PER_LOOP,
                                         MECANUM_PWM_MIN_SPEED);
hardware::MotorLimited hardware::wheelFR(PIN_WHEEL_FR_INA, PIN_WHEEL_FR_INB,
                                         PIN_WHEEL_FR_PWM,
                                         MECANUM_PWM_CHANGE_LIMIT_PER_MS,
                                         MECANUM_PWM_CHANGE_LIMIT_PER_LOOP,
                                         MECANUM_PWM_MIN_SPEED);
hardware::MotorLimited hardware::wheelBL(PIN_WHEEL_BL_INA, PIN_WHEEL_BL_INB,
                                         PIN_WHEEL_BL_PWM,
                                         MECANUM_PWM_CHANGE_LIMIT_PER_MS,
                                         MECANUM_PWM_CHANGE_LIMIT_PER_LOOP,
                                         MECANUM_PWM_MIN_SPEED);
hardware::MotorLimited hardware::wheelBR(PIN_WHEEL_BR_INA, PIN_WHEEL_BR_INB,
                                         PIN_WHEEL_BR_PWM,
                                         MECANUM_PWM_CHANGE_LIMIT_PER_MS,
                                         MECANUM_PWM_CHANGE_LIMIT_PER_LOOP,
                                         MECANUM_PWM_MIN_SPEED);
hardware::Mecanum hardware::mecanum(&wheelFL, &wheelFR, &wheelBL, &wheelBR);

bool hardware::isHardwareLoopUpdating = true;

void hardware::init() {
  LOG_INFO("<Hardware>\tInit Start...");

  interface::init();
  interface::lcd.setCursor(1, 3);
  interface::lcd.print("    Init     ");

  sensors::init();
  encoders::init();
  servos::init();
  controller::init();

  LOG_INFO("<Hardware>\tInit Complete");
}

void hardware::calibrate() {
  LOG_INFO("<Hardware>\tCalibration Start...");
  interface::lcd.setCursor(1, 3);
  interface::lcd.print("  Calibrate  ");

  mecanum.findRotationOffset();

  LOG_INFO("<Hardware>\tCalibration Complete");
}

void hardware::startingPosition() {
  LOG_INFO("<Hardware>\tHoming Start...");
  interface::lcd.setCursor(1, 3);
  interface::lcd.print("    Home     ");

  servos::startingPosition();
  encoders::clearAll();

  LOG_INFO("<Hardware>\tHoming Complete");
}

void hardware::stopAll() {
  mecanum.stop();

  isHardwareLoopUpdating = false;
  LOG_INFO("<Hardware>\tStopped Loop");
}

void hardware::loop() {
  sensors::loop();
  controller::loop();

  if (isHardwareLoopUpdating) {
    mecanum.update();
    wheelFL.update();
    wheelFR.update();
    wheelBL.update();
    wheelBR.update();
  }
}
