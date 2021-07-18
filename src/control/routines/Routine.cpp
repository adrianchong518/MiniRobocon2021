#include "control/routines/Routine.h"

#include "control/control.h"
#include "utils/time.h"

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
  hasCollidedWithFrontWall = false;
  hasCollidedWithLeftWall = false;

  hardware::sensors::distanceSensors[SENSOR_F1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_F2].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_L1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_L2].setIsEnabled(true);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(0.9);
  hardware::mecanum.setDirection(-0.52359878);
}

bool control::routines::FLMoveWall::loop() {
  hasCollidedWithFrontWall =
      (hardware::sensors::collisionButtonsState & 0b00110000) ||
      hasCollidedWithFrontWall;
  hasCollidedWithLeftWall =
      (hardware::sensors::collisionButtonsState & 0b00000011) ||
      hasCollidedWithLeftWall;

  if (hasCollidedWithFrontWall && hasCollidedWithLeftWall) {
    hardware::mecanum.setSpeed(0);
    return true;
  }

  if (!(stage & 0b01) &&
      (hardware::sensors::distanceSensors[SENSOR_F1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_F2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_F1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_F2].setIsEnabled(false);

    stage |= 0b01;
  }

  if (!(stage & 0b10) &&
      (hardware::sensors::distanceSensors[SENSOR_L1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_L2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_L1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_L2].setIsEnabled(false);

    stage |= 0b10;
  }

  switch (stage) {
    case 0:
      break;

    case 0b01:
      hardware::mecanum.setSpeed(0.5);
      hardware::mecanum.setDirection(-1.3962634);
      break;

    case 0b10:
      hardware::mecanum.setSpeed(0.7);
      hardware::mecanum.setDirection(-0.17453293);
      break;

    case 0b11:
      hardware::mecanum.setSpeed(0.4);
      if (hasCollidedWithFrontWall) {
        hardware::mecanum.setDirection(-1.48352986);
      } else if (hasCollidedWithLeftWall) {
        hardware::mecanum.setDirection(-0.08726646);
      } else {
        hardware::mecanum.setDirection(-M_PI_4);
      }
      break;
  }

  return false;
}

void control::routines::FRMoveWall::init() {
  stage = 0;
  hasCollidedWithFrontWall = false;
  hasCollidedWithRightWall = false;

  hardware::sensors::distanceSensors[SENSOR_F1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_F2].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_R1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_R2].setIsEnabled(true);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(0.9);
  hardware::mecanum.setDirection(0.52359878);
}

bool control::routines::FRMoveWall::loop() {
  hasCollidedWithFrontWall =
      (hardware::sensors::collisionButtonsState & 0b00110000) ||
      hasCollidedWithFrontWall;
  hasCollidedWithRightWall =
      (hardware::sensors::collisionButtonsState & 0b00001100) ||
      hasCollidedWithRightWall;

  if (hasCollidedWithFrontWall && hasCollidedWithRightWall) {
    hardware::mecanum.setSpeed(0);
    return true;
  }

  if (!(stage & 0b01) &&
      (hardware::sensors::distanceSensors[SENSOR_F1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_F2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_F1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_F2].setIsEnabled(false);

    stage |= 0b01;
  }

  if (!(stage & 0b10) &&
      (hardware::sensors::distanceSensors[SENSOR_R1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_R2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_R1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_R2].setIsEnabled(false);

    stage |= 0b10;
  }

  switch (stage) {
    case 0:
      break;

    case 0b01:
      hardware::mecanum.setSpeed(0.5);
      hardware::mecanum.setDirection(1.3962634);
      break;

    case 0b10:
      hardware::mecanum.setSpeed(0.7);
      hardware::mecanum.setDirection(0.17453293);
      break;

    case 0b11:
      hardware::mecanum.setSpeed(0.4);
      if (hasCollidedWithFrontWall) {
        hardware::mecanum.setDirection(1.48352986);
      } else if (hasCollidedWithRightWall) {
        hardware::mecanum.setDirection(0.08726646);
      } else {
        hardware::mecanum.setDirection(M_PI_4);
      }
      break;
  }

  return false;
}

void control::routines::BLMoveWall::init() {
  stage = 0;
  hasCollidedWithBackWall = false;
  hasCollidedWithLeftWall = false;

  hardware::sensors::distanceSensors[SENSOR_B1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_B2].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_L1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_L2].setIsEnabled(true);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(0.9);
  hardware::mecanum.setDirection(-2.61799388);
}

bool control::routines::BLMoveWall::loop() {
  hasCollidedWithBackWall =
      (hardware::sensors::collisionButtonsState & 0b11000000) ||
      hasCollidedWithBackWall;
  hasCollidedWithLeftWall =
      (hardware::sensors::collisionButtonsState & 0b00000011) ||
      hasCollidedWithLeftWall;

  if (hasCollidedWithBackWall && hasCollidedWithLeftWall) {
    hardware::mecanum.setSpeed(0);
    return true;
  }

  if (!(stage & 0b01) &&
      (hardware::sensors::distanceSensors[SENSOR_B1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_B2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_B1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_B2].setIsEnabled(false);

    stage |= 0b01;
  }

  if (!(stage & 0b10) &&
      (hardware::sensors::distanceSensors[SENSOR_L1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_L2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_L1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_L2].setIsEnabled(false);

    stage |= 0b10;
  }

  switch (stage) {
    case 0:
      break;

    case 0b01:
      hardware::mecanum.setSpeed(0.5);
      hardware::mecanum.setDirection(-1.74532925);
      break;

    case 0b10:
      hardware::mecanum.setSpeed(0.7);
      hardware::mecanum.setDirection(-2.96705973);
      break;

    case 0b11:
      hardware::mecanum.setSpeed(0.4);
      if (hasCollidedWithBackWall) {
        hardware::mecanum.setDirection(-1.65806279);
      } else if (hasCollidedWithLeftWall) {
        hardware::mecanum.setDirection(-3.05432619);
      } else {
        hardware::mecanum.setDirection(-(M_PI_4 + M_PI_2));
      }
      break;
  }

  return false;
}

void control::routines::BRMoveWall::init() {
  stage = 0;
  hasCollidedWithBackWall = false;
  hasCollidedWithRightWall = false;

  hardware::sensors::distanceSensors[SENSOR_B1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_B2].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_R1].setIsEnabled(true);
  hardware::sensors::distanceSensors[SENSOR_R2].setIsEnabled(true);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(0.9);
  hardware::mecanum.setDirection(2.61799388);
}

bool control::routines::BRMoveWall::loop() {
  hasCollidedWithBackWall =
      (hardware::sensors::collisionButtonsState & 0b11000000) ||
      hasCollidedWithBackWall;
  hasCollidedWithRightWall =
      (hardware::sensors::collisionButtonsState & 0b00001100) ||
      hasCollidedWithRightWall;

  if (hasCollidedWithBackWall && hasCollidedWithRightWall) {
    hardware::mecanum.setSpeed(0);
    return true;
  }

  if (!(stage & 0b01) &&
      (hardware::sensors::distanceSensors[SENSOR_B1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_B2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_B1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_B2].setIsEnabled(false);

    stage |= 0b01;
  }

  if (!(stage & 0b10) &&
      (hardware::sensors::distanceSensors[SENSOR_R1].getDist() < 15 ||
       hardware::sensors::distanceSensors[SENSOR_R2].getDist() < 15)) {
    hardware::sensors::distanceSensors[SENSOR_R1].setIsEnabled(false);
    hardware::sensors::distanceSensors[SENSOR_R2].setIsEnabled(false);

    stage |= 0b10;
  }

  switch (stage) {
    case 0:
      break;

    case 0b01:
      hardware::mecanum.setSpeed(0.5);
      hardware::mecanum.setDirection(1.74532925);
      break;

    case 0b10:
      hardware::mecanum.setSpeed(0.7);
      hardware::mecanum.setDirection(2.96705973);
      break;

    case 0b11:
      hardware::mecanum.setSpeed(0.4);
      if (hasCollidedWithBackWall) {
        hardware::mecanum.setDirection(1.65806279);
      } else if (hasCollidedWithRightWall) {
        hardware::mecanum.setDirection(3.05432619);
      } else {
        hardware::mecanum.setDirection(M_PI_4 + M_PI_2);
      }
      break;
  }

  return false;
}

void control::routines::ForwardMoveDist::init() {
  targetYPosition = hardware::encoders::yPositionMM + distance;
  Serial.println(hardware::encoders::yPositionMM);
  Serial.println(targetYPosition);

  hardware::mecanum.setIsGyroEnabled(true);
  hardware::mecanum.setSpeed(1);
  hardware::mecanum.setDirection(0);
}

bool control::routines::ForwardMoveDist::loop() {
  if (hardware::encoders::yPositionMM > targetYPosition) {
    hardware::mecanum.setSpeed(0);
    return true;
  }

  return false;
}

void control::routines::PutBall::init() {
  hardware::servos::setState(2);
  timer = time::currentTimeMillis + 500;
  stage = 0;
}

bool control::routines::PutBall::loop() {
  if (stage == 0 && time::currentTimeMillis > timer) {
    hardware::servos::setState(1);
    timer += 500;
    stage = 1;
  }

  if (stage == 1 && time::currentTimeMillis > timer) {
    return true;
  }

  return false;
}

void control::routines::HitBall::init() {
  hitPrevStage = 255;

  hardware::ballHitter.hitStartPos(BALL_HITTER_HOLD_DEG, BALL_HITTER_START_DEG,
                                   BALL_HITTER_MID_DEG, BALL_HITTER_END_DEG,
                                   BALL_HITTER_HOLD_TO_START_SPEED,
                                   BALL_HITTER_SPEED, BALL_HITTER_MID_SPEED);
}

bool control::routines::HitBall::loop() {
  uint8_t currentHitStage = hardware::ballHitter.getHitStage();
  if (hitPrevStage != currentHitStage) {
    if (currentHitStage == 1) {
      hardware::mecanum.setSpeed(0.8);
      switch (zone) {
        case Zone::RED:
          hardware::mecanum.setDirection(2.7925268);
          break;

        case Zone::BLUE:
          hardware::mecanum.setDirection(-2.7925268);
      }
      hardware::mecanum.setMotorsSpeeds();
    } else if (currentHitStage == 2) {
      hardware::mecanum.setSpeed(0);
      hardware::mecanum.setMotorsSpeeds();
    }
  }

  return false;
}

void control::routines::HoldHitter::init() {
  hardware::ballHitter.setTargetDeg(BALL_HITTER_NORMAL_DEG);
}