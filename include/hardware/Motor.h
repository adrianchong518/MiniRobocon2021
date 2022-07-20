// Copyright (c) 2022 adrianchong518
// License: Apache-2.0 (see LICENSE for details)

#pragma once

#include <stdint.h>

namespace hardware {

// Abstraction over a motor component controlled with an H-bridge through 3
// pins, namely `IN A`, `IN B` and `PWM`
class Motor {
 public:
  // H-Bridge configurations for the motor
  enum class HBridge {
    kLowZ,
    kClockwise,
    kAntiClockwise,
    kHighZ,
  };

  // Constructs a `Motor` object and initializes the pins `pin_in_a`,
  // `pin_in_b`, and `pin_pwm`. Note that `pin_pwm` must support pwm output on
  // the target platform.
  Motor(uint8_t pin_in_a, uint8_t pin_in_b, uint8_t pin_pwm);

  // Writes `speed` as a PWM duty cycle to `pin_pwm_` and sets the H-bridge to
  // the specified `state`.
  void Set(uint8_t speed, HBridge state);

  // Sets the speed and direction of the motor to `norm_speed`
  //
  // `norm_speed` is a fixed-point number in `s.15` format (-1 ~ 1) representing
  // the normalized motor speed. A positive value represents `kClockwise`, while
  // a negative value represents `kAntiClockwise`
  void SetNormalized(int16_t norm_speed);

  /// Brake the motor with the PWM duty cycle set to `0` and the H-bridge
  /// configuration to `High-Z`
  void Brake();

  // Returns the set `speed_` of the motor
  uint8_t GetSpeed();

  // Returns the set H-bridge configuration `state_`
  HBridge GetState();

  // Returns the normalized speed of the motor in s.15 fixed-point format
  //
  // See documentation for `Motor::SetNormalizedSpeed()` for more detail on the
  // normalized speed number format.
  int16_t GetNormalizedSpeed();

 private:
  // Pin ID of `IN A`
  uint8_t pin_in_a_;
  // Pin ID of `IN B`
  uint8_t pin_in_b_;
  // Pin ID of `PWM`
  uint8_t pin_pwm_;

  // Set speed of the motor
  uint8_t speed_;
  // Set rotation direction of the motor
  HBridge state_;
};

}  // namespace hardware