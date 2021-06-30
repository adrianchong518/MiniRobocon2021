#include "control/automatic/automatic.h"

#include "constants.h"
#include "control/routines/routines.h"
#include "hardware/hardware.h"

bool control::automatic::isAutomaticEnabled;

control::automatic::PositionControl control::automatic::positionControl;

void control::automatic::init() {
  setIsAutomaticEnabled(!digitalRead(PIN_CONTROLLER_SWITCH_3));
}

void control::automatic::loop() {
  routines::loop();
  positionControl.update(hardware::encoders::encoderXCount,
                         hardware::encoders::encoderYCount);
}

void control::automatic::stop() {
  routines::runRoutine(routines::RoutineID::NONE);
  positionControl.stop();
  setIsAutomaticEnabled(false);
}

void control::automatic::setIsAutomaticEnabled(const bool isAutomaticEnabled) {
  control::automatic::isAutomaticEnabled = isAutomaticEnabled;

  if (isAutomaticEnabled) {
    hardware::interface::lcd.setCursor(16, 3);
    hardware::interface::lcd.print("A-");
  } else {
    routines::runRoutine(routines::RoutineID::NONE);
    positionControl.stop();
  }

  LOG_INFO("<Automatic>\t" +
           String(isAutomaticEnabled ? "Enabled" : "Disabled"));
}