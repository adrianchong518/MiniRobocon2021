#ifndef HARDWARE_HARDWARE_H
#define HARDWARE_HARDWARE_H

#include "hardware/Mecanum.h"
#include "hardware/Motor.h"
// #include "hardware/encoders.h"
// #include "hardware/sensors/sensors.h"
#include "hardware/servos.h"
#include "hardware/controller.h"
#include "hardware/interface.h"

namespace hardware {

extern Motor wheelFL;
extern Motor wheelFR;
extern Motor wheelBL;
extern Motor wheelBR;
extern Mecanum mecanum;

extern bool isHardwareLoopUpdating;

void init();

void calibrate();

void startingPosition();

void stopAll();

void loop();

}  // namespace hardware

#endif  // HARDWARE_HARDWARE_H
