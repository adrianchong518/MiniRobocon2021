#include "control/control.h"

#include "hardware/hardware.h"
#include "control/commands.h"
#include "control/manual/manual.h"
#include "control/routines/routines.h"

String control::input = "";

void control::init() {
  LOG_INFO("<Control>\tInit Start...");
  hardware::interface::lcd.setCursor(1, 3);
  hardware::interface::lcd.print("Control Init ");
  LOG_INFO("<Control>\tInit Done");
}

void control::loop() {
  if (Serial.available()) {
    char inChar = Serial.read();

    switch (inChar) {
      case '\n':
      case '\r':
        input.trim();
        if (commands::parseInput(input) == -1) {
          LOG_ERROR("Invalid Input: " + input);
        }
        input = "";
        break;

      case '\b':
        input.remove(input.length() - 1);
        break;

      case 'x':
        hardware::stopAll();
        routines::runRoutine(routines::RoutineID::NONE);

      default:
        input.concat(inChar);
        break;
    }
  }

  manual::loop();
  routines::loop();
}
