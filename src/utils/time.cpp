#include "utils/time.h"

#include <Arduino.h>

unsigned long time::prevLoopTimeMillis = 0;
unsigned long time::prevLoopTimeTakenMillis = 0;
unsigned long time::currentTimeMillis = 0;

unsigned long time::prevLoopTimeMicros = 0;
unsigned long time::prevLoopTimeTakenMicros = 0;
unsigned long time::currentTimeMicros = 0;

void time::preLoop() {
  currentTimeMillis = millis();
  prevLoopTimeTakenMillis = currentTimeMillis - prevLoopTimeMillis;

  currentTimeMicros = micros();
  prevLoopTimeTakenMicros = currentTimeMicros - prevLoopTimeMicros;
}

void time::postLoop() {
  prevLoopTimeMillis = currentTimeMillis;
  prevLoopTimeMicros = currentTimeMicros;
}