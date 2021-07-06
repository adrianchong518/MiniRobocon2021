#include "utils/time.h"

#include <Arduino.h>

unsigned long time::prevLoopTimeMicros = 0;
unsigned long time::prevLoopTimeTakenMicros = 0;
unsigned long time::currentTimeMicros = 0;

void time::preLoop() {
  currentTimeMicros = micros();
  prevLoopTimeTakenMicros = currentTimeMicros - prevLoopTimeMicros;
}

void time::postLoop() { prevLoopTimeMicros = currentTimeMicros; }