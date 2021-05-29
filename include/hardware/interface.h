#pragma once

#include <Arduino.h>

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
namespace interface {}  // namespace interface
}  // namespace hardware