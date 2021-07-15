#include "hardware/BallHitter.h"

#include <Arduino.h>

#include "constants.h"
#include "hardware/interface.h"

hardware::BallHitter::BallHitter(Motor* const motor, const bool isPIDEnabled,
                                 const double Kp, const double Ki,
                                 const double Kd, const uint8_t pidMaxSpeed,
                                 const uint32_t PPR)
    : PID(Kp, Ki, Kd, -pidMaxSpeed, pidMaxSpeed),
      m_motor(motor),
      m_PPR(PPR),
      m_isPIDEnabled(isPIDEnabled) {
  setAllowedError(15);
  setTarget(0);
}

void hardware::BallHitter::loop(const int32_t reading) {
  int16_t motorSpeed = calculatePID(reading % m_PPR);

  if (!m_isPIDEnabled || m_isTargetReached) {
    motorSpeed = m_prevMotorSpeed;
  }

  switch (m_hitStage) {
    case 1:
      if (m_isTargetReached) {
        // Enter LIMBO
        m_isReadyToHit = true;

        m_hitStage = 2;
        LOG_DEBUG("<Ball Hitter>\tEnter Hit Stage\t2");
      }
      break;

    case 2:
      // LIMBO
      break;

    case 3:
      if ((m_hitHoldToStartSpeed < 0 && reading <= m_hitStageTarget) ||
          (m_hitHoldToStartSpeed > 0 && reading >= m_hitStageTarget)) {
        // Start Pos to Mid Pos at hitSpeed
        m_hitStageTarget = reading + m_hitDistStartToMid;
        motorSpeed = m_hitSpeed;

        m_hitStage = 4;
        LOG_DEBUG("<Ball Hitter>\tEnter Hit Stage\t4");
      }
      break;

    case 4:
      if ((m_hitSpeed < 0 && reading <= m_hitStageTarget) ||
          (m_hitSpeed > 0 && reading >= m_hitStageTarget)) {
        // Mid Pos to End Pos at hitMidSpeed
        m_hitStageTarget = reading + m_hitDistMidToEnd;
        motorSpeed = m_hitMidSpeed;

        m_hitStage = 5;
        LOG_DEBUG("<Ball Hitter>\tEnter Hit Stage\t5");
      }
      break;

    case 5:
      if ((m_hitMidSpeed < 0 && reading <= m_hitStageTarget) ||
          (m_hitMidSpeed > 0 && reading >= m_hitStageTarget)) {
        // Start timer
        motorSpeed = 0;
        setMotorSpeed(motorSpeed);
        m_hitCompleteTimer = millis() + 500;

        m_hitStage = 6;
        LOG_DEBUG("<Ball Hitter>\tEnter Hit Stage\t6");
      }
      break;

    case 6:
      if (millis() >= m_hitCompleteTimer) {
        // Go to hold pos
        setIsPIDEnabled(true);
        setTarget(m_hitHoldPos);

        digitalWrite(PIN_BUZZER, LOW);
        m_hitStage = 1;
        LOG_DEBUG("<Ball Hitter>\tEnter Hit Stage\t1");
      }
      break;

    default:
      break;
  }

  setMotorSpeed(motorSpeed);

  // Serial.print(m_motor->getSpeed());
  // Serial.print(" ");
  // Serial.print(reading);
  // Serial.print(" ");
  // Serial.print(m_target);
  // Serial.print(" ");
  // Serial.print(m_hitStageTarget);
  // Serial.println();
}

void hardware::BallHitter::home() {}

void hardware::BallHitter::hit(const int32_t reading) {
  if (m_isReadyToHit) {
    // Hold Pos to Start Pos at hitHoldToStartSpeed
    m_hitStageTarget = reading + m_hitHoldToStartSpeed;
    setIsPIDEnabled(false);
    setMotorSpeed(m_hitHoldToStartSpeed);

    m_isReadyToHit = false;
    digitalWrite(PIN_BUZZER, HIGH);
    m_hitStage = 3;
    LOG_DEBUG("<Ball Hitter>\tEnter Hit Stage\t3");
  }
}

