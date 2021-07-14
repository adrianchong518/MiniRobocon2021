#include "control/automatic/PositionControl.h"

#include <math.h>

#include "constants.h"
#include "hardware/hardware.h"
#include "utils/fast_trig.h"

control::automatic::PositionControl::PositionControl()
    : PID(POSITION_CONTROL_PID_KP, POSITION_CONTROL_PID_KI,
          POSITION_CONTROL_PID_KD, 0, 1) {
  setAllowedError(POSITION_CONTROL_PID_ALLOWED_ERROR);
  PID::setTarget(0);
}

void control::automatic::PositionControl::update() {
  if (m_isEnabled) {
    const double xDiff = m_targetPosX - hardware::encoders::xPositionMM;
    const double yDiff = m_targetPosY - hardware::encoders::yPositionMM;
    const double absTargetDistanceSquared = xDiff * xDiff + yDiff * yDiff;
    const double speed = calculatePID(absTargetDistanceSquared);
    const double direction = atan2(xDiff, yDiff);

    hardware::mecanum.setSpeed(speed);
    hardware::mecanum.setDirection(direction);

    // LOG_DEBUG("<Position Control>\t" + String(posX) + "\t" + String(posY) +
    //           "\t" + String(xDiff) + "\t" + String(yDiff) + "\t" +
    //           String(absTargetDistance) + "\t" + String(speed) + "\t" +
    //           String(degrees(direction)));
  }
}

void control::automatic::PositionControl::stop() { setIsEnabled(false); }

void control::automatic::PositionControl::setTarget(double targetPosX,
                                                    double targetPosY) {
  m_targetPosX = targetPosX;
  m_targetPosY = targetPosY;
  LOG_DEBUG("<Position Control>\tPosition Target Set(" + String(targetPosX) +
            ", " + String(targetPosY) + ")");
}

bool control::automatic::PositionControl::isEnabled() const {
  return m_isEnabled;
}

void control::automatic::PositionControl::setIsEnabled(bool isEnabled) {
  m_isEnabled = isEnabled;
  LOG_DEBUG("<Position Control>\t" +
            String(isEnabled ? "Enabled" : "Disabled"));
}