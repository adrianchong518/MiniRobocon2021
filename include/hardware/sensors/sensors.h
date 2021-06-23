#pragma once

#include "hardware/sensors/TFMiniS.h"

namespace hardware {
namespace sensors {

extern TFMiniS distanceSensors[8];

extern unsigned long distanceSensorsPrevPollTime;

extern uint8_t collisionButtonsPrevState;
extern void (*collisionHandler)(uint8_t);

void init();
void loop();

}  // namespace sensors
}  // namespace hardware