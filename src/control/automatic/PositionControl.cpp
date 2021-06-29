#include "control/automatic/PositionControl.h"

#include <math.h>

#include "constants.h"
#include "hardware/hardware.h"
#include "utils/fast_trig.h"

control::automatic::PositionControl::PositionControl()
    : PID(POSITION_CONTROL_PID_KP, POSITION_CONTROL_PID_KI,
          POSITION_CONTROL_PID_KD, 0, 1) {
  setAllowedError(POSITION_CONTROL_PID_ALLOWED_ERROR);
}

void control::automatic::PositionControl::update(int32_t posX, int32_t posY) {
  if (m_isEnabled) {
    const double xDiff = posX - m_targetPosX;
    const double yDiff = posY - m_targetPosY;
    const double absTargetDistance = sqrt(xDiff * xDiff + yDiff * yDiff);
    const double speed = calculatePID(absTargetDistance);
    const double direction = atan2(yDiff, xDiff);

    hardware::mecanum.setSpeed(speed);
    hardware::mecanum.setDirection(direction);

    // LOG_DEBUG("<Position Control>\t" + String(posX) + "\t" + String(posY) +
    //           "\t" + String(xDiff) + "\t" + String(yDiff) + "\t" +
    //           String(absTargetDistance) + "\t" + String(speed) + "\t" +
    //           String(degrees(direction)));
  }
}

void control::automatic::PositionControl::stop() { setIsEnabled(false); }

void control::automatic::PositionControl::setTarget(int32_t targetPosX,
                                                    int32_t targetPosY) {
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

  if (isEnabled)
    LOG_DEBUG("<Position Control>\t" +
              String(isEnabled ? "Enabled" : "Disabled"));
}