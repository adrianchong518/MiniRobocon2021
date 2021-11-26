#pragma once

#include "hardware/Mecanum.h"
#include "hardware/Motor.h"
#include "hardware/MotorLimited.h"
#include "hardware/servos.h"
#include "hardware/controller.h"
#include "hardware/interface.h"

namespace hardware {

extern bool isI2CEnabled;

extern MotorLimited wheelFL;
extern MotorLimited wheelFR;
extern MotorLimited wheelBL;
extern MotorLimited wheelBR;
extern Mecanum mecanum;

extern bool isHardwareLoopUpdating;

void init();

void calibrate();

void startingPosition();

void stopAll();

void loop();

}  // namespace hardware
