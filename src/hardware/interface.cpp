#include "hardware/interface.h"

#include "constants.h"

Adafruit_NeoPixel hardware::interface::grid(NEOPIXEL_LED_COUNT,
                                            PIN_NEOPIXEL_LED,
                                            NEO_GRB + NEO_KHZ800);

void hardware::interface::init() {
  LOG_DEBUG("<Interface>\tInitialising...");

  grid.begin();
  grid.show();
}

void hardware::interface::gridDisplayPattern(
    const uint8_t pattern[NEOPIXEL_LED_COUNT][3]) {
  for (int i = 0; i < NEOPIXEL_LED_COUNT; i++) {
    grid.setPixelColor(i, pgm_read_byte(&pattern[i][0]),
                       pgm_read_byte(&pattern[i][1]),
                       pgm_read_byte(&pattern[i][2]));
  }

  grid.show();
}