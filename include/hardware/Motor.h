#pragma once

#include <Arduino.h>

namespace hardware {

class Motor {
 private:
  const uint8_t m_pin_inA;
  const uint8_t m_pin_inB;
  const uint8_t m_pin_PWM;

 protected:
  int16_t m_speed = 0;

 public:
  Motor(const uint8_t pin_inA, const uint8_t pin_inB, const uint8_t pin_PWM);

  void setSpeed(const int16_t speed);
  int16_t getSpeed() const;
};

}  // namespace hardware
