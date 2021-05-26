#pragma once

#include <stdint.h>

namespace hardware {
namespace controller {

extern uint16_t joystickXVal;
extern uint16_t joystickYVal;

extern uint16_t turnLeftVal;
extern uint16_t turnRightVal;

extern uint8_t buttonsPrevState;
extern void (*buttonsCallback[8][2])(uint8_t);

void init();
void loop();

}  // namespace controller
}  // namespace hardware