#pragma once

#include <Arduino.h>

#include "constants.h"

namespace control {
namespace routines {

enum RoutineID { NONE, FWD_WALL, BKWD_WALL, LEFT_WALL, RIGHT_WALL };

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
  double direction;

  CardinalMoveWall(RoutineID id, const String &name, uint8_t sensor1Index,
                   uint8_t sensor2Index, double direction)
      : Routine(id, name),
        sensor1Index(sensor1Index),
        sensor2Index(sensor2Index),
        direction(direction) {}

  void init();
  bool loop();
};

const RoutineID getRoutineIDByName(String name);

static Routine *const routineList[] = {
    new Routine,
    new CardinalMoveWall(FWD_WALL, "fwd-wall", SENSOR_F1, SENSOR_F2, 0),
    new CardinalMoveWall(BKWD_WALL, "bkwd-wall", SENSOR_B1, SENSOR_B2, M_PI),
    new CardinalMoveWall(LEFT_WALL, "left-wall", SENSOR_L1, SENSOR_L2, -M_PI_2),
    new CardinalMoveWall(RIGHT_WALL, "right-wall", SENSOR_R1, SENSOR_R2,
                         M_PI_2),
};

}  // namespace routines
}  // namespace control