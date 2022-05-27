#include "utils/math.h"

namespace utils {
namespace math {

uint16_t Abs(int16_t n) {
  uint16_t mask = n >> 15;
  return (mask ^ n) - mask;
}

}  // namespace math
}  // namespace utils