#include "hardware/encoders.h"

#include <Arduino.h>

#include "constants.h"
#include "hardware/interface.h"

volatile int32_t hardware::encoders::encoderXCount = 0;
volatile int32_t hardware::encoders::encoderXErrorCount = 0;
volatile uint8_t hardware::encoders::encoderXPrevPhase;

volatile int32_t hardware::encoders::encoderYCount = 0;
volatile int32_t hardware::encoders::encoderYErrorCount = 0;
volatile uint8_t hardware::encoders::encoderYPrevPhase;

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

ISR(PCINT2_vect) {
  const uint8_t PINK_TEMP = PINK;
  const uint8_t PHASE = PINK_TEMP >> 4 & 0b11;
  hardware::encoders::ballHitterEncoderCount += hardware::encoders::PHASE_COMP
      [PHASE][hardware::encoders::ballHitterEncoderPrevPhase];

  if (!hardware::encoders::PHASE_COMP
          [PHASE][hardware::encoders::ballHitterEncoderPrevPhase]) {
    hardware::encoders::ballHitterEncoderErrorCount++;
  }

  if (hardware::encoders::ballHitterEncoderIsHoming && PINK_TEMP >> 6 & 0b1) {
    cli();
    hardware::encoders::clearBallHitterEncoder();
    PCMSK2 = 0b00110000;
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
  ballHitterEncoderPrevPhase = PINK >> 4 & 0b11;

  cli();

  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_X_CHA), encoderXISR,
                  CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_X_CHB), encoderXISR,
                  CHANGE);

  PCICR |= (1 << PCIE1);
  PCMSK1 = 0b00000110;

  PCICR |= (1 << PCIE2);
  PCMSK2 = 0b00110000;

  sei();
}

void hardware::encoders::clearAll() {
  clearEncoderX();
  clearEncoderY();
  clearBallHitterEncoder();
  LOG_DEBUG("<Encoders>\tAll Cleared");
}

void hardware::encoders::clearEncoderX() {
  encoderXCount = 0;
  LOG_DEBUG("<Encoders>\tX Cleared");
}

void hardware::encoders::clearEncoderY() {
  encoderYCount = 0;
  LOG_DEBUG("<Encoders>\tY Cleared");
}

void hardware::encoders::clearBallHitterEncoder() {
  ballHitterEncoderCount = 0;
  ballHitterEncoderIsHoming = false;
  LOG_DEBUG("<Encoders>\tBH Cleared");
}

void hardware::encoders::startBallHitterEncoderHome() {
  cli();
  PCMSK2 = 0b01110000;
  ballHitterEncoderIsHoming = true;
  sei();
}