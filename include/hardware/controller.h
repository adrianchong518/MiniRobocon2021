#pragma once

#include <stdint.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

namespace hardware {
namespace controller {

extern uint16_t joystickXVal;
extern uint16_t joystickYVal;

extern uint16_t turnLeftVal;
extern uint16_t turnRightVal;

extern uint8_t buttonsPrevState;
extern void (*buttonsCallback[8][2])(uint8_t);

extern bool switch0State;
extern bool switch1State;
extern bool switch2State;
extern bool switch3State;

extern hd44780_I2Cexp lcd;

void init();
void loop();

}  // namespace controller
}  // namespace hardware