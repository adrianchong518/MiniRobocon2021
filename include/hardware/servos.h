#ifndef HARDWARE_SERVOS_H
#define HARDWARE_SERVOS_H

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

#endif  // HARDWARE_SERVOS_H
