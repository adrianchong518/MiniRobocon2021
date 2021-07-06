#include "hardware/Mecanum.h"

#include <JY901.h>

#include "constants.h"
#include "hardware/interface.h"
#include "hardware/controller.h"
#include "utils/fast_trig.h"

hardware::Mecanum::Mecanum(MotorLimited *const wheelFL,
                           MotorLimited *const wheelFR,
                           MotorLimited *const wheelBL,
                           MotorLimited *const wheelBR)
    : PID(MECANUM_ROT_PID_KP, MECANUM_ROT_PID_KI, MECANUM_ROT_PID_KD,
          MECANUM_ROT_DIFF_PID_MIN, MECANUM_ROT_DIFF_PID_MAX),
      m_wheelFL(wheelFL),
      m_wheelFR(wheelFR),
      m_wheelBL(wheelBL),
      m_wheelBR(wheelBR) {
  m_isTargetLimitEnabled = true;
  m_targetLowerLimit = -180;
  m_targetUpperLimit = 180;

  setAllowedError(MECANUM_ROT_ALLOWED_ERROR);

  SERIAL_GYROSCOPE.begin(SERIAL_GYROSCOPE_BAUDRATE);
}

void hardware::Mecanum::update() {
  bool isGyroUpdated = false;
  while (SERIAL_GYROSCOPE.available()) {
    JY901.CopeSerialData(SERIAL_GYROSCOPE.read());
    isGyroUpdated = true;
  }

  if (isGyroUpdated) {
    m_rotation =
        (double)-JY901.stcAngle.Angle[2] / 32768 * PI - m_rotationOffset;
    if (m_rotation > PI) {
      m_rotation -= 2 * PI;
    } else if (m_rotation < -PI) {
      m_rotation += 2 * PI;
    }

    if (m_isGyroEnabled && m_isEnabled) {
      m_rotationSpeedDiff = calculatePID(m_rotation);
    }
  }

  if (m_isEnabled) {
    setMotorsSpeeds();
  }
}

void hardware::Mecanum::stop() { setIsEnabled(false); }

void hardware::Mecanum::findRotationOffset() {
  LOG_INFO("<Mecanum>\tFinding Rotation Offset...");

  double rotationalOffset = 0;

  unsigned long prevReadingTime = 0;
  int numReadings = 0;
  while (numReadings < 10) {
    while (SERIAL_GYROSCOPE.available()) {
      JY901.CopeSerialData(SERIAL_GYROSCOPE.read());
    }

    unsigned long currTime = millis();
    if (currTime - prevReadingTime >= 100) {
      prevReadingTime = currTime;

      rotationalOffset += (double)-JY901.stcAngle.Angle[2] / 10.0;
      numReadings++;
    }
  }

  m_rotationOffset = rotationalOffset / 32768 * PI;
  LOG_INFO("<Mecanum>\tRotation Offset: " + String(degrees(m_rotationOffset)));
}

void hardware::Mecanum::setSpeed(const double speed) {
  m_speed = constrain(speed, 0, 1);
  LOG_DEBUG("<Mecanum>\tSpeed (" + String(m_speed) + ") Set");
}

void hardware::Mecanum::setDirection(const double direction) {
  m_direction = direction;

  while (m_direction > 2 * PI) {
    m_direction -= 2 * PI;
  }

  while (m_direction < 0) {
    m_direction += 2 * PI;
  }

  LOG_DEBUG("<Mecanum>\tDirection (" + String(degrees(m_direction)) + ") Set");
}

void hardware::Mecanum::setRotationSpeedDiff(const int16_t rotationSpeedDiff) {
  m_rotationSpeedDiff =
      constrain(rotationSpeedDiff, MECANUM_ROT_DIFF_MIN, MECANUM_ROT_DIFF_MAX);
  LOG_DEBUG("<Mecanum>\tRotation Speed Difference (" +
            String(m_rotationSpeedDiff) + ") Set");
}

double hardware::Mecanum::getRotation() const { return degrees(m_rotation); }

