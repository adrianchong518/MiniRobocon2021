#pragma once

#include <Arduino.h>

namespace control {

extern String input;

enum class Zone { RED, BLUE };
extern Zone zone;

void init();

void loop();

}  // namespace control
