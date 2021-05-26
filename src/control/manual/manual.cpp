#include "control/manual/manual.h"

#include <math.h>

#include "constants.h"
#include "hardware/hardware.h"
#include "hardware/controller.h"

bool control::manual::isManualEnabled = true;

double control::manual::joystickHeading;
double control::manual::joystickMappedSpeed;

int16_t control::manual::turnMappedRotationSpeedDiff;

void mapJoystick() {
  double normalizedX;
  if (hardware::controller::joystickXVal >
      CONTROLLER_JOYSTICK_X_MID + CONTROLLER_DEADZONE) {
    normalizedX = ((double)hardware::controller::joystickXVal -
                   CONTROLLER_JOYSTICK_X_MID) /
                  (CONTROLLER_JOYSTICK_X_MAX - CONTROLLER_JOYSTICK_X_MID);
  } else if (hardware::controller::joystickXVal <
             CONTROLLER_JOYSTICK_X_MID - CONTROLLER_DEADZONE) {
    normalizedX = ((double)hardware::controller::joystickXVal -
                   CONTROLLER_JOYSTICK_X_MID) /
                  (CONTROLLER_JOYSTICK_X_MID - CONTROLLER_JOYSTICK_X_MIN);
  } else {
    normalizedX = 0;
  }
  normalizedX = constrain(-normalizedX, -1, 1);

  double normalizedY;
  if (hardware::controller::joystickYVal >
      CONTROLLER_JOYSTICK_Y_MID + CONTROLLER_DEADZONE) {
    normalizedY = ((double)hardware::controller::joystickYVal -
                   CONTROLLER_JOYSTICK_Y_MID) /
                  (CONTROLLER_JOYSTICK_Y_MAX - CONTROLLER_JOYSTICK_Y_MID);
  } else if (hardware::controller::joystickYVal <
             CONTROLLER_JOYSTICK_Y_MID - CONTROLLER_DEADZONE) {
    normalizedY = ((double)hardware::controller::joystickYVal -
                   CONTROLLER_JOYSTICK_Y_MID) /
                  (CONTROLLER_JOYSTICK_Y_MID - CONTROLLER_JOYSTICK_Y_MIN);
  } else {
    normalizedY = 0;
  }
  normalizedY = constrain(normalizedY, -1, 1);

  control::manual::joystickHeading = atan2(normalizedX, normalizedY);
  control::manual::joystickMappedSpeed =
      fmax(fabs(normalizedX), fabs(normalizedY));
}

void mapTurn() {
  int16_t mappedTurnLeftVal;
  if (hardware::controller::turnLeftVal <
      CONTROLLER_TURN_LEFT_MAX - CONTROLLER_DEADZONE) {
    mappedTurnLeftVal = -(CONTROLLER_TURN_LEFT_MAX -
                          (double)hardware::controller::turnLeftVal) *
                        (-MECANUM_ROT_DIFF_MIN) /
                        (CONTROLLER_TURN_LEFT_MAX - CONTROLLER_TURN_LEFT_MIN);
  } else {
    mappedTurnLeftVal = 0;
  }
  mappedTurnLeftVal = constrain(mappedTurnLeftVal, MECANUM_ROT_DIFF_MIN, 0);

  int16_t mappedTurnRightVal;
  if (hardware::controller::turnRightVal <
      CONTROLLER_TURN_RIGHT_MAX - CONTROLLER_DEADZONE) {
    mappedTurnRightVal =
        (CONTROLLER_TURN_RIGHT_MAX -
         (double)hardware::controller::turnRightVal) *
        MECANUM_ROT_DIFF_MAX /
        (CONTROLLER_TURN_RIGHT_MAX - CONTROLLER_TURN_RIGHT_MIN);
  } else {
    mappedTurnRightVal = 0;
  }
  mappedTurnRightVal = constrain(mappedTurnRightVal, 0, MECANUM_ROT_DIFF_MAX);

  control::manual::turnMappedRotationSpeedDiff =
      mappedTurnLeftVal + mappedTurnRightVal;
}

void control::manual::loop() {
  mapJoystick();
  mapTurn();

  if (isManualEnabled) {
    hardware::mecanum.setSpeed(joystickMappedSpeed);
    hardware::mecanum.setDirection(joystickHeading);
    hardware::mecanum.setRotationSpeedDiff(turnMappedRotationSpeedDiff);
  }
}

void control::manual::setIsManualEnabled(const bool isManualEnabled) {
  control::manual::isManualEnabled = isManualEnabled;

  if (!isManualEnabled) {
    hardware::mecanum.setIsGyroEnabled(false);
  }

  LOG_INFO("<Manual> " + String(isManualEnabled ? "Enabled" : "Disabled"));
}