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
  hardware::mecanum.setSpeed(speed);
  hardware::mecanum.setDirection(direction);
}

bool control::routines::CardinalMoveWall::loop() {
  if ((hardware::sensors::collisionButtonsState >> sensor1Index & 0b11) ==
      0b11) {
    hardware::mecanum.setSpeed(0);

    hardware::sensors::distanceSensors[sensor1Index].setIsEnabled(false);
    hardware::sensors::distanceSensors[sensor2Index].setIsEnabled(false);

    return true;
  }

  if (stage == 0 &&
      (hardware::sensors::distanceSensors[sensor1Index].getDist() < 15 ||
       hardware::sensors::distanceSensors[sensor2Index].getDist() < 15)) {
    hardware::mecanum.setSpeed(slowSpeed);
    stage = 1;
  }

  return false;
}

void control::routines::FLMoveWall::init() {
  stage = 0;

  hardware::sensors::distanceSensors[SENSOR_F1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_F2].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_L1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_L2].setIsEnabled(true);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(0.8);
  hardware::mecanum.setDirection(-M_PI_4);
}

bool control::routines::FLMoveWall::loop() {
  hasCollidedWithFrontWall =
      (hardware::sensors::collisionButtonsState & 0b00110000) == 0b00110000;
  hasCollidedWithLeftWall =
      (hardware::sensors::collisionButtonsState & 0b00000011) == 0b00000011;

  if (hasCollidedWithFrontWall && hasCollidedWithLeftWall) {
    hardware::mecanum.setSpeed(0);
    return true;
  }

  bool isStageUpdated = false;
  if (!(stage & 0b01) &&
      (hardware::sensors::distanceSensors[SENSOR_F1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_F2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_F1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_F2].setIsEnabled(false);

    isStageUpdated = true;
    stage |= 0b01;
  }

  if (!(stage & 0b10) &&
      (hardware::sensors::distanceSensors[SENSOR_L1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_L2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_L1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_L2].setIsEnabled(false);

    isStageUpdated = true;
    stage |= 0b10;
  }

  if (isStageUpdated) {
    switch (stage) {
      case 0:
        break;

      case 0b01:
        if (hasCollidedWithFrontWall) {
          hardware::mecanum.setSpeed(0.5);
          hardware::mecanum.setDirection(-M_PI_2);
        } else {
          hardware::mecanum.setSpeed(0.65);
          hardware::mecanum.setDirection(-1.107149);
        }
        break;

      case 0b10:
        if (hasCollidedWithLeftWall) {
          hardware::mecanum.setSpeed(0.6);
          hardware::mecanum.setDirection(0);
        } else {
          hardware::mecanum.setSpeed(0.65);
          hardware::mecanum.setDirection(-0.463648);
        }
        break;

      case 0b11:
        if (hasCollidedWithFrontWall) {
          hardware::mecanum.setSpeed(0.2);
          hardware::mecanum.setDirection(-M_PI_2);
        } else if (hasCollidedWithLeftWall) {
          hardware::mecanum.setSpeed(0.3);
          hardware::mecanum.setDirection(0);
        } else {
          hardware::mecanum.setSpeed(0.4);
          hardware::mecanum.setDirection(-M_PI_4);
        }
        break;
    }
  }

  return false;
}

void control::routines::FRMoveWall::init() {
  stage = 0;

  hardware::sensors::distanceSensors[SENSOR_F1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_F2].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_R1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_R2].setIsEnabled(true);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(0.8);
  hardware::mecanum.setDirection(M_PI_4);
}

bool control::routines::FRMoveWall::loop() {
  hasCollidedWithFrontWall =
      (hardware::sensors::collisionButtonsState & 0b00110000) == 0b00110000;
  hasCollidedWithRightWall =
      (hardware::sensors::collisionButtonsState & 0b00001100) == 0b00001100;

  if (hasCollidedWithFrontWall && hasCollidedWithRightWall) {
    hardware::mecanum.setSpeed(0);
    return true;
  }

  bool isStageUpdated = false;
  if (!(stage & 0b01) &&
      (hardware::sensors::distanceSensors[SENSOR_F1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_F2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_F1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_F2].setIsEnabled(false);

    isStageUpdated = true;
    stage |= 0b01;
  }

  if (!(stage & 0b10) &&
      (hardware::sensors::distanceSensors[SENSOR_R1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_R2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_R1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_R2].setIsEnabled(false);

    isStageUpdated = true;
    stage |= 0b10;
  }

  if (isStageUpdated) {
    switch (stage) {
      case 0:
        break;

      case 0b01:
        if (hasCollidedWithFrontWall) {
          hardware::mecanum.setSpeed(0.5);
          hardware::mecanum.setDirection(M_PI_2);
        } else {
          hardware::mecanum.setSpeed(0.65);
          hardware::mecanum.setDirection(1.107149);
        }
        break;

      case 0b10:
        if (hasCollidedWithRightWall) {
          hardware::mecanum.setSpeed(0.6);
          hardware::mecanum.setDirection(0);
        } else {
          hardware::mecanum.setSpeed(0.65);
          hardware::mecanum.setDirection(0.463648);
        }
        break;

      case 0b11:
        if (hasCollidedWithFrontWall) {
          hardware::mecanum.setSpeed(0.2);
          hardware::mecanum.setDirection(M_PI_2);
        } else if (hasCollidedWithRightWall) {
          hardware::mecanum.setSpeed(0.3);
          hardware::mecanum.setDirection(0);
        } else {
          hardware::mecanum.setSpeed(0.4);
          hardware::mecanum.setDirection(M_PI_4);
        }
        break;
    }
  }

  return false;
}

void control::routines::BLMoveWall::init() {
  stage = 0;

  hardware::sensors::distanceSensors[SENSOR_B1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_B2].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_L1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_L2].setIsEnabled(true);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(0.8);
  hardware::mecanum.setDirection(-(M_PI_4 + M_PI_2));
}

bool control::routines::BLMoveWall::loop() {
  hasCollidedWithBackWall =
      (hardware::sensors::collisionButtonsState & 0b11000000) == 0b11000000;
  hasCollidedWithLeftWall =
      (hardware::sensors::collisionButtonsState & 0b00000011) == 0b00000011;

  if (hasCollidedWithBackWall && hasCollidedWithLeftWall) {
    hardware::mecanum.setSpeed(0);
    return true;
  }

  bool isStageUpdated = false;
  if (!(stage & 0b01) &&
      (hardware::sensors::distanceSensors[SENSOR_B1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_B2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_B1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_B2].setIsEnabled(false);

    isStageUpdated = true;
    stage |= 0b01;
  }

  if (!(stage & 0b10) &&
      (hardware::sensors::distanceSensors[SENSOR_L1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_L2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_L1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_L2].setIsEnabled(false);

    isStageUpdated = true;
    stage |= 0b10;
  }

  if (isStageUpdated) {
    switch (stage) {
      case 0:
        break;

      case 0b01:
        if (hasCollidedWithBackWall) {
          hardware::mecanum.setSpeed(0.5);
          hardware::mecanum.setDirection(-M_PI_2);
        } else {
          hardware::mecanum.setSpeed(0.65);
          hardware::mecanum.setDirection(-2.034444);
        }
        break;

      case 0b10:
        if (hasCollidedWithLeftWall) {
          hardware::mecanum.setSpeed(0.6);
          hardware::mecanum.setDirection(-M_PI);
        } else {
          hardware::mecanum.setSpeed(0.65);
          hardware::mecanum.setDirection(-2.677945);
        }
        break;

      case 0b11:
        if (hasCollidedWithBackWall) {
          hardware::mecanum.setSpeed(0.2);
          hardware::mecanum.setDirection(-M_PI_2);
        } else if (hasCollidedWithLeftWall) {
          hardware::mecanum.setSpeed(0.3);
          hardware::mecanum.setDirection(-M_PI);
        } else {
          hardware::mecanum.setSpeed(0.4);
          hardware::mecanum.setDirection(-(M_PI_4 + M_PI_2));
        }
        break;
    }
  }

  return false;
}

void control::routines::BRMoveWall::init() {
  stage = 0;

  hardware::sensors::distanceSensors[SENSOR_B1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_B2].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_R1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_R2].setIsEnabled(true);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(0.8);
  hardware::mecanum.setDirection(M_PI_4 + M_PI_2);
}

bool control::routines::BRMoveWall::loop() {
  hasCollidedWithBackWall =
      (hardware::sensors::collisionButtonsState & 0b11000000) == 0b11000000;
  hasCollidedWithRightWall =
      (hardware::sensors::collisionButtonsState & 0b00001100) == 0b00001100;

  if (hasCollidedWithBackWall && hasCollidedWithRightWall) {
    hardware::mecanum.setSpeed(0);
    return true;
  }

  bool isStageUpdated = false;
  if (!(stage & 0b01) &&
      (hardware::sensors::distanceSensors[SENSOR_B1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_B2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_B1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_B2].setIsEnabled(false);

    isStageUpdated = true;
    stage |= 0b01;
  }

  if (!(stage & 0b10) &&
      (hardware::sensors::distanceSensors[SENSOR_R1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_R2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_R1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_R2].setIsEnabled(false);

    isStageUpdated = true;
    stage |= 0b10;
  }

  if (isStageUpdated) {
    switch (stage) {
      case 0:
        break;

      case 0b01:
        if (hasCollidedWithBackWall) {
          hardware::mecanum.setSpeed(0.5);
          hardware::mecanum.setDirection(M_PI_2);
        } else {
          hardware::mecanum.setSpeed(0.65);
          hardware::mecanum.setDirection(2.034444);
        }
        break;

      case 0b10:
        if (hasCollidedWithRightWall) {
          hardware::mecanum.setSpeed(0.6);
          hardware::mecanum.setDirection(M_PI);
        } else {
          hardware::mecanum.setSpeed(0.65);
          hardware::mecanum.setDirection(2.677945);
        }
        break;

      case 0b11:
        if (hasCollidedWithBackWall) {
          hardware::mecanum.setSpeed(0.2);
          hardware::mecanum.setDirection(M_PI_2);
        } else if (hasCollidedWithRightWall) {
          hardware::mecanum.setSpeed(0.3);
          hardware::mecanum.setDirection(M_PI);
        } else {
          hardware::mecanum.setSpeed(0.4);
          hardware::mecanum.setDirection(M_PI_4 + M_PI_2);
        }
        break;
    }
  }

  return false;
}