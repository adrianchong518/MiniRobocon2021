#pragma once

#include "hardware/sensors/TFMiniS.h"

namespace hardware {
namespace sensors {

extern TFMiniS distanceSensors[8];

extern unsigned long distanceSensorsPrevPollTime;

void init();
void loop();

}  // namespace sensors
}  // namespace hardware