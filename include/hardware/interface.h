#pragma once

#include <Arduino.h>

#if DEBUG == 1
#define LOG_DEBUG(msg) Serial.println("[DEBUG]\t" + String(msg))
#else
#define LOG_DEBUG(msg)
#endif

#define LOG_INFO(msg) Serial.println("[INFO]\t" + String(msg))
#define LOG_ERROR(msg) Serial.println("[ERROR]\t" + String(msg))

namespace hardware {
namespace interface {}  // namespace interface
}  // namespace hardware