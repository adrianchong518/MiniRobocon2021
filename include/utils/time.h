#pragma once

namespace time {

extern unsigned long prevLoopTimeMicros;
extern unsigned long prevLoopTimeTakenMicros;
extern unsigned long currentTimeMicros;

void preLoop();
void postLoop();

}  // namespace time