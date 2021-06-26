#include "control/control.h"

#include "hardware/hardware.h"
#include "control/commands.h"
#include "control/automatic/automatic.h"
#include "control/manual/manual.h"

String control::input = "";

void control::init() {
  LOG_INFO("<Control>\tInit Start...");
  hardware::interface::lcd.setCursor(1, 3);
  hardware::interface::lcd.print("Control Init ");

  manual::init();
  automatic::init();
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
        automatic::stop();

      default:
        input.concat(inChar);
        break;
    }
  }

  if (manual::isManualEnabled != hardware::controller::switch0State) {
    manual::setIsManualEnabled(hardware::controller::switch0State);
  }

  if (automatic::isAutomaticEnabled != !hardware::controller::switch0State) {
    automatic::setIsAutomaticEnabled(!hardware::controller::switch0State);
  }

  manual::loop();
  automatic::loop();
}
