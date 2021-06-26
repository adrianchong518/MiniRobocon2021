#pragma once

#include <Arduino.h>

namespace control {
namespace routines {

enum RoutineID {
  NONE,
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

const RoutineID getRoutineIDByName(String name);

static Routine *const routineList[] = {
    new Routine,
};

}  // namespace routines
}  // namespace control