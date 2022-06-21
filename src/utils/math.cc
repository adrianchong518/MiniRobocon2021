// Copyright (c) 2022 adrianchong518
// License: Apache-2.0 (see LICENSE for details)

#include "utils/math.h"

namespace utils {
namespace math {

uint16_t Abs(int16_t n) {
  uint16_t mask = n >> 15;
  return (mask ^ n) - mask;
}

}  // namespace math
}  // namespace utils