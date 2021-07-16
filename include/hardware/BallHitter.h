#pragma once

#include <stdint.h>

#include <PID.h>

#include "hardware/Motor.h"

namespace hardware {

class BallHitter : public PID {
 private:
  Motor *const m_motor;

  int32_t m_pos;
  uint32_t m_PPR;

  uint8_t m_hitStage = 0;

  int32_t m_hitHoldPos;
  int32_t m_hitStartPos;
  int32_t m_hitMidPos;
  int32_t m_hitEndPos;

  int16_t m_hitHoldToStartSpeed;
  int16_t m_hitSpeed;
  int16_t m_hitMidSpeed;

  int32_t m_hitDistHoldToStart;
  int32_t m_hitDistStartToMid;
  int32_t m_hitDistMidToEnd;
  int32_t m_hitStageTarget;

  bool m_isReadyToHit = false;

  int16_t m_prevMotorSpeed;
  bool m_isPIDEnabled;

  uint64_t m_hitCompleteTimer;

 public:
  BallHitter(Motor *const motor, const bool isPIDEnabled, const double Kp,
             const double Ki, const double Kd, const uint8_t pidMaxSpeed,
             const uint32_t PPR);

  void loop(const int32_t encoderReading);

  void home();

  void hitStartPos(const double holdDeg, const double startDeg,
                   const double midDeg, const double endDeg,
                   const int16_t holdToStartSpeed, const int16_t speed,
                   const int16_t midSpeed);
  void hit(const int32_t reading);

  PID::CODES setTarget(const uint16_t target);
  PID::CODES setTargetDeg(const double degree);

  int16_t getMotorSpeed() const;
  void setMotorSpeed(const int16_t speed);

  void setIsPIDEnabled(const bool isPIDEnabled);

 protected:
  double calculateError(const double reading);
};

}  // namespace hardware