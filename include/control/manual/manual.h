#pragma once

#include <stdint.h>

namespace control {
namespace manual {

extern bool isManualEnabled;

extern double joystickHeading;
extern double joystickMappedSpeed;

extern int16_t turnMappedRotationSpeedDiff;

void init();
void loop();

void setIsManualEnabled(const bool isManualEnabled);
void setButtonsHandlers();

}  // namespace manual
}  // namespace control