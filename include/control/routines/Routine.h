#pragma once

#include <Arduino.h>

#include "constants.h"
#include "hardware/hardware.h"

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
  BR_WALL,
  FWD_DIST_750,
  RETRACT_SERVO,
  HOLD_BALL,
  PUT_BALL,
  HIT_BALL,
  HOLD_HITTER,
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

struct ForwardMoveDist : public Routine {
  double targetYPosition;
  double distance;

  ForwardMoveDist(RoutineID id, const String &name, double distance)
      : Routine(id, name), distance(distance) {}

  void init();
  bool loop();
};

struct RetractServo : public Routine {
  RetractServo() : Routine(RETRACT_SERVO, "retract") {}

  void init() { hardware::servos::setState(0); }
  bool loop() { return true; }
};

struct HoldBall : public Routine {
  HoldBall() : Routine(HOLD_BALL, "hold-ball") {}

  void init() { hardware::servos::setState(1); }
  bool loop() { return true; }
};

struct PutBall : public Routine {
  unsigned long timer;
  uint8_t stage;

  PutBall() : Routine(PUT_BALL, "put") {}

  void init();
  bool loop();
};

struct HitBall : public Routine {
  uint8_t hitPrevStage;

  HitBall() : Routine(HIT_BALL, "hit") {}

  void init();
  bool loop();
};

struct HoldHitter : public Routine {
  HoldHitter() : Routine(HOLD_HITTER, "hold-hitter") {}

  void init();
  bool loop() { return true; }
};

const RoutineID getRoutineIDByName(String name);

static Routine *const routineList[] = {
    new Routine,
    new CardinalMoveWall(FWD_WALL, "fwd-wall", SENSOR_F1, SENSOR_F2, 0.7, 0.3,
                         0),
    new CardinalMoveWall(BKWD_WALL, "bkwd-wall", SENSOR_B1, SENSOR_B2, 0.7, 0.3,
                         M_PI),
    new CardinalMoveWall(LEFT_WALL, "left-wall", SENSOR_L1, SENSOR_L2, 0.6, 0.2,
                         -M_PI_2),
    new CardinalMoveWall(RIGHT_WALL, "right-wall", SENSOR_R1, SENSOR_R2, 0.6,
                         0.2, M_PI_2),
    new FLMoveWall(),
    new FRMoveWall(),
    new BLMoveWall(),
    new BRMoveWall(),
    new ForwardMoveDist(FWD_DIST_750, "fwd-750", 750),
    new RetractServo(),
    new HoldBall(),
    new PutBall(),
    new HitBall(),
    new HoldHitter(),
};

}  // namespace routines
}  // namespace control