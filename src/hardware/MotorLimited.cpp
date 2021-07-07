#include "hardware/MotorLimited.h"

#include "utils/time.h"

hardware::MotorLimited::MotorLimited(const uint8_t pin_inA,
                                     const uint8_t pin_inB,
                                     const uint8_t pin_PWM,
                                     const uint8_t pwmChangeLimitPerMs,
                                     const uint8_t pwmChangeLimitPerLoop)
    : m_pin_inA(pin_inA),
      m_pin_inB(pin_inB),
      m_pin_PWM(pin_PWM),
      m_pwmChangeLimitPerMs(pwmChangeLimitPerMs),
      m_pwmChangeLimitPerLoop(pwmChangeLimitPerLoop) {
  setSpeed(0);
}

void hardware::MotorLimited::update() {
  if (m_speedTarget == m_speed) {
    return;
  }

  uint8_t pwmChangeLimit =
      time::prevLoopTimeTakenMillis * m_pwmChangeLimitPerMs + 1;
  pwmChangeLimit = min(pwmChangeLimit, m_pwmChangeLimitPerLoop);
  setSpeed(constrain(m_speedTarget, m_speed - pwmChangeLimit,
                     m_speed + pwmChangeLimit));
}

void hardware::MotorLimited::setSpeedTarget(const int16_t speedTarget) {
  m_speedTarget = constrain(speedTarget, -255, 255);
}

int16_t hardware::MotorLimited::getSpeedTarget() const { return m_speedTarget; }

void hardware::MotorLimited::setSpeed(const int16_t speed) {
  m_speed = constrain(speed, -255, 255);

  if (m_speed > 0) {
    digitalWrite(m_pin_inA, LOW);
    digitalWrite(m_pin_inB, HIGH);
    analogWrite(m_pin_PWM, m_speed);
  } else if (m_speed < 0) {
    digitalWrite(m_pin_inA, HIGH);
    digitalWrite(m_pin_inB, LOW);
    analogWrite(m_pin_PWM, -m_speed);
  } else {
    digitalWrite(m_pin_inA, HIGH);
    digitalWrite(m_pin_inB, HIGH);
    analogWrite(m_pin_PWM, 0);
  }
}

int16_t hardware::MotorLimited::getSpeed() const { return m_speed; }