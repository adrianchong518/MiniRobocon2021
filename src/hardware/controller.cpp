#include "hardware/controller.h"

#include <Arduino.h>

#include "constants.h"
#include "hardware/interface.h"

uint16_t hardware::controller::joystickXVal;
uint16_t hardware::controller::joystickYVal;

uint16_t hardware::controller::turnLeftVal;
uint16_t hardware::controller::turnRightVal;

uint8_t hardware::controller::buttonsPrevState = 0xFF;
void (*hardware::controller::buttonsCallback[8][2])(uint8_t);

void testPressedCallback(uint8_t buttonIndex) {
  LOG_INFO("<Controller>\tButton " + String(buttonIndex) + " Pressed");
}

void testReleaseCallback(uint8_t buttonIndex) {
  LOG_INFO("<Controller>\tButton " + String(buttonIndex) + " Released");
}

void hardware::controller::init() {
  LOG_DEBUG("<Controller>\tInitialising...");

  pinMode(PIN_CONTROLLER_JOYSTICK_X, INPUT);
  pinMode(PIN_CONTROLLER_JOYSTICK_Y, INPUT);

  pinMode(PIN_CONTROLLER_TURN_LEFT, INPUT);
  pinMode(PIN_CONTROLLER_TURN_RIGHT, INPUT);

  PORT_CONTROLLER_BUTTONS_DDR = 0x00;
  PORT_CONTROLLER_BUTTONS_PORT = 0xFF;

  memset(buttonsCallback, 0, sizeof(buttonsCallback));

  for (int i = 0; i < 8; i++) {
    buttonsCallback[i][0] = &testPressedCallback;
    buttonsCallback[i][1] = &testReleaseCallback;
  }
}

void hardware::controller::loop() {
  joystickXVal = analogRead(PIN_CONTROLLER_JOYSTICK_X);
  joystickYVal = analogRead(PIN_CONTROLLER_JOYSTICK_Y);

  turnLeftVal = analogRead(PIN_CONTROLLER_TURN_LEFT);
  turnRightVal = analogRead(PIN_CONTROLLER_TURN_RIGHT);

  uint8_t buttonsState = PORT_CONTROLLER_BUTTONS_PIN;
  if ((buttonsState ^ buttonsPrevState) != 0) {
    for (int i = 0; i < 8; i++) {
      if ((buttonsState >> i & 1) != (buttonsPrevState >> i & 1)) {
        if (buttonsCallback[i][buttonsState >> i & 1]) {
          (*buttonsCallback[i][buttonsState >> i & 1])(i);
        }
      }
    }

    buttonsPrevState = buttonsState;
  }
}