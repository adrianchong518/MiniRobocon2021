#pragma once

#include <Arduino.h>

namespace control {
namespace routines {

enum RoutineID {
  NONE,
};

struct {
} data;

struct Routine {
  RoutineID id;
  String name;

  Routine(RoutineID id = RoutineID::NONE, const String &name = "")
      : id(id), name(name) {}

  virtual void init() {}
  virtual bool loop() { return false; }
};

const RoutineID getRoutineIDByName(String name);

Routine *const routineList[] = {
    new Routine,
};

}  // namespace routines
}  // namespace control