#pragma once

#include <Arduino.h>

namespace hardware {

class MotorLimited {
 private:
  const uint8_t m_pin_inA;
  const uint8_t m_pin_inB;
  const uint8_t m_pin_PWM;
  const uint8_t m_pwmChangeLimitPerMs;
  const uint8_t m_pwmChangeLimitPerLoop;
  const uint8_t m_pwmMinSpeed;

  int16_t m_speed = 0;
  int16_t m_speedTarget = 0;

 public:
  MotorLimited(const uint8_t pin_inA, const uint8_t pin_inB,
               const uint8_t pin_PWM, const uint8_t pwmChangeLimitPerMs,
               const uint8_t pwmChangeLimitPerLoop, const uint8_t pwmMinSpeed);

  void update();

  void setSpeedTarget(const int16_t speedTarget);
  int16_t getSpeedTarget() const;

  void setSpeed(const int16_t speed);
  int16_t getSpeed() const;

  void brakeToGnd();
  void brakeToVcc();
};

}  // namespace hardware
