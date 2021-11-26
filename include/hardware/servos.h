#pragma once

#include <Servo.h>

namespace hardware {
namespace servos {

extern Servo puttingServo;

void init();
void startingPosition();

void setState(uint8_t state);

}  // namespace servos
}  // namespace hardware
