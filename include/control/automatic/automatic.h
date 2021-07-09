#pragma once

#include "control/automatic/PositionControl.h"

namespace control {
namespace automatic {

extern bool isAutomaticEnabled;

extern PositionControl positionControl;

void init();
void loop();

void stop();

void setIsAutomaticEnabled(const bool isAutomaticEnabled);

}  // namespace automatic
}  // namespace control