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

hardware::Motor hardware::ballHitterMotor(PIN_BALL_HITTER_INA,
                                          PIN_BALL_HITTER_INB,
                                          PIN_BALL_HITTER_PWM);
hardware::BallHitter hardware::ballHitter(
    &hardware::ballHitterMotor, true, BALL_HITTER_PID_KP, BALL_HITTER_PID_KI,
    BALL_HITTER_PID_KD, BALL_HITTER_PID_MAX_SPEED, BALL_HITTER_ENCODER_PPR);

bool hardware::isHardwareLoopUpdating = true;

void hardware::init() {
  LOG_INFO("<Hardware>\tInit Start...");

#if NO_CONTROLLER != 1
  interface::init();
  interface::lcd.setCursor(1, 3);
  interface::lcd.print("    Init     ");

  controller::init();
#endif

  sensors::init();
  encoders::init();
  servos::init();

  LOG_INFO("<Hardware>\tInit Complete");
}

void hardware::calibrate() {
  LOG_INFO("<Hardware>\tCalibration Start...");
#if NO_CONTROLLER != 1
  interface::lcd.setCursor(1, 3);
  interface::lcd.print("  Calibrate  ");
#endif

  mecanum.findRotationOffset();

  LOG_INFO("<Hardware>\tCalibration Complete");
}

void hardware::startingPosition() {
  LOG_INFO("<Hardware>\tHoming Start...");
#if NO_CONTROLLER != 1
  interface::lcd.setCursor(1, 3);
  interface::lcd.print("    Home     ");
#endif

  servos::startingPosition();
  encoders::clearAll();
  ballHitter.home();

  LOG_INFO("<Hardware>\tHoming Complete");
}

void hardware::stopAll() {
  mecanum.stop();
  // TODO ballHitter.stop();

  isHardwareLoopUpdating = false;
  LOG_INFO("<Hardware>\tStopped Loop");
}

void hardware::loop() {
  sensors::loop();
  encoders::loop();

#if NO_CONTROLLER != 1
  controller::loop();
#endif

  if (isHardwareLoopUpdating) {
    mecanum.update();
    wheelFL.update();
    wheelFR.update();
    wheelBL.update();
    wheelBR.update();

    ballHitter.loop(encoders::ballHitterEncoderCount);
  }
}