void hardware::BallHitter::hitStartPos(const double holdDeg,
                                       const double startDeg,
                                       const double midDeg, const double endDeg,
                                       const int16_t holdToStartSpeed,
                                       const int16_t speed,
                                       const int16_t midSpeed) {
  m_hitHoldPos = holdDeg / 360 * m_PPR;
  while (m_hitHoldPos >= (int32_t)m_PPR) {
    m_hitHoldPos -= m_PPR;
  }
  while (m_hitHoldPos < 0) {
    m_hitHoldPos += m_PPR;
  }

  m_hitStartPos = startDeg / 360 * m_PPR;
  while (m_hitStartPos >= (int32_t)m_PPR) {
    m_hitStartPos -= m_PPR;
  }
  while (m_hitStartPos < 0) {
    m_hitStartPos += m_PPR;
  }

  m_hitMidPos = midDeg / 360 * m_PPR;
  while (m_hitMidPos >= (int32_t)m_PPR) {
    m_hitMidPos -= m_PPR;
  }
  while (m_hitMidPos < 0) {
    m_hitMidPos += m_PPR;
  }

  m_hitEndPos = endDeg / 360 * m_PPR;
  while (m_hitEndPos >= (int32_t)m_PPR) {
    m_hitEndPos -= m_PPR;
  }
  while (m_hitEndPos < 0) {
    m_hitEndPos += m_PPR;
  }

  m_hitHoldToStartSpeed = holdToStartSpeed;
  m_hitSpeed = speed;
  m_hitMidSpeed = midSpeed;

  m_hitDistHoldToStart = m_hitStartPos - m_hitHoldPos;
  if (m_hitHoldToStartSpeed > 0 && m_hitDistHoldToStart < 0) {
    m_hitDistHoldToStart += m_PPR;
  }
  if (m_hitHoldToStartSpeed < 0 && m_hitDistHoldToStart > 0) {
    m_hitDistHoldToStart -= m_PPR;
  }

  m_hitDistStartToMid = m_hitMidPos - m_hitStartPos;
  if (m_hitSpeed > 0 && m_hitDistStartToMid < 0) {
    m_hitDistStartToMid += m_PPR;
  }
  if (m_hitSpeed < 0 && m_hitDistStartToMid > 0) {
    m_hitDistStartToMid -= m_PPR;
  }

  m_hitDistMidToEnd = m_hitEndPos - m_hitMidPos;
  if (m_hitMidSpeed > 0 && m_hitDistMidToEnd < 0) {
    m_hitDistMidToEnd += m_PPR;
  }
  if (m_hitMidSpeed < 0 && m_hitDistMidToEnd > 0) {
    m_hitDistMidToEnd -= m_PPR;
  }

  // Go to hold pos
  setTarget(m_hitHoldPos);
  m_isReadyToHit = false;
  m_hitStage = 1;
  LOG_DEBUG("<Ball Hitter>\tEnter Hit Stage\t1");
}

PID::CODES hardware::BallHitter::setTarget(const uint16_t target) {
  m_hitStage = 0;
  return PID::setTarget(target % m_PPR);
}

PID::CODES hardware::BallHitter::setTargetDeg(const double degree) {
  LOG_DEBUG("<Ball Hitter>\tTarget Set To " + String(degree) + " deg");
  return setTarget(degree / 360 * m_PPR);
}

int16_t hardware::BallHitter::getMotorSpeed() const {
  return m_motor->getSpeed();
}

void hardware::BallHitter::setMotorSpeed(const int16_t speed) {
  m_prevMotorSpeed = speed;
  m_motor->setSpeed(speed);
}

void hardware::BallHitter::setIsPIDEnabled(const bool isPIDEnabled) {
  if (m_isPIDEnabled != isPIDEnabled) {
    m_cumError = 0;
  }
  m_isPIDEnabled = isPIDEnabled;
  LOG_DEBUG("<Ball Hitter>\tPID " +
            String(isPIDEnabled ? "Enabled" : "Disabled"));
}

double hardware::BallHitter::calculateError(const double reading) {
  double error = m_target - reading;

  while (error > m_PPR / 2) {
    error -= m_PPR;
  }

  while (error < -(int32_t)m_PPR / 2) {
    error += m_PPR;
  }

  return error;
}
