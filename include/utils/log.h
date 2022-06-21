// Copyright (c) 2022 adrianchong518
// License: Apache-2.0 (see LICENSE for details)

// Logging utilities

#pragma once

#include <stddef.h>

namespace utils {
namespace log {

#ifndef LOG_LEVEL
#define LOG_LEVEL 3
#endif

// Logs a format string to `Serial` with `LOG_LEVEL` trace (0)
void trace(const char* fmt, ...);

// Logs a format string to `Serial` with `LOG_LEVEL` debug (<=1)
void debug(const char* fmt, ...);

// Logs a format string to `Serial` with `LOG_LEVEL` info (<=2)
void info(const char* fmt, ...);

// Logs a format string to `Serial` with `LOG_LEVEL` warn (<=3)
void warn(const char* fmt, ...);

// Logs a format string to `Serial` with `LOG_LEVEL` error (<=4)
void error(const char* fmt, ...);

}  // namespace log
}  // namespace utils
