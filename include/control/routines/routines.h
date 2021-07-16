#pragma once

#include <Arduino.h>

#include "control/routines/Routine.h"

namespace control {
namespace routines {

static const size_t NUM_SEQ = 1;
static const RoutineID seq0[] = {FWD_WALL, NONE};
static const RoutineID *const seqList[NUM_SEQ] = {seq0};

extern RoutineID runningRoutine;
extern const RoutineID *runningSeqPtr;

void loop();

void runRoutine(const RoutineID &routineID);
void runSeq(const size_t seqID);

}  // namespace routines
}  // namespace control
