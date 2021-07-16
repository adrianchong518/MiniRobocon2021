#include "control/automatic/automatic.h"

#include "constants.h"
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