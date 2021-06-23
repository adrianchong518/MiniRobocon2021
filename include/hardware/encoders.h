#pragma once

#include <stdint.h>

namespace hardware {
namespace encoders {

static const int8_t PHASE_COMP[4][4] = {
    {0, -1, 1, 0}, {1, 0, 0, -1}, {-1, 0, 0, 1}, {0, 1, -1, 0}};

extern volatile int32_t encoderXCount;
extern volatile int32_t encoderXErrorCount;
extern volatile uint8_t encoderXPrevPhase;

extern volatile int32_t encoderYCount;
extern volatile int32_t encoderYErrorCount;
extern volatile uint8_t encoderYPrevPhase;

extern volatile bool ballHitterEncoderIsHoming;
extern volatile int32_t ballHitterEncoderCount;
extern volatile int32_t ballHitterEncoderErrorCount;
extern volatile uint8_t ballHitterEncoderPrevPhase;

void init();

void clearAll();
void clearEncoderX();
void clearEncoderY();
void clearBallHitterEncoder();

void startBallHitterEncoderHome();

}  // namespace encoders
}  // namespace hardware