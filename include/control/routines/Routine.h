#pragma once

#include <Arduino.h>

namespace control {
namespace routines {

enum RoutineID { NONE, FWD_WALL };

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

struct ForwardWall : public Routine {
  uint8_t stage;

  ForwardWall() : Routine(FWD_WALL, "fwd-wall") {}

  void init();
  bool loop();

  static bool hasCollided;
  static void collisionHandler(uint8_t buttonsState);
};

const RoutineID getRoutineIDByName(String name);

static Routine *const routineList[] = {
    new Routine,
    new ForwardWall,
};

}  // namespace routines
}  // namespace control