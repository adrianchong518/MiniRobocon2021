#include "control/routines/Routine.h"

#include "constants.h"
#include "hardware/hardware.h"

const control::routines::RoutineID control::routines::getRoutineIDByName(
    String name) {
  for (Routine *const routine : routineList) {
    if (routine->name == name) {
      return routine->id;
    }
  }

  return RoutineID::NONE;
}

bool control::routines::ForwardWall::hasCollided;

void control::routines::ForwardWall::init() {
  hasCollided = false;
  stage = 0;

  hardware::sensors::distanceSensors[SENSOR_F1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_F2].setIsEnabled(true);

  hardware::sensors::collisionHandler = collisionHandler;
  collisionHandler(hardware::sensors::collisionButtonsPrevState);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(0.5);
  hardware::mecanum.setDirection(0);
}

bool control::routines::ForwardWall::loop() {
  if (hasCollided) {
    hardware::mecanum.setSpeed(0);

    hardware::sensors::distanceSensors[SENSOR_F1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_F2].setIsEnabled(false);

    hardware::sensors::collisionHandler = nullptr;
    return true;
  }

  if (stage == 0 &&
      (hardware::sensors::distanceSensors[SENSOR_F1].getDist() < 10 ||
       hardware::sensors::distanceSensors[SENSOR_F2].getDist() < 10)) {
    hardware::mecanum.setSpeed(0.1);
    stage = 1;
  }

  return false;
}

void control::routines::ForwardWall::collisionHandler(uint8_t buttonsState) {
  LOG_DEBUG("<Sensors>\tCollision Buttons State:\t" +
            String(buttonsState >> SENSOR_F1 & 0b11, BIN));
  if (!(buttonsState >> SENSOR_F1 & 0b11)) {
    hasCollided = true;
  }
}