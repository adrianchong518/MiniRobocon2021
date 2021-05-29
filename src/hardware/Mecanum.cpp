#include "hardware/Mecanum.h"

#include "constants.h"
#include "hardware/interface.h"
#include "utils/fast_trig.h"

hardware::Mecanum::Mecanum(Motor *const wheelFL, Motor *const wheelFR,
                           Motor *const wheelBL, Motor *const wheelBR)
    : PID(MECANUM_ROT_PID_KP, MECANUM_ROT_PID_KI, MECANUM_ROT_PID_KD,
          MECANUM_ROT_DIFF_MIN, MECANUM_ROT_DIFF_MAX),
      m_wheelFL(wheelFL),
      m_wheelFR(wheelFR),
      m_wheelBL(wheelBL),
      m_wheelBR(wheelBR) {
  m_isTargetLimitEnabled = true;
  m_targetLowerLimit = -180;
  m_targetUpperLimit = 180;

  setAllowedError(MECANUM_ROT_ALLOWED_ERROR);

  // SERIAL_GYROSCOPE.begin(SERIAL_GYROSCOPE_BAUDRATE);
}

hardware::Mecanum::~Mecanum() {}

void hardware::Mecanum::update() {
  /*
  while (SERIAL_GYROSCOPE.available()) {
    JY901.CopeSerialData(SERIAL_GYROSCOPE.read());
  }

  m_rotation = (double)-JY901.stcAngle.Angle[2] / 32768 * PI - m_rotationOffset;
  if (m_rotation > PI) {
    m_rotation -= 2 * PI;
  } else if (m_rotation < -PI) {
    m_rotation += 2 * PI;
  }
  */

  if (m_isEnabled) {
    if (m_isGyroEnabled) {
      // m_rotationSpeedDiff = round(calculatePID(m_rotation));
    }

    setMotorsSpeeds();
  }
}

void hardware::Mecanum::stop() { setIsEnabled(false); }

void hardware::Mecanum::moveForward(const uint8_t speed) {
  setIsGyroEnabled(true);
  setDirection(0);
  setSpeed(speed);
}

void hardware::Mecanum::moveBackward(const uint8_t speed) {
  setIsGyroEnabled(true);
  setDirection(PI);
  setSpeed(speed);
}

void hardware::Mecanum::moveStop() {
  setIsGyroEnabled(true);
  setDirection(0);
  setSpeed(0);
}

/*
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
*/

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

double hardware::Mecanum::getRotation() { return degrees(m_rotation); }

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
                                        int16_t &wheelBRSpeed) {
  wheelFLSpeed = m_wheelFLSpeed;
  wheelFRSpeed = m_wheelFRSpeed;
  wheelBLSpeed = m_wheelBLSpeed;
  wheelBRSpeed = m_wheelBRSpeed;
}

void hardware::Mecanum::setMotorsSpeeds() {
  const double halfRotationSpeedDiff = m_rotationSpeedDiff * 0.5;
  const double speedScalingFactor = 1 - abs(halfRotationSpeedDiff) / 255.0;
  const uint16_t directionScaled =
      (m_direction + M_PI_4) * FAST_TRIG_RAD_TO_UINT;

  const double x0 =
      (double)sin_fast(directionScaled) * FAST_TRIG_RETURN_TO_RESULT;
  const double y0 =
      (double)cos_fast(directionScaled) * FAST_TRIG_RETURN_TO_RESULT;
  const double mapScalingFactor =
      1.0 / max(abs(x0), abs(y0)) * m_speed * 255 * speedScalingFactor;

  const double x1 = x0 * mapScalingFactor;
  const double y1 = y0 * mapScalingFactor;

  m_wheelFLSpeed = (x1 + halfRotationSpeedDiff);
  m_wheelFL->setSpeed(m_wheelFLSpeed);

  m_wheelFRSpeed = -(y1 - halfRotationSpeedDiff);
  m_wheelFR->setSpeed(m_wheelFRSpeed);

  m_wheelBLSpeed = (y1 + halfRotationSpeedDiff);
  m_wheelBL->setSpeed(m_wheelBLSpeed);

  m_wheelBRSpeed = -(x1 - halfRotationSpeedDiff);
  m_wheelBR->setSpeed(m_wheelBRSpeed);
}

void hardware::Mecanum::setMotorsSpeeds(const int16_t wheelFLSpeed,
                                        const int16_t wheelFRSpeed,
                                        const int16_t wheelBLSpeed,
                                        const int16_t wheelBRSpeed) {
  m_wheelFLSpeed = wheelFLSpeed;
  m_wheelFL->setSpeed(m_wheelFLSpeed);

  m_wheelFRSpeed = wheelFRSpeed;
  m_wheelFR->setSpeed(m_wheelFRSpeed);

  m_wheelBLSpeed = wheelBLSpeed;
  m_wheelBL->setSpeed(m_wheelBLSpeed);

  m_wheelBRSpeed = wheelBRSpeed;
  m_wheelBR->setSpeed(m_wheelBRSpeed);
}

bool hardware::Mecanum::isEnabled() { return m_isEnabled; }

void hardware::Mecanum::setIsEnabled(const bool isEnabled) {
  LOG_DEBUG("<Mecanum>\t" + String(isEnabled ? "Enabled" : "Disabled"));

  m_isEnabled = isEnabled;

  if (!m_isEnabled) {
    setSpeed(0);
    setRotationSpeedDiff(0);
    setMotorsSpeeds();
  }
}

bool hardware::Mecanum::isGyroEnabled() { return m_isGyroEnabled; }

void hardware::Mecanum::setIsGyroEnabled(const bool isGyroEnabled) {
  LOG_DEBUG("<Mecanum>\tGyroscope " +
            String(isGyroEnabled ? "Enabled" : "Disabled"));

  m_isGyroEnabled = isGyroEnabled;

  if (!m_isGyroEnabled) {
    setRotationSpeedDiff(0);
    setMotorsSpeeds();
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