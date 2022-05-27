#pragma once

#include <stddef.h>

namespace utils {
namespace log {

#ifndef LOG_LEVEL
#define LOG_LEVEL 3
#endif

void trace(const char* fmt, ...);

void debug(const char* fmt, ...);

void info(const char* fmt, ...);

void warn(const char* fmt, ...);

void error(const char* fmt, ...);

}  // namespace log
}  // namespace utils
