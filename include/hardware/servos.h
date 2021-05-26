#pragma once

#include <Servo.h>

namespace hardware {
namespace servos {

extern Servo puttingLeftUpper;
extern Servo puttingLeftLower;
extern Servo puttingRightUpper;
extern Servo puttingRightLower;

void init();
void startingPosition();

}  // namespace servos
}  // namespace hardware
