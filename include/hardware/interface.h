#pragma once

#include <Arduino.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#if DEBUG == 1
#define LOG_DEBUG(msg) \
  Serial.println("\e[;90m[DEBUG]\t" + String(msg) + "\e[0m")
#else
#define LOG_DEBUG(msg)
#endif

#define LOG_INFO(msg) Serial.println("[INFO]\t" + String(msg))
#define LOG_ERROR(msg) \
  Serial.println("\e[1;91m[ERROR]\t" + String(msg) + "\e[0m")

namespace hardware {
namespace interface {

extern hd44780_I2Cexp lcd;

void init();

}  // namespace interface
}  // namespace hardware