#include "hardware/MotorLimited.h"

hardware::MotorLimited::MotorLimited(const uint8_t pin_inA,
                                     const uint8_t pin_inB,
                                     const uint8_t pin_PWM,
                                     const double pwmChangeLimitPerUs)
    : Motor(pin_inA, pin_inB, pin_PWM),
      m_pwmChangeLimitPerUs(pwmChangeLimitPerUs) {}

void hardware::MotorLimited::update() {
  unsigned long timeSincePrevUpdate = micros() - m_prevUpdateTime;

  uint8_t pwmChangeLimit = timeSincePrevUpdate * m_pwmChangeLimitPerUs;
  Motor::setSpeed(constrain(m_speedTarget, m_speed + pwmChangeLimit,
                            m_speed - pwmChangeLimit));

  m_prevUpdateTime += timeSincePrevUpdate;
}

void hardware::MotorLimited::setSpeed(int16_t speed) {
  m_speedTarget = constrain(speed, -255, 255);
}