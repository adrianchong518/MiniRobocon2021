#pragma once

#include <stdint.h>

namespace hardware {
namespace controller {

extern bool isJoystickEnabled;

extern uint16_t joystickXVal;
extern uint16_t joystickYVal;

extern uint16_t turnLeftVal;
extern uint16_t turnRightVal;

extern uint8_t buttonsPrevState;
extern void (*buttonsHandlers[8][2])(uint8_t);

extern bool switch0State;
extern bool switch1State;
extern bool switch2State;
extern bool switch3State;

void init();
void loop();

}  // namespace controller
}  // namespace hardware