#include "control/routines/Routine.h"

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

void control::routines::CardinalMoveWall::init() {
  stage = 0;

  hardware::sensors::distanceSensors[sensor1Index].setIsEnabled(true);
  hardware::sensors::distanceSensors[sensor2Index].setIsEnabled(true);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(0.5);
  hardware::mecanum.setDirection(direction);
}

bool control::routines::CardinalMoveWall::loop() {
  if (!(hardware::sensors::collisionButtonsState >> sensor1Index & 0b11)) {
    hardware::mecanum.setSpeed(0);

    hardware::sensors::distanceSensors[sensor1Index].setIsEnabled(false);
    hardware::sensors::distanceSensors[sensor2Index].setIsEnabled(false);

    return true;
  }

  if (stage == 0 &&
      (hardware::sensors::distanceSensors[sensor1Index].getDist() < 10 ||
       hardware::sensors::distanceSensors[sensor2Index].getDist() < 10)) {
    hardware::mecanum.setSpeed(0.1);
    stage = 1;
  }

  return false;
}