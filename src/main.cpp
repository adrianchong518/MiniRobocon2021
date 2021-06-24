#include <Arduino.h>
#include <Wire.h>

#include "hardware/hardware.h"
#include "control/control.h"

#define IS_TIMING

void setup() {
  Serial.begin(115200);
  Wire.begin();

  hardware::init();

  while (DEBUG && Serial.read() != '\n')
    ;
  hardware::calibrate();

  while (DEBUG && Serial.read() != '\n')
    ;
  hardware::startingPosition();

  control::init();

  LOG_INFO("<Main>\t\tReady");
}

#ifdef IS_TIMING
unsigned long start, end;
void loop() {
  start = micros();
  // hardware::loop();
  // control::loop();

  hardware::interface::gridDisplayPattern(hardware::interface::RED_UP);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::BLU_UP);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::RED_UP_LEFT);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::BLU_UP_LEFT);
  delay(1000);

  hardware::interface::gridDisplayPattern(
      hardware::interface::RED_UP_LEFT_RETURN);
  delay(1000);

  hardware::interface::gridDisplayPattern(
      hardware::interface::BLU_UP_LEFT_RETURN);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::RED_R);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::BLU_R);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::RED_M);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::BLU_M);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::RED_DOWNRIGHT);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::BLU_DOWNRIGHT);
  delay(1000);

  hardware::interface::gridDisplayPattern(
      hardware::interface::BLU_DOWNRIGHT_RETURN);
  delay(1000);

  hardware::interface::gridDisplayPattern(
      hardware::interface::RED_DOWNRIGHT_RETURN);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::BLU_DOWNLEFT);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::RED_DOWNLEFT);
  delay(1000);

  hardware::interface::gridDisplayPattern(
      hardware::interface::BLU_DOWNLEFT_RETURN);
  delay(1000);

  hardware::interface::gridDisplayPattern(
      hardware::interface::RED_DOWNLEFT_RETURN);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::RED_KICK);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::BLU_KICK);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::BLU_STANDING_BY);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::RED_STANDING_BY);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::DEBUG_1);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::DEBUG_2);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::DEBUG_3);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::DEBUG_4);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::DEBUG_5);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::DEBUG_6);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::DEBUG_7);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::DEBUG_8);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::DEBUG_9);
  delay(1000);

  hardware::interface::gridDisplayPattern(hardware::interface::DEBUG_0);
  delay(1000);

  end = micros();
  LOG_INFO("<Main>\t\tTime Taken:\t" + String(end - start) + "\tus");
}
#else
unsigned long start, end;
void loop() {
  hardware::loop();
  control::loop();
}
#endif