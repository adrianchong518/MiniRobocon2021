#include "control/automatic/PositionControl.h"

#include <math.h>

#include "constants.h"
#include "hardware/hardware.h"
#include "utils/fast_trig.h"

control::automatic::PositionControl::PositionControl()
    : PID(POSITION_CONTROL_PID_KP, POSITION_CONTROL_PID_KI,
          POSITION_CONTROL_PID_KD, -1, 1) {
  setAllowedError(POSITION_CONTROL_PID_ALLOWED_ERROR);
}

void control::automatic::PositionControl::update(int16_t posX, int16_t posY) {
  if (m_isEnabled) {
    const double speed = calculatePID(sqrt(posX * posX + posY * posY));
    const double direction =
        atan2_fast(posY - m_targetPosY, posX - m_targetPosX) *
        FAST_TRIG_UINT_TO_RAD;

    hardware::mecanum.setSpeed(speed);
    hardware::mecanum.setDirection(direction);
  }
}

void control::automatic::PositionControl::stop() { setIsEnabled(false); }

void control::automatic::PositionControl::setTarget(int16_t targetPosX,
                                                    int16_t targetPosY) {
  m_targetPosX = targetPosX;
  m_targetPosY = targetPosY;
  PID::setTarget(sqrt(targetPosX * targetPosX + targetPosY * targetPosY));
  LOG_DEBUG("<Position Control>\tPosition Target Set(" + String(targetPosX) +
            ", " + String(targetPosY) + ")");
}

void control::automatic::PositionControl::setTargetMM(double targetPosXMM,
                                                      double targetPosYMM) {
  setTarget(targetPosXMM * ENCODER_X_MM_PER_PULSE,
            targetPosYMM * ENCODER_Y_MM_PER_PULSE);
}

bool control::automatic::PositionControl::isEnabled() const {
  return m_isEnabled;
}

void control::automatic::PositionControl::setIsEnabled(bool isEnabled) {
  m_isEnabled = isEnabled;
}