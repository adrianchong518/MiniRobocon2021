#include "control/commands.h"

#include "hardware/hardware.h"
#include "control/manual/manual.h"
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
    LOG_INFO("<Mecanum>\tRotation: " +
             String(degrees(hardware::mecanum.getRotation())));
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
  if (command.startsWith("set ")) {
    uint8_t pos = constrain(command.substring(3).toInt(), 0, 180);
    hardware::servos::puttingServo.write(pos);
    LOG_DEBUG("<Servos>\tPutting Right Upper Pos (" + String(pos) + ") Set");
  } else if (command == "r0") {
    hardware::servos::setState(0);
  } else if (command == "r1") {
    hardware::servos::setState(1);
  } else if (command == "r2") {
    hardware::servos::setState(2);
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
  }

  return -1;
}
