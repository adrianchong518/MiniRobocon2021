#include "control/commands.h"

#include "hardware/hardware.h"
#include "control/manual/manual.h"
#include "control/automatic/automatic.h"
#include "control/routines/routines.h"
#include "constants.h"

int hardwareCommands(const String &command) {
  if (command == "c") {
    hardware::calibrate();
  } else if (command == "h") {
    hardware::startingPosition();
  } else if (command == "cont") {
    hardware::isHardwareLoopUpdating = true;
    LOG_INFO("<Hardware>\tLoop Continued");
  } else {
    return -1;
  }

  return 0;
}

int mecanumCommands(const String &command) {
  if (command.startsWith("s ")) {
    hardware::mecanum.setSpeed(command.substring(2).toDouble());
  } else if (command.startsWith("d ")) {
    hardware::mecanum.setDirection(radians(command.substring(2).toDouble()));
  } else if (command.startsWith("r ")) {
    hardware::mecanum.setTarget(radians(command.substring(2).toDouble()));
  } else if (command.startsWith("rsd ")) {
    hardware::mecanum.setRotationSpeedDiff(command.substring(4).toInt());
  } else if (command == "ms") {
    int16_t wheelFLSpeed, wheelFRSpeed, wheelBLSpeed, wheelBRSpeed;
    hardware::mecanum.getMotorsSpeeds(wheelFLSpeed, wheelFRSpeed, wheelBLSpeed,
                                      wheelBRSpeed);
    LOG_INFO("<Mecanum>\tWheels Speeds: " + String(wheelFLSpeed) + " | " +
             String(wheelFRSpeed) + " | " + String(wheelBLSpeed) + " | " +
             String(wheelBRSpeed));
  } else if (command == "rr") {
    LOG_INFO("<Mecanum>\tRotation: " + String(hardware::mecanum.getRotation()));
  } else if (command == "gt") {
    hardware::mecanum.setIsGyroEnabled(!hardware::mecanum.isGyroEnabled());
  } else if (command == "c") {
    hardware::mecanum.findRotationOffset();
  } else if (command == "pid") {
    LOG_INFO("<Mecanum>\tPID Constants: " + String(hardware::mecanum.Kp) +
             " | " + String(hardware::mecanum.Ki) + " | " +
             String(hardware::mecanum.Kd));
  } else if (command.startsWith("kp ")) {
    double Kp = command.substring(3).toDouble();
    hardware::mecanum.Kp = Kp;
    LOG_DEBUG("<Mecanum>\tPID Kp (" + String(Kp) + ") Set");
  } else if (command.startsWith("ki ")) {
    double Ki = command.substring(3).toDouble();
    hardware::mecanum.Ki = Ki;
    LOG_DEBUG("<Mecanum>\tPID Ki (" + String(Ki) + ") Set");
  } else if (command.startsWith("kd ")) {
    double Kd = command.substring(3).toDouble();
    hardware::mecanum.Kd = Kd;
    LOG_DEBUG("<Mecanum>\tPID Kd (" + String(Kd) + ") Set");
  } else if (command == "t") {
    hardware::mecanum.setIsEnabled(!hardware::mecanum.isEnabled());
  } else {
    return -1;
  }

  return 0;
}

