#pragma once

#include <Arduino.h>

#include "constants.h"

namespace control {
namespace routines {

enum RoutineID {
  NONE,
  FWD_WALL,
  BKWD_WALL,
  LEFT_WALL,
  RIGHT_WALL,
  FL_WALL,
  FR_WALL,
  BL_WALL,
  BR_WALL
};

struct {
} globalState;

struct Routine {
  RoutineID id;
  String name;

  Routine(RoutineID id = RoutineID::NONE, const String &name = "")
      : id(id), name(name) {}

  virtual void init() {}
  virtual bool loop() { return false; }
};

struct CardinalMoveWall : public Routine {
  uint8_t stage;

  uint8_t sensor1Index;
  uint8_t sensor2Index;
  double speed;
  double slowSpeed;
  double direction;

  CardinalMoveWall(RoutineID id, const String &name, uint8_t sensor1Index,
                   uint8_t sensor2Index, double speed, double slowSpeed,
                   double direction)
      : Routine(id, name),
        sensor1Index(sensor1Index),
        sensor2Index(sensor2Index),
        speed(speed),
        slowSpeed(slowSpeed),
        direction(direction) {}

  void init();
  bool loop();
};

struct FLMoveWall : public Routine {
  uint8_t stage;
  bool hasCollidedWithFrontWall;
  bool hasCollidedWithLeftWall;

  FLMoveWall() : Routine(FL_WALL, "fl-wall") {}

  void init();
  bool loop();
};

struct FRMoveWall : public Routine {
  uint8_t stage;
  bool hasCollidedWithFrontWall;
  bool hasCollidedWithRightWall;

  FRMoveWall() : Routine(FR_WALL, "fr-wall") {}

  void init();
  bool loop();
};

struct BLMoveWall : public Routine {
  uint8_t stage;
  bool hasCollidedWithBackWall;
  bool hasCollidedWithLeftWall;

  BLMoveWall() : Routine(BL_WALL, "bl-wall") {}

  void init();
  bool loop();
};

struct BRMoveWall : public Routine {
  uint8_t stage;
  bool hasCollidedWithBackWall;
  bool hasCollidedWithRightWall;

  BRMoveWall() : Routine(BR_WALL, "br-wall") {}

  void init();
  bool loop();
};

const RoutineID getRoutineIDByName(String name);

static Routine *const routineList[] = {
    new Routine,
    new CardinalMoveWall(FWD_WALL, "fwd-wall", SENSOR_F1, SENSOR_F2, 0.6, 0.3,
                         0),
    new CardinalMoveWall(BKWD_WALL, "bkwd-wall", SENSOR_B1, SENSOR_B2, 0.6, 0.3,
                         M_PI),
    new CardinalMoveWall(LEFT_WALL, "left-wall", SENSOR_L1, SENSOR_L2, 0.5, 0.2,
                         -M_PI_2),
    new CardinalMoveWall(RIGHT_WALL, "right-wall", SENSOR_R1, SENSOR_R2, 0.5,
                         0.2, M_PI_2),
    new FLMoveWall(),
    new FRMoveWall(),
    new BLMoveWall(),
    new BRMoveWall(),
};

}  // namespace routines
}  // namespace control