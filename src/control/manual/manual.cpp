#include "control/manual/manual.h"

#include <math.h>

#include "constants.h"
#include "utils/fast_trig.h"
#include "control/control.h"
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
                            CONTROLLER_JOYSTICK_X_MID - CONTROLLER_DEADZONE) /
                  (CONTROLLER_JOYSTICK_X_MAX - CONTROLLER_JOYSTICK_X_MID -
                   CONTROLLER_DEADZONE);
    normalizedX = constrain(normalizedX, -1, 1);
  } else if (hardware::controller::joystickXVal <
             CONTROLLER_JOYSTICK_X_MID - CONTROLLER_DEADZONE) {
    normalizedX = -(double)((int32_t)hardware::controller::joystickXVal -
                            CONTROLLER_JOYSTICK_X_MID + CONTROLLER_DEADZONE) /
                  (CONTROLLER_JOYSTICK_X_MID - CONTROLLER_JOYSTICK_X_MIN -
                   CONTROLLER_DEADZONE);
    normalizedX = constrain(normalizedX, -1, 1);
  } else {
    normalizedX = 0;
  }

  double normalizedY;
  if (hardware::controller::joystickYVal >
      CONTROLLER_JOYSTICK_Y_MID + CONTROLLER_DEADZONE) {
    normalizedY = (double)((int32_t)hardware::controller::joystickYVal -
                           CONTROLLER_JOYSTICK_Y_MID - CONTROLLER_DEADZONE) /
                  (CONTROLLER_JOYSTICK_Y_MAX - CONTROLLER_JOYSTICK_Y_MID -
                   CONTROLLER_DEADZONE);
    normalizedY = constrain(normalizedY, -1, 1);
  } else if (hardware::controller::joystickYVal <
             CONTROLLER_JOYSTICK_Y_MID - CONTROLLER_DEADZONE) {
    normalizedY = (double)((int32_t)hardware::controller::joystickYVal -
                           CONTROLLER_JOYSTICK_Y_MID + CONTROLLER_DEADZONE) /
                  (CONTROLLER_JOYSTICK_Y_MID - CONTROLLER_JOYSTICK_Y_MIN -
                   CONTROLLER_DEADZONE);
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

  Serial.println(String(normalizedX) + " " + String(normalizedY) + " " +
                 String(control::manual::joystickHeading) + " " +
                 String(control::manual::joystickMappedSpeed));
}

void mapTurn() {
  int16_t mappedTurnLeftVal;
  if (hardware::controller::turnLeftVal <
      CONTROLLER_TURN_LEFT_MAX - CONTROLLER_DEADZONE) {
    mappedTurnLeftVal = -(CONTROLLER_TURN_LEFT_MAX - CONTROLLER_DEADZONE -
                          (int32_t)hardware::controller::turnLeftVal) *
                        (-MECANUM_ROT_DIFF_MIN) /
                        (CONTROLLER_TURN_LEFT_MAX - CONTROLLER_TURN_LEFT_MIN -
                         CONTROLLER_DEADZONE);
    mappedTurnLeftVal = constrain(mappedTurnLeftVal, MECANUM_ROT_DIFF_MIN, 0);
  } else {
    mappedTurnLeftVal = 0;
  }

  int16_t mappedTurnRightVal;
  if (hardware::controller::turnRightVal <
      CONTROLLER_TURN_RIGHT_MAX - CONTROLLER_DEADZONE) {
    mappedTurnRightVal = (CONTROLLER_TURN_RIGHT_MAX - CONTROLLER_DEADZONE -
                          (int32_t)hardware::controller::turnRightVal) *
                         MECANUM_ROT_DIFF_MAX /
                         (CONTROLLER_TURN_RIGHT_MAX -
                          CONTROLLER_TURN_RIGHT_MIN - CONTROLLER_DEADZONE);
    mappedTurnRightVal = constrain(mappedTurnRightVal, 0, MECANUM_ROT_DIFF_MAX);
  } else {
    mappedTurnRightVal = 0;
  }

  control::manual::turnMappedRotationSpeedDiff =
      mappedTurnLeftVal + mappedTurnRightVal;
}

void control::manual::init() {
  setIsManualEnabled(digitalRead(PIN_CONTROLLER_SWITCH_3));
}

