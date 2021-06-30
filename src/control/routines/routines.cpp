#include "control/routines/routines.h"

#include "hardware/interface.h"
#include "control/automatic/automatic.h"

control::routines::RoutineID control::routines::runningRoutine =
    control::routines::RoutineID::NONE;

const control::routines::RoutineID *control::routines::runningSeqPtr = nullptr;

void control::routines::loop() {
  if (runningSeqPtr != nullptr) {
    if (runningRoutine == RoutineID::NONE) {
      if (*runningSeqPtr == RoutineID::NONE) {
        runningSeqPtr = nullptr;
        hardware::interface::lcd.setCursor(0, 2);
        hardware::interface::lcd.print("--");
      } else {
        runRoutine(*(++runningSeqPtr));
      }
    }
  }

  if (runningRoutine != RoutineID::NONE &&
      routineList[runningRoutine]->loop()) {
    runRoutine(RoutineID::NONE);
  }
}

void control::routines::runRoutine(
    const control::routines::RoutineID &routineID) {
  if (!automatic::isAutomaticEnabled) {
    LOG_ERROR("<Routines>\tAutomatic Mode Not Enabled");
    return;
  }

  LOG_DEBUG("<Routines>\tRunning Routine: " + String(routineID));
  hardware::interface::lcd.setCursor(3, 2);
  if (routineID < 10) {
    hardware::interface::lcd.print("0");
  }
  hardware::interface::lcd.print(routineID);

  runningRoutine = routineID;
  routineList[runningRoutine]->init();
}

void control::routines::runSeq(const int seqID) {
  if (seqID < 0 || seqID > 9 || seqList[seqID] == nullptr) {
    LOG_ERROR("<Routines>\tSequence " + String(seqID) + " Not Valid");
    return;
  }

  LOG_DEBUG("<Routines>\tRunning Sequence " + String(seqID));
  hardware::interface::lcd.setCursor(0, 2);
  hardware::interface::lcd.print("0");
  hardware::interface::lcd.print(seqID);

  runningSeqPtr = seqList[seqID];
  runRoutine(*runningSeqPtr);
}