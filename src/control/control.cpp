#include "control/control.h"

#include "hardware/hardware.h"
#include "control/commands.h"
#include "control/manual/manual.h"
#include "control/routines/routines.h"

String control::input = "";

void control::init() {}

void control::loop() {
  while (Serial.available()) {
    char inChar = Serial.read();

    if (inChar == '\n' || inChar == '\r') {
      input.trim();
      if (commands::parseInput(input) == -1) {
        LOG_ERROR("Invalid Input: " + input);
      }
      input = "";
    } else if (inChar == '\b') {
      input.remove(input.length() - 1);
    } else if (inChar == 'x') {
      hardware::stopAll();
      routines::runRoutine(routines::RoutineID::NONE);
    } else {
      input.concat(inChar);
    }
  }

  manual::loop();
  routines::loop();
}
