#include "control/manual/manual.h"

#include <math.h>

#include "constants.h"
#include "utils/fast_trig.h"
#include "hardware/hardware.h"
#include "hardware/controller.h"

bool control::manual::isManualEnabled;

double control::manual::joystickHeading;
double control::manual::joystickMappedSpeed;

int16_t control::manual::turnMappedRotationSpeedDiff;

void mapJoystick() {
  double normalizedX;
  if (hardware::controller::joystickXVal >
      CONTROLLER_JOYSTICK_X_MID + CONTROLLER_DEADZONE) {
    normalizedX = -(double)((int32_t)hardware::controller::joystickXVal -
                            CONTROLLER_JOYSTICK_X_MID) /
                  (CONTROLLER_JOYSTICK_X_MAX - CONTROLLER_JOYSTICK_X_MID);
    normalizedX = constrain(normalizedX, -1, 1);
  } else if (hardware::controller::joystickXVal <
             CONTROLLER_JOYSTICK_X_MID - CONTROLLER_DEADZONE) {
    normalizedX = -(double)((int32_t)hardware::controller::joystickXVal -
                            CONTROLLER_JOYSTICK_X_MID) /
                  (CONTROLLER_JOYSTICK_X_MID - CONTROLLER_JOYSTICK_X_MIN);
    normalizedX = constrain(normalizedX, -1, 1);
  } else {
    normalizedX = 0;
  }

  double normalizedY;
  if (hardware::controller::joystickYVal >
      CONTROLLER_JOYSTICK_Y_MID + CONTROLLER_DEADZONE) {
    normalizedY = (double)((int32_t)hardware::controller::joystickYVal -
                           CONTROLLER_JOYSTICK_Y_MID) /
                  (CONTROLLER_JOYSTICK_Y_MAX - CONTROLLER_JOYSTICK_Y_MID);
    normalizedY = constrain(normalizedY, -1, 1);
  } else if (hardware::controller::joystickYVal <
             CONTROLLER_JOYSTICK_Y_MID - CONTROLLER_DEADZONE) {
    normalizedY = (double)((int32_t)hardware::controller::joystickYVal -
                           CONTROLLER_JOYSTICK_Y_MID) /
                  (CONTROLLER_JOYSTICK_Y_MID - CONTROLLER_JOYSTICK_Y_MIN);
    normalizedY = constrain(normalizedY, -1, 1);
  } else {
    normalizedY = 0;
  }

  control::manual::joystickHeading =
      (double)atan2_fast(normalizedX * FAST_TRIG_ATAN2_SCALING,
                         normalizedY * FAST_TRIG_ATAN2_SCALING) *
      FAST_TRIG_UINT_TO_RAD;
  control::manual::joystickMappedSpeed =
      fmax(fabs(normalizedX), fabs(normalizedY));
}

void mapTurn() {
  int16_t mappedTurnLeftVal;
  if (hardware::controller::turnLeftVal <
      CONTROLLER_TURN_LEFT_MAX - CONTROLLER_DEADZONE) {
    mappedTurnLeftVal = (CONTROLLER_TURN_LEFT_MAX -
                         (int32_t)hardware::controller::turnLeftVal) *
                        (-MECANUM_ROT_DIFF_MIN) /
                        (CONTROLLER_TURN_LEFT_MAX - CONTROLLER_TURN_LEFT_MIN);
    mappedTurnLeftVal = constrain(mappedTurnLeftVal, 0, MECANUM_ROT_DIFF_MAX);
  } else {
    mappedTurnLeftVal = 0;
  }

  int16_t mappedTurnRightVal;
  if (hardware::controller::turnRightVal <
      CONTROLLER_TURN_RIGHT_MAX - CONTROLLER_DEADZONE) {
    mappedTurnRightVal =
        -(CONTROLLER_TURN_RIGHT_MAX -
          (int32_t)hardware::controller::turnRightVal) *
        MECANUM_ROT_DIFF_MAX /
        (CONTROLLER_TURN_RIGHT_MAX - CONTROLLER_TURN_RIGHT_MIN);
    mappedTurnRightVal = constrain(mappedTurnRightVal, MECANUM_ROT_DIFF_MIN, 0);
  } else {
    mappedTurnRightVal = 0;
  }

  control::manual::turnMappedRotationSpeedDiff =
      mappedTurnLeftVal + mappedTurnRightVal;
}

void control::manual::init() {
  setIsManualEnabled(digitalRead(PIN_CONTROLLER_SWITCH_0));
}

void control::manual::loop() {
  if (isManualEnabled) {
    if (hardware::mecanum.isGyroEnabled() !=
        hardware::controller::switch2State) {
      hardware::mecanum.setIsGyroEnabled(hardware::controller::switch2State);

      if (hardware::mecanum.isGyroEnabled()) {
        hardware::interface::lcd.setCursor(10, 1);
        hardware::interface::lcd.print("    ");
      }
    }

    mapJoystick();
    hardware::mecanum.setSpeed(joystickMappedSpeed);
    hardware::mecanum.setDirection(joystickHeading);

    hardware::interface::lcd.setCursor(10, 0);
    hardware::interface::lcd.print(joystickMappedSpeed, 2);
    hardware::interface::lcd.setCursor(15, 0);
    size_t numChar =
        hardware::interface::lcd.print(round(degrees(joystickHeading)));
    for (size_t i = 0; i < 4 - numChar; i++)
      hardware::interface::lcd.print(" ");

    if (!hardware::mecanum.isGyroEnabled()) {
      mapTurn();
      hardware::mecanum.setRotationSpeedDiff(turnMappedRotationSpeedDiff);

      hardware::interface::lcd.setCursor(10, 1);
      size_t numChar =
          hardware::interface::lcd.print(turnMappedRotationSpeedDiff);
      for (size_t i = 0; i < 4 - numChar; i++)
        hardware::interface::lcd.print(" ");
    }
  }
}

void control::manual::setIsManualEnabled(const bool isManualEnabled) {
  control::manual::isManualEnabled = isManualEnabled;
  hardware::controller::isJoystickEnabled = isManualEnabled;

  if (isManualEnabled) {
    hardware::mecanum.setIsGyroEnabled(hardware::controller::switch2State);

    hardware::interface::lcd.setCursor(16, 3);
    hardware::interface::lcd.print("M");
  } else {
    hardware::interface::lcd.setCursor(0, 0);
    hardware::interface::lcd.print("                    ");
    hardware::interface::lcd.setCursor(0, 1);
    hardware::interface::lcd.print("                    ");
  }

  LOG_INFO("<Manual>\t" + String(isManualEnabled ? "Enabled" : "Disabled"));
}