void hardware::Mecanum::setTarget(double rotationTarget) {
  while (rotationTarget > PI) {
    rotationTarget -= 2 * PI;
  }

  while (rotationTarget < -PI) {
    rotationTarget += 2 * PI;
  }

  PID::setTarget(rotationTarget);
  LOG_DEBUG("<Mecanum>\tRotation Target (" + String(degrees(rotationTarget)) +
            ") Set");
}

void hardware::Mecanum::getMotorsSpeeds(int16_t &wheelFLSpeed,
                                        int16_t &wheelFRSpeed,
                                        int16_t &wheelBLSpeed,
                                        int16_t &wheelBRSpeed) const {
  wheelFLSpeed = m_wheelFL->getSpeed();
  wheelFRSpeed = m_wheelFR->getSpeed();
  wheelBLSpeed = m_wheelBL->getSpeed();
  wheelBRSpeed = m_wheelBR->getSpeed();
}

void hardware::Mecanum::setMotorsSpeeds() {
  const double halfRotationSpeedDiff = m_rotationSpeedDiff * 0.5;
  const double speedScalingFactor =
      1 - fabs(halfRotationSpeedDiff) * 0.00392157;
  const uint16_t directionScaled =
      (m_direction + M_PI_4) * FAST_TRIG_RAD_TO_UINT;

  const double x0 =
      (double)sin_fast(directionScaled) * FAST_TRIG_RETURN_TO_RESULT;
  const double y0 =
      (double)cos_fast(directionScaled) * FAST_TRIG_RETURN_TO_RESULT;
  const double mapScalingFactor =
      m_speed * 255 * speedScalingFactor / fmax(fabs(x0), fabs(y0));

  const double x1 = x0 * mapScalingFactor;
  const double y1 = y0 * mapScalingFactor;

  m_wheelFL->setSpeedTarget(-(x1 + halfRotationSpeedDiff));
  m_wheelFR->setSpeedTarget((y1 - halfRotationSpeedDiff));
  m_wheelBL->setSpeedTarget((y1 + halfRotationSpeedDiff));
  m_wheelBR->setSpeedTarget(-(x1 - halfRotationSpeedDiff));
}

void hardware::Mecanum::setMotorsSpeeds(const int16_t wheelFLSpeed,
                                        const int16_t wheelFRSpeed,
                                        const int16_t wheelBLSpeed,
                                        const int16_t wheelBRSpeed) {
  m_wheelFL->setSpeedTarget(wheelFLSpeed);
  m_wheelFR->setSpeedTarget(wheelFRSpeed);
  m_wheelBL->setSpeedTarget(wheelBLSpeed);
  m_wheelBR->setSpeedTarget(wheelBRSpeed);
}

bool hardware::Mecanum::isEnabled() const { return m_isEnabled; }

void hardware::Mecanum::setIsEnabled(const bool isEnabled) {
  LOG_DEBUG("<Mecanum>\t" + String(isEnabled ? "Enabled" : "Disabled"));

  m_isEnabled = isEnabled;

  if (!m_isEnabled) {
    setSpeed(0);
    setRotationSpeedDiff(0);
    setMotorsSpeeds();
  }
}

bool hardware::Mecanum::isGyroEnabled() const { return m_isGyroEnabled; }

void hardware::Mecanum::setIsGyroEnabled(const bool isGyroEnabled) {
  LOG_DEBUG("<Mecanum>\tGyroscope " +
            String(isGyroEnabled ? "Enabled" : "Disabled"));

  m_isGyroEnabled = isGyroEnabled;

  interface::lcd.setCursor(17, 3);
  if (m_isGyroEnabled) {
    setTarget(m_rotation);

    interface::lcd.print("G");
  } else {
    setRotationSpeedDiff(0);
    setMotorsSpeeds();

    interface::lcd.print("_");
  }
}

double hardware::Mecanum::calculateError(double reading) {
  double error = m_target - reading;

  if (error > PI) {
    error -= 2 * PI;
  } else if (error < -PI) {
    error += 2 * PI;
  }

  return error;
}