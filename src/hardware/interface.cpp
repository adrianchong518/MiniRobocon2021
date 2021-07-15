#include "hardware/interface.h"

#include "constants.h"

hd44780_I2Cexp hardware::interface::lcd;

Adafruit_NeoPixel hardware::interface::grid(NEOPIXEL_LED_COUNT,
                                            PIN_NEOPIXEL_LED,
                                            NEO_GRB + NEO_KHZ800);

void hardware::interface::init() {
  LOG_DEBUG("<Interface>\tInitialising...");

#if NO_CONTROLLER != 1
  int lcdBeginStatus =
      lcd.begin(CONTROLLER_LCD_NUM_COLS, CONTROLLER_LCD_NUM_ROWS);
  if (lcdBeginStatus) {
    hd44780::fatalError(lcdBeginStatus);
  }
  lcd.clear();

  lcd.setCursor(0, 2);
  lcd.print("--:--");

  lcd.setCursor(0, 3);
  lcd.print("[             ] ----");
#endif

  pinMode(PIN_BUZZER, OUTPUT);

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