int servosCommands(const String &command) {
  if (command.startsWith("ru ")) {
    uint8_t pos = constrain(command.substring(3).toInt(), 0, 180);
    hardware::servos::puttingRightUpper.write(pos);
    LOG_DEBUG("<Servos>\tPutting Right Upper Pos (" + String(pos) + ") Set");
  } else if (command.startsWith("rl ")) {
    uint8_t pos = constrain(command.substring(3).toInt(), 0, 180);
    hardware::servos::puttingRightLower.write(pos);
    LOG_DEBUG("<Servos>\tPutting Right Lower Pos (" + String(pos) + ") Set");
  } else if (command.startsWith("lu ")) {
    uint8_t pos = constrain(command.substring(3).toInt(), 0, 180);
    hardware::servos::puttingLeftUpper.write(pos);
    LOG_DEBUG("<Servos>\tPutting Right Upper Pos (" + String(pos) + ") Set");
  } else if (command.startsWith("ll ")) {
    uint8_t pos = constrain(command.substring(3).toInt(), 0, 180);
    hardware::servos::puttingLeftLower.write(pos);
    LOG_DEBUG("<Servos>\tPutting Right Lower Pos (" + String(pos) + ") Set");
  } else if (command == "r1") {
    hardware::servos::puttingRightUpper.write(PUTTING_RIGHT_UPPER_STARTING_POS);
    hardware::servos::puttingRightLower.write(PUTTING_RIGHT_LOWER_STARTING_POS);
  } else if (command == "r2") {
    hardware::servos::puttingRightUpper.write(PUTTING_RIGHT_UPPER_HOLDING_POS);
    hardware::servos::puttingRightLower.write(PUTTING_RIGHT_LOWER_HOLDING_POS);
  } else if (command == "r3") {
    hardware::servos::puttingRightUpper.write(PUTTING_RIGHT_UPPER_PUTTING_POS);
    hardware::servos::puttingRightLower.write(PUTTING_RIGHT_LOWER_PUTTING_POS);
  } else if (command == "l1") {
    hardware::servos::puttingLeftUpper.write(PUTTING_LEFT_UPPER_STARTING_POS);
    hardware::servos::puttingLeftLower.write(PUTTING_LEFT_LOWER_STARTING_POS);
  } else if (command == "l2") {
    hardware::servos::puttingLeftUpper.write(PUTTING_LEFT_UPPER_HOLDING_POS);
    hardware::servos::puttingLeftLower.write(PUTTING_LEFT_LOWER_HOLDING_POS);
  } else if (command == "l3") {
    hardware::servos::puttingLeftUpper.write(PUTTING_LEFT_UPPER_PUTTING_POS);
    hardware::servos::puttingLeftLower.write(PUTTING_LEFT_LOWER_PUTTING_POS);
  } else {
    return -1;
  }

  return 0;
}

int encodersCommands(const String &command) {
  if (command == "r") {
    LOG_INFO("<Encoders>\tX\t" + String(hardware::encoders::encoderXCount) +
             "\t|\t" + String(hardware::encoders::encoderXErrorCount));
    LOG_INFO("<Encoders>\tY\t" + String(hardware::encoders::encoderYCount) +
             "\t|\t" + String(hardware::encoders::encoderYErrorCount));
    LOG_INFO("<Encoders>\tBall Hitter\t" +
             String(hardware::encoders::ballHitterEncoderCount) + "\t|\t" +
             String(hardware::encoders::ballHitterEncoderErrorCount));
  } else if (command == "rx") {
    LOG_INFO("<Encoders>\tX\t" + String(hardware::encoders::encoderXCount) +
             "\t|\t" + String(hardware::encoders::encoderXErrorCount));
  } else if (command == "ry") {
    LOG_INFO("<Encoders>\tY\t" + String(hardware::encoders::encoderYCount) +
             "\t|\t" + String(hardware::encoders::encoderYErrorCount));
  } else if (command == "rbh") {
    LOG_INFO("<Encoders>\tBH\t" +
             String(hardware::encoders::ballHitterEncoderCount) + "\t|\t" +
             String(hardware::encoders::ballHitterEncoderErrorCount));
  } else if (command == "c") {
    hardware::encoders::clearAll();
  } else if (command == "cx") {
    hardware::encoders::clearEncoderX();
  } else if (command == "cy") {
    hardware::encoders::clearEncoderY();
  } else if (command == "cbh") {
    hardware::encoders::clearBallHitterEncoder();
  } else {
    return -1;
  }

  return 0;
}

