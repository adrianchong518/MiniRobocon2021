#include "control/automatic/automatic.h"

#include "constants.h"
#include "control/control.h"
#include "control/routines/routines.h"
#include "hardware/hardware.h"

bool control::automatic::isAutomaticEnabled;

control::automatic::PositionControl control::automatic::positionControl;

void control::automatic::init() {
#if NO_CONTROLLER != 1
  setIsAutomaticEnabled(!digitalRead(PIN_CONTROLLER_SWITCH_3));
#endif
}

void control::automatic::loop() {
  if (isAutomaticEnabled) {
    routines::loop();
    positionControl.update();
  }
}

void control::automatic::stop() { setIsAutomaticEnabled(false); }

void control::automatic::setIsAutomaticEnabled(const bool isAutomaticEnabled) {
  if (isAutomaticEnabled) {
    hardware::mecanum.setSpeed(0);

    switch (zone) {
      case Zone::RED:
        hardware::controller::buttonsHandlers[0][0] = [](uint8_t, bool) {
          routines::runSeq(0);
        };
        hardware::controller::buttonsHandlers[1][0] = [](uint8_t, bool) {
          routines::runSeq(1);
        };
        hardware::controller::buttonsHandlers[2][0] = [](uint8_t, bool) {
          routines::runSeq(2);
        };
        hardware::controller::buttonsHandlers[3][0] = [](uint8_t, bool) {
          routines::runSeq(3);
        };
        break;

      case Zone::BLUE:
        hardware::controller::buttonsHandlers[0][0] = [](uint8_t, bool) {
          routines::runSeq(4);
        };
        hardware::controller::buttonsHandlers[1][0] = [](uint8_t, bool) {
          routines::runSeq(5);
        };
        hardware::controller::buttonsHandlers[2][0] = [](uint8_t, bool) {
          routines::runSeq(6);
        };
        hardware::controller::buttonsHandlers[3][0] = [](uint8_t, bool) {
          routines::runSeq(7);
        };
        break;
    }

    hardware::controller::buttonsHandlers[0][1] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[1][1] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[2][1] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[3][1] =
        hardware::controller::defaultButtonsHandler;

    hardware::controller::buttonsHandlers[4][0] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[4][1] =
        hardware::controller::defaultButtonsHandler;

    hardware::controller::buttonsHandlers[5][0] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[5][1] =
        hardware::controller::defaultButtonsHandler;

    hardware::controller::buttonsHandlers[6][0] =
        hardware::controller::defaultButtonsHandler;
    hardware::controller::buttonsHandlers[6][1] =
        hardware::controller::defaultButtonsHandler;

    hardware::controller::buttonsHandlers[7][0] = [](uint8_t, bool) {
      hardware::ballHitter.hit(hardware::encoders::ballHitterEncoderCount);
    };
    hardware::controller::buttonsHandlers[7][1] =
        hardware::controller::defaultButtonsHandler;

    hardware::interface::lcd.setCursor(16, 3);
    hardware::interface::lcd.print("A-");
  } else {
    routines::runRoutine(routines::RoutineID::NONE);
    positionControl.stop();
  }

  control::automatic::isAutomaticEnabled = isAutomaticEnabled;

  LOG_INFO("<Automatic>\t" +
           String(isAutomaticEnabled ? "Enabled" : "Disabled"));
}