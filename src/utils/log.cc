// Copyright (c) 2022 adrianchong518
// License: Apache-2.0 (see LICENSE for details)

#include "utils/log.h"

#include <Arduino.h>

namespace utils {
namespace log {

namespace {

char buffer[100];

}

#if LOG_LEVEL <= 0
void trace(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  va_end(args);

  Serial.print("\e[90;2m[TRACE] ");
  Serial.print(buffer);
  Serial.println("\e[0m");
}
#else
void trace(...) {}
#endif

#if LOG_LEVEL <= 1
void debug(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  va_end(args);

  Serial.print("\e[90m[DEBUG] ");
  Serial.print(buffer);
  Serial.println("\e[0m");
}
#else
void debug(...) {}
#endif

#if LOG_LEVEL <= 2
void info(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  va_end(args);

  Serial.print("[INFO]  ");
  Serial.println(buffer);
}
#else
void info(...) {}
#endif

#if LOG_LEVEL <= 3
void warn(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  va_end(args);

  Serial.print("\e[93m[WARN]  ");
  Serial.print(buffer);
  Serial.println("\e[0m");
}
#else
void warn(...) {}
#endif

#if LOG_LEVEL <= 4
void error(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  va_end(args);

  Serial.print("\e[91m[ERROR] ");
  Serial.print(buffer);
  Serial.println("\e[0m");
}
#else
void error(...) {}
#endif

}  // namespace log
}  // namespace utils