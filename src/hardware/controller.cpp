#include "hardware/controller.h"

#include <Arduino.h>

#include "constants.h"
#include "hardware/interface.h"

bool hardware::controller::isJoystickEnabled = true;

uint16_t hardware::controller::joystickXVal;
uint16_t hardware::controller::joystickYVal;

uint16_t hardware::controller::turnLeftVal;
uint16_t hardware::controller::turnRightVal;

uint8_t hardware::controller::buttonsPrevState = 0xFF;
void (*hardware::controller::buttonsHandlers[8][2])(uint8_t);

bool hardware::controller::switch0State;
bool hardware::controller::switch1State;
bool hardware::controller::switch2State;
bool hardware::controller::switch3State;

void hardware::controller::init() {
  LOG_DEBUG("<Controller>\tInitialising...");

  pinMode(PIN_CONTROLLER_JOYSTICK_X, INPUT);
  pinMode(PIN_CONTROLLER_JOYSTICK_Y, INPUT);

  pinMode(PIN_CONTROLLER_TURN_LEFT, INPUT);
  pinMode(PIN_CONTROLLER_TURN_RIGHT, INPUT);

  PORT_CONTROLLER_BUTTONS_DDR = 0x00;
  PORT_CONTROLLER_BUTTONS_PORT = 0xFF;

  memset(buttonsHandlers, 0, sizeof(buttonsHandlers));
  for (int i = 0; i < 8; i++) {
    buttonsHandlers[i][0] = [](uint8_t buttonIndex) {
      LOG_INFO("<Controller>\tButton " + String(buttonIndex) + " Pressed");
    };
    buttonsHandlers[i][1] = [](uint8_t buttonIndex) {
      LOG_INFO("<Controller>\tButton " + String(buttonIndex) + " Released");
    };
  }

  pinMode(PIN_CONTROLLER_SWITCH_0, INPUT_PULLUP);
  pinMode(PIN_CONTROLLER_SWITCH_1, INPUT_PULLUP);
  pinMode(PIN_CONTROLLER_SWITCH_2, INPUT_PULLUP);
  pinMode(PIN_CONTROLLER_SWITCH_3, INPUT_PULLUP);
}

void hardware::controller::loop() {
  if (isJoystickEnabled) {
    joystickXVal = analogRead(PIN_CONTROLLER_JOYSTICK_X);
    joystickYVal = analogRead(PIN_CONTROLLER_JOYSTICK_Y);

    turnLeftVal = analogRead(PIN_CONTROLLER_TURN_LEFT);
    turnRightVal = analogRead(PIN_CONTROLLER_TURN_RIGHT);

#if DEBUG == 1
    interface::lcd.setCursor(0, 0);
    if (joystickXVal < 1000) interface::lcd.print("0");
    if (joystickXVal < 100) interface::lcd.print("0");
    if (joystickXVal < 10) interface::lcd.print("0");
    interface::lcd.print(joystickXVal);

    interface::lcd.setCursor(5, 0);
    if (joystickYVal < 1000) interface::lcd.print("0");
    if (joystickYVal < 100) interface::lcd.print("0");
    if (joystickYVal < 10) interface::lcd.print("0");
    interface::lcd.print(joystickYVal);

    interface::lcd.setCursor(0, 1);
    if (turnLeftVal < 1000) interface::lcd.print("0");
    if (turnLeftVal < 100) interface::lcd.print("0");
    if (turnLeftVal < 10) interface::lcd.print("0");
    interface::lcd.print(turnLeftVal);

    interface::lcd.setCursor(5, 1);
    if (turnRightVal < 1000) interface::lcd.print("0");
    if (turnRightVal < 100) interface::lcd.print("0");
    if (turnRightVal < 10) interface::lcd.print("0");
    interface::lcd.print(turnRightVal);
#endif
  }

  uint8_t buttonsState = PORT_CONTROLLER_BUTTONS_PIN;
  if (buttonsState != buttonsPrevState) {
    for (int i = 0; i < 8; i++) {
      if ((buttonsState >> i & 1) != (buttonsPrevState >> i & 1)) {
        if (buttonsHandlers[i][buttonsState >> i & 1]) {
          (*buttonsHandlers[i][buttonsState >> i & 1])(i);
        }
      }
    }

    buttonsPrevState = buttonsState;
  }

  switch0State = digitalRead(PIN_CONTROLLER_SWITCH_0);
  switch1State = digitalRead(PIN_CONTROLLER_SWITCH_1);
  switch2State = digitalRead(PIN_CONTROLLER_SWITCH_2);
  switch3State = digitalRead(PIN_CONTROLLER_SWITCH_3);
}