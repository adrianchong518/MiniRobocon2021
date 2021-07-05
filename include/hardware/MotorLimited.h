#pragma once

#include <Arduino.h>

#include "Motor.h"

namespace hardware {

class MotorLimited : public Motor {
 private:
  const uint8_t m_pwmChangeLimitPerUs;

  double m_speedTarget = 0;
  unsigned long m_prevUpdateTime;

 public:
  MotorLimited(const uint8_t pin_inA, const uint8_t pin_inB,
               const uint8_t pin_PWM, const double pwmChangeLimit);

  void update();

  void setSpeed(const int16_t speed);
};

}  // namespace hardware
