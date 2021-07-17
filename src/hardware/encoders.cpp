#include "hardware/encoders.h"

#include <Arduino.h>

#include "constants.h"
#include "hardware/hardware.h"
#include "utils/fast_trig.h"

volatile int32_t hardware::encoders::encoderXCount = 0;
volatile int32_t hardware::encoders::encoderXErrorCount = 0;
volatile uint8_t hardware::encoders::encoderXPrevPhase;

int32_t hardware::encoders::encoderXPrevCount = 0;
double hardware::encoders::xPositionMM = 0;

volatile int32_t hardware::encoders::encoderYCount = 0;
volatile int32_t hardware::encoders::encoderYErrorCount = 0;
volatile uint8_t hardware::encoders::encoderYPrevPhase;

int32_t hardware::encoders::encoderYPrevCount = 0;
double hardware::encoders::yPositionMM = 0;

volatile bool hardware::encoders::ballHitterEncoderIsHoming = false;
volatile int32_t hardware::encoders::ballHitterEncoderCount = 0;
volatile int32_t hardware::encoders::ballHitterEncoderErrorCount = 0;
volatile uint8_t hardware::encoders::ballHitterEncoderPrevPhase;

void encoderXISR() {
  const uint8_t PHASE = PIND >> 2 & 0b11;
  hardware::encoders::encoderXCount +=
      hardware::encoders::PHASE_COMP[PHASE]
                                    [hardware::encoders::encoderXPrevPhase];

  if (!hardware::encoders::PHASE_COMP[PHASE]
                                     [hardware::encoders::encoderXPrevPhase]) {
    hardware::encoders::encoderXErrorCount++;
  }

  hardware::encoders::encoderXPrevPhase = PHASE;
}

ISR(PCINT1_vect) {
  const uint8_t PHASE = PINJ & 0b11;
  hardware::encoders::encoderYCount +=
      hardware::encoders::PHASE_COMP[PHASE]
                                    [hardware::encoders::encoderYPrevPhase];

  if (!hardware::encoders::PHASE_COMP[PHASE]
                                     [hardware::encoders::encoderYPrevPhase]) {
    hardware::encoders::encoderYErrorCount++;
  }

  hardware::encoders::encoderYPrevPhase = PHASE;
}

ISR(PCINT0_vect) {
  const uint8_t PINB_TEMP = PINB;
  const uint8_t PHASE = PINB_TEMP & 0b11;
  hardware::encoders::ballHitterEncoderCount -= hardware::encoders::PHASE_COMP
      [PHASE][hardware::encoders::ballHitterEncoderPrevPhase];

  if (!hardware::encoders::PHASE_COMP
          [PHASE][hardware::encoders::ballHitterEncoderPrevPhase]) {
    hardware::encoders::ballHitterEncoderErrorCount++;
  }

  if (hardware::encoders::ballHitterEncoderIsHoming && PINB_TEMP >> 2 & 0b1) {
    cli();
    hardware::encoders::ballHitterEncoderCount = BALL_HITTER_HOME_OFFSET;
    hardware::encoders::ballHitterEncoderIsHoming = false;
    PCMSK0 = 0b00000011;
    sei();
  }

  hardware::encoders::ballHitterEncoderPrevPhase = PHASE;
}

void hardware::encoders::init() {
  pinMode(PIN_ENCODER_X_CHA, INPUT);
  pinMode(PIN_ENCODER_X_CHB, INPUT);
  encoderXPrevPhase = PIND >> 2 & 0b11;

  pinMode(PIN_ENCODER_Y_CHA, INPUT);
  pinMode(PIN_ENCODER_Y_CHB, INPUT);
  encoderYPrevPhase = PINJ & 0b11;

  pinMode(PIN_BALL_HITTER_ENCODER_CHA, INPUT);
  pinMode(PIN_BALL_HITTER_ENCODER_CHB, INPUT);
  pinMode(PIN_BALL_HITTER_ENCODER_CHZ, INPUT);
  ballHitterEncoderPrevPhase = PINB & 0b11;

  cli();

  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_X_CHA), encoderXISR,
                  CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_X_CHB), encoderXISR,
                  CHANGE);

  PCICR |= (1 << PCIE1);
  PCMSK1 = 0b00000110;

  PCICR |= (1 << PCIE0);
  PCMSK0 = 0b00000011;

  sei();
}

void hardware::encoders::loop() {
  const double xMMDiff =
      (encoderXCount - encoderXPrevCount) * ENCODER_X_MM_PER_PULSE;
  encoderXPrevCount = encoderXCount;

  const double yMMDiff =
      (encoderYCount - encoderYPrevCount) * ENCODER_Y_MM_PER_PULSE;
  encoderYPrevCount = encoderYCount;

  // const uint16_t directionScaled =
  //     hardware::mecanum.getRotation() * FAST_TRIG_RAD_TO_UINT;
  // const double sinValue = sin_fast(directionScaled) * FAST_TRIG_UINT_TO_RAD;
  // const double cosValue = cos_fast(directionScaled) * FAST_TRIG_UINT_TO_RAD;

  const double sinValue = sin(hardware::mecanum.getRotation());
  const double cosValue = cos(hardware::mecanum.getRotation());

  xPositionMM += xMMDiff * cosValue - yMMDiff * sinValue;
  yPositionMM += xMMDiff * sinValue + yMMDiff * cosValue;
}

void hardware::encoders::clearAll() {
  clearEncoderX();
  clearEncoderY();
  clearBallHitterEncoder();
  LOG_DEBUG("<Encoders>\tAll Cleared");
}

void hardware::encoders::clearEncoderX() {
  encoderXCount = 0;
  encoderXPrevCount = 0;
  LOG_DEBUG("<Encoders>\tX Cleared");
}

void hardware::encoders::clearEncoderY() {
  encoderYCount = 0;
  encoderYPrevCount = 0;
  LOG_DEBUG("<Encoders>\tY Cleared");
}

void hardware::encoders::clearEncoderXY() {
  clearEncoderX();
  clearEncoderY();

  xPositionMM = 0;
  yPositionMM = 0;
}

void hardware::encoders::clearBallHitterEncoder() {
  ballHitterEncoderCount = 0;
  ballHitterEncoderIsHoming = false;
  LOG_DEBUG("<Encoders>\tBH Cleared");
}

void hardware::encoders::startBallHitterEncoderHome() {
  cli();
  PCMSK0 = 0b00000111;
  ballHitterEncoderIsHoming = true;
  sei();
}