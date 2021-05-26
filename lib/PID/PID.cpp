#include <Arduino.h>
#include <PID.h>

PID::PID(const double Kp, const double Ki, const double Kd, const double min,
         const double max)
    : Kp(Kp), Ki(Ki), Kd(Kd), m_min(min), m_max(max) {}

PID::~PID() {}

double PID::calculatePID(double reading) {
  double error = calculateError(reading);
  double rateError = error - m_prevError;

  m_isTargetReached = abs(error) < m_allowedError;

  double tempCumError = m_cumError + error;
  double pid = Kp * error + Ki * m_cumError + Kd * rateError;

  if (pid > m_min && pid < m_max && !m_isTargetReached) {
    m_cumError = tempCumError;
  } else {
    pid = constrain(pid, m_min, m_max);
  }
  m_prevError = error;

  return pid;
}

bool PID::isTargetReached() { return m_isTargetReached; }

void PID::setAllowedError(double allowedError) {
  m_allowedError = allowedError;
}

void PID::setTargetLimitEnabled(const bool isTargetLimitEnabled) {
  m_isTargetLimitEnabled = isTargetLimitEnabled;
}

void PID::setTargetLimit(const double targetLowerLimit,
                         const double targetUpperLimit) {
  m_targetLowerLimit = targetLowerLimit;
  m_targetUpperLimit = targetUpperLimit;
}

double PID::getTarget() { return m_target; }

PID::CODES PID::setTarget(const double target) {
  if (m_isTargetLimitEnabled &&
      (target < m_targetLowerLimit || target > m_targetUpperLimit)) {
    return CODES::ERROR_TARGET_EXCEEDS_LIMIT;
  }

  m_target = target;
  m_isTargetReached = false;
  return CODES::NO_ERROR;
}

double PID::calculateError(double reading) { return m_target - reading; }