void control::manual::loop() {
  if (isManualEnabled) {
    if (hardware::mecanum.isGyroEnabled() !=
        hardware::controller::switch2State) {
      hardware::mecanum.setIsGyroEnabled(hardware::controller::switch2State);

#if LCD_DEBUG_ENABLED == 1
      if (hardware::mecanum.isGyroEnabled()) {
        hardware::interface::lcd.setCursor(10, 1);
        hardware::interface::lcd.print("    ");
      }
#endif
    }

    mapJoystick();
    hardware::mecanum.setSpeed(joystickMappedSpeed);
    hardware::mecanum.setDirection(joystickHeading);

#if LCD_DEBUG_ENABLED == 1
    hardware::interface::lcd.setCursor(10, 0);
    hardware::interface::lcd.print(joystickMappedSpeed, 2);
    hardware::interface::lcd.setCursor(15, 0);
    size_t numChar =
        hardware::interface::lcd.print(round(degrees(joystickHeading)));
    for (size_t i = 0; i < 4 - numChar; i++)
      hardware::interface::lcd.print(" ");

    hardware::interface::lcd.setCursor(15, 1);
    numChar =
        hardware::interface::lcd.print(round(hardware::mecanum.getRotation()));
    for (size_t i = 0; i < 4 - numChar; i++)
      hardware::interface::lcd.print(" ");
#endif

    if (!hardware::mecanum.isGyroEnabled()) {
      mapTurn();
      hardware::mecanum.setRotationSpeedDiff(turnMappedRotationSpeedDiff);

#if LCD_DEBUG_ENABLED == 1
      hardware::interface::lcd.setCursor(10, 1);
      size_t numChar =
          hardware::interface::lcd.print(turnMappedRotationSpeedDiff);
      for (size_t i = 0; i < 4 - numChar; i++)
        hardware::interface::lcd.print(" ");
#endif
    }
  }
}

void control::manual::setIsManualEnabled(const bool isManualEnabled) {
  control::manual::isManualEnabled = isManualEnabled;
  hardware::controller::isJoystickEnabled = isManualEnabled;

  if (isManualEnabled) {
    hardware::mecanum.setIsEnabled(true);
    hardware::mecanum.setIsGyroEnabled(hardware::controller::switch2State);

    hardware::controller::buttonsHandlers[0][0] = [](uint8_t, bool) {
      hardware::servos::setState(0);
    };

    hardware::controller::buttonsHandlers[1][0] = [](uint8_t, bool) {
      hardware::servos::setState(1);
    };

    hardware::controller::buttonsHandlers[2][0] = [](uint8_t, bool) {
      hardware::servos::setState(2);
    };

    hardware::controller::buttonsHandlers[2][1] = [](uint8_t, bool) {
      hardware::servos::setState(1);
    };

    hardware::controller::buttonsHandlers[5][0] = [](uint8_t, bool) {
      hardware::ballHitter.setTargetDeg(BALL_HITTER_NORMAL_DEG);
    };

    hardware::controller::buttonsHandlers[6][0] = [](uint8_t, bool) {
      hardware::ballHitter.hitStartPos(
          BALL_HITTER_HOLD_DEG, BALL_HITTER_START_DEG, BALL_HITTER_MID_DEG,
          BALL_HITTER_END_DEG, BALL_HITTER_HOLD_TO_START_SPEED,
          BALL_HITTER_SPEED, BALL_HITTER_MID_SPEED);
    };

    hardware::controller::buttonsHandlers[7][0] = [](uint8_t, bool) {
      hardware::ballHitter.hit(hardware::encoders::ballHitterEncoderCount);
    };

    hardware::interface::lcd.setCursor(16, 3);
    hardware::interface::lcd.print("M");
  } else {
    hardware::controller::buttonsHandlers[0][0] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[1][0] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[2][0] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[5][0] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[6][0] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[7][0] =
        hardware::controller::defaultButtonsHandler;

#if LCD_DEBUG_ENABLED == 1
    hardware::interface::lcd.setCursor(0, 0);
    hardware::interface::lcd.print("                    ");
    hardware::interface::lcd.setCursor(0, 1);
    hardware::interface::lcd.print("                    ");
#endif
  }

  LOG_INFO("<Manual>\t" + String(isManualEnabled ? "Enabled" : "Disabled"));
}