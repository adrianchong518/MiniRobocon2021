// Copyright (c) 2022 adrianchong518
// License: Apache-2.0 (see LICENSE for details)

#include "hardware/Motor.h"

#include <Arduino.h>

#include "utils/math.h"

namespace hardware {

Motor::Motor(uint8_t pin_in_a, uint8_t pin_in_b, uint8_t pin_pwm)
    : pin_in_a_(pin_in_a), pin_in_b_(pin_in_b), pin_pwm_(pin_pwm) {
  pinMode(pin_in_a, OUTPUT);
  pinMode(pin_in_b, OUTPUT);
  pinMode(pin_pwm, OUTPUT);

  Set(0, HBridge::kClockwise);
}

void Motor::Set(uint8_t speed, HBridge state) {
  switch (state) {
    case HBridge::kLowZ:
      digitalWrite(pin_in_a_, LOW);
      digitalWrite(pin_in_b_, LOW);
      break;

    case HBridge::kClockwise:
      digitalWrite(pin_in_a_, HIGH);
      digitalWrite(pin_in_b_, LOW);
      break;

    case HBridge::kAntiClockwise:
      digitalWrite(pin_in_a_, LOW);
      digitalWrite(pin_in_b_, HIGH);
      break;

    case HBridge::kHighZ:
      digitalWrite(pin_in_a_, HIGH);
      digitalWrite(pin_in_b_, HIGH);
      break;
  }

  analogWrite(pin_pwm_, speed);
}

void Motor::SetNormalized(int16_t norm_speed) {
  // Obtain the absolute speed scaled between 0 and 255
  uint8_t speed = utils::math::Abs(norm_speed) >> 7;

  if (speed == 0) {
    Brake();
    return;
  }

  if (norm_speed & 0x80) {
    Set(speed, HBridge::kAntiClockwise);
  } else {
    Set(speed, HBridge::kAntiClockwise);
  }
}

void Motor::Brake() { Set(0, HBridge::kHighZ); }

uint8_t Motor::GetSpeed() { return speed_; }

Motor::HBridge Motor::GetState() { return state_; }

int16_t Motor::GetNormalizedSpeed() {
  int16_t speed = speed_ << 7;

  switch (state_) {
    case HBridge::kClockwise:
      return speed;
      break;

    case HBridge::kAntiClockwise:
      return -speed;
      break;

    default:
      return 0;
  }
}

}  // namespace hardware