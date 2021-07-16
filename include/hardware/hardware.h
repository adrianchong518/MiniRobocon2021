#pragma once

#include "hardware/Mecanum.h"
#include "hardware/Motor.h"
#include "hardware/MotorLimited.h"
#include "hardware/encoders.h"
#include "hardware/sensors/sensors.h"
#include "hardware/servos.h"
#include "hardware/controller.h"
#include "hardware/interface.h"
#include "hardware/BallHitter.h"

namespace hardware {

extern MotorLimited wheelFL;
extern MotorLimited wheelFR;
extern MotorLimited wheelBL;
extern MotorLimited wheelBR;
extern Mecanum mecanum;

extern Motor ballHitterMotor;
extern BallHitter ballHitter;

extern bool isHardwareLoopUpdating;

void init();

void calibrate();

void startingPosition();

void stopAll();

void loop();

}  // namespace hardware
