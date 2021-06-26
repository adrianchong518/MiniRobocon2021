#include "control/automatic/automatic.h"

#include "control/routines/routines.h"
#include "hardware/interface.h"

bool control::automatic::isAutomaticEnabled;

void control::automatic::init() {}

void control::automatic::loop() { routines::loop(); }

void control::automatic::stop() {
  routines::runRoutine(routines::RoutineID::NONE);
}

void control::automatic::setIsAutomaticEnabled(const bool isAutomaticEnabled) {
  control::automatic::isAutomaticEnabled = isAutomaticEnabled;

  LOG_INFO("<Automatic>\t" +
           String(isAutomaticEnabled ? "Enabled" : "Disabled"));
}