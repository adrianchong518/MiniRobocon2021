#pragma once

#include <Arduino.h>

#include "control/routines/Routine.h"

namespace control {
namespace routines {

static const size_t NUM_SEQ = 8;
static const RoutineID seq0[] = {HOLD_BALL, FL_WALL, NONE};
static const RoutineID seq1[] = {BR_WALL, PUT_BALL, FWD_DIST_750, FL_WALL,
                                 NONE};
static const RoutineID seq2[] = {BR_WALL, PUT_BALL, RETRACT_SERVO, HIT_BALL,
                                 NONE};
static const RoutineID seq3[] = {HOLD_HITTER, HOLD_BALL, FWD_DIST_750, FL_WALL,
                                 NONE};
static const RoutineID seq4[] = {HOLD_BALL, FR_WALL, NONE};
static const RoutineID seq5[] = {BL_WALL, PUT_BALL, FWD_DIST_750, FR_WALL,
                                 NONE};
static const RoutineID seq6[] = {BL_WALL, PUT_BALL, RETRACT_SERVO, HIT_BALL,
                                 NONE};
static const RoutineID seq7[] = {HOLD_HITTER, HOLD_BALL, FWD_DIST_750, FR_WALL,
                                 NONE};
static const RoutineID *const seqList[NUM_SEQ] = {seq0, seq1, seq2, seq3,
                                                  seq4, seq5, seq6, seq7};

extern RoutineID runningRoutine;
extern const RoutineID *runningSeqPtr;

void loop();

void runRoutine(const RoutineID &routineID);
void runSeq(const size_t seqID);

}  // namespace routines
}  // namespace control
