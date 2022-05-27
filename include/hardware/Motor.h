#pragma once

#include <stdint.h>

namespace hardware {

/**
 * @brief Abstraction over a motor component controlled with an *H-Bridge*
 *        through 3 pins, namely `IN A`, `IN B` and `PWM`
 */
class Motor {
 public:
  /**
   * H-Bridge configuration for the motor
   */
  enum class HBridge {
    kLowZ,
    kClockwise,
    kAntiClockwise,
    kHighZ,
  };

  /**
   * @brief Creates and initializes a motor
   *
   * @warning `pin_pwm` **must** support PWM (`analogWrite`) on
   *          the target
   *
   * @param pin_in_a Pin `IN A`
   * @param pin_in_b Pin `IN B`
   * @param pin_pwm Pin `PWM`
   */
  Motor(uint8_t pin_in_a, uint8_t pin_in_b, uint8_t pin_pwm);

  /**
   * @brief Set the `speed` and H-bridge `state` of the motor
   *
   * @param speed PWM set point for the motor
   * @param state Configuration of the H-bridge
   */
  void Set(uint8_t speed, HBridge state);

  /**
   * @brief Set the normalized speed of the motor
   *
   * Set the speed of the motor based on `speed` normalized between -1
   * and 1, where a positive value represents `Clockwise` and a
   * negative value represents `Anti Clockwise`
   *
   * @param norm_speed Fixed-point number in s.15 format repsenting the motor
   *                   speed
   */
  void SetNormalized(int16_t norm_speed);

  /// Brake the motor with `PWM` set to `0` and the H-bridge to `High-Z`
  void Brake();

  /**
   * @brief Returns the set speed of motor
   *
   * @return uint8_t The set speed
   */
  uint8_t GetSpeed();

  /**
   * @brief Returns the set H-bridge configuration state
   *
   * @return HBridge The set H-bridge configuration state
   */
  HBridge GetState();

  /**
   * @brief Returns the signed normalized speed of the motor
   *
   * @return int16_t The set normalized speed in s.15 fixed-point number
   *
   * @related `SetNormalized`
   */
  int16_t GetNormalizedSpeed();

 private:
  uint8_t pin_in_a_;  // Pin ID of `IN A`
  uint8_t pin_in_b_;  // Pin ID of `IN B`
  uint8_t pin_pwm_;   // Pin ID of `PWM`

  uint8_t speed_;  // Set speed of the motor
  HBridge state_;  // Set rotation direction of the motor
};

}  // namespace hardware