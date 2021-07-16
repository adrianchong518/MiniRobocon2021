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

void setState(uint8_t state);
void setLeftState(uint8_t state);
void setRightState(uint8_t state);

}  // namespace servos
}  // namespace hardware