int distanceSensorsCommands(const String &command) {
  int sensorIndex;

  if (command == "vr") {
    for (int i = 0; i < 8; i++) {
      hardware::sensors::distanceSensors[i].printValue();
    }
    return 0;
  } else if (command == "enable") {
    for (int i = 0; i < 8; i++) {
      hardware::sensors::distanceSensors[i].setIsEnabled(true);
    }
    return 0;
  } else if (command == "disable") {
    for (int i = 0; i < 8; i++) {
      hardware::sensors::distanceSensors[i].setIsEnabled(false);
    }
    return 0;
  }

  sensorIndex = command.substring(0, 1).toInt();
  if (sensorIndex < 0 || sensorIndex >= 8) {
    return -1;
  }

  String subcommand = command.substring(2);
  if (subcommand == "vr") {
    hardware::sensors::distanceSensors[sensorIndex].printValue();
  } else if (subcommand == "enable") {
    hardware::sensors::distanceSensors[sensorIndex].setIsEnabled(true);
  } else if (subcommand == "disable") {
    hardware::sensors::distanceSensors[sensorIndex].setIsEnabled(false);
  } else {
    return -1;
  }

  return 0;
}

int manualCommands(const String &command) {
  if (command == "t") {
    control::manual::setIsManualEnabled(!control::manual::isManualEnabled);
  } else {
    return -1;
  }

  return 0;
}

int automaticCommands(const String &command) {
  if (command == "t") {
    control::automatic::setIsAutomaticEnabled(
        !control::automatic::isAutomaticEnabled);
  } else {
    return -1;
  }

  return 0;
}

int positionControlCommands(const String &command) {
  if (command.startsWith("set ")) {
    double posXMM = command.substring(command.indexOf(' ', 4)).toDouble();
    double posYMM = command.substring(4, command.indexOf(' ', 4)).toDouble();
    control::automatic::positionControl.setTargetMM(posXMM, posYMM);
  } else if (command.startsWith("kp ")) {
    double Kp = command.substring(3).toDouble();
    control::automatic::positionControl.Kp = Kp;
    LOG_DEBUG("<Position Control>\tPID Kp (" + String(Kp) + ") Set");
  } else if (command.startsWith("ki ")) {
    double Ki = command.substring(3).toDouble();
    control::automatic::positionControl.Ki = Ki;
    LOG_DEBUG("<Position Control>\tPID Ki (" + String(Ki) + ") Set");
  } else if (command.startsWith("kd ")) {
    double Kd = command.substring(3).toDouble();
    control::automatic::positionControl.Kd = Kd;
    LOG_DEBUG("<Position Control>\tPID Kd (" + String(Kd) + ") Set");
  } else if (command == "t") {
    control::automatic::positionControl.setIsEnabled(
        !control::automatic::positionControl.isEnabled());
  } else {
    return -1;
  }

  return 0;
}

int runCommands(const String &command) {
  if (command.startsWith("routine ")) {
    control::routines::runRoutine(
        control::routines::getRoutineIDByName(command.substring(8)));
  } else if (command.startsWith("seq ")) {
    control::routines::runSeq(command.substring(4).toInt());
  } else {
    return -1;
  }

  return 0;
}

int control::commands::parseInput(const String &command) {
  if (command.length() == 0) {
    return -1;
  }

  if (command.startsWith("h ")) {
    return hardwareCommands(command.substring(2));
  } else if (command.startsWith("m ")) {
    return mecanumCommands(command.substring(2));
  } else if (command.startsWith("s ")) {
    return servosCommands(command.substring(2));
  } else if (command.startsWith("e ")) {
    return encodersCommands(command.substring(2));
  } else if (command.startsWith("dist ")) {
    return distanceSensorsCommands(command.substring(5));
  } else if (command.startsWith("manual ")) {
    return manualCommands(command.substring(7));
  } else if (command.startsWith("auto ")) {
    return automaticCommands(command.substring(5));
  } else if (command.startsWith("pos ")) {
    return positionControlCommands(command.substring(4));
  } else if (command.startsWith("run ")) {
    return runCommands(command.substring(4));
  }

  return -1;
}
