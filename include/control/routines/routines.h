#pragma once

#include <Arduino.h>

#include "control/routines/Routine.h"

namespace control {
namespace routines {

static const RoutineID *const seqList[10] = {nullptr, nullptr, nullptr, nullptr,
                                             nullptr, nullptr, nullptr, nullptr,
                                             nullptr, nullptr};

extern RoutineID runningRoutine;
extern const RoutineID *runningSeqPtr;

void loop();

void runRoutine(const RoutineID &routineID);
void runSeq(const int seqID);

}  // namespace routines
}  // namespace control
