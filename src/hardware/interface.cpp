#include "hardware/interface.h"

#include "constants.h"

hd44780_I2Cexp hardware::interface::lcd;

void hardware::interface::init() {
  LOG_DEBUG("<Interface>\tInitialising...");

  int lcdBeginStatus =
      lcd.begin(CONTROLLER_LCD_NUM_COLS, CONTROLLER_LCD_NUM_ROWS);
  if (lcdBeginStatus) {
    hd44780::fatalError(lcdBeginStatus);
  }
  lcd.clear();

  lcd.setCursor(0, 3);
  lcd.print("[             ] ----");
}
