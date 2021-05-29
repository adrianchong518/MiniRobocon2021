#pragma once

#include <stdint.h>

#include <TFMPI2C.h>

namespace hardware {
namespace sensors {

class TFMiniS {
 private:
  static TFMPI2C tfmpI2C;

  bool m_isEnabled = false;
  uint8_t m_addr;

  int16_t m_dist = 0;
  int16_t m_flux = 0;
  int16_t m_temp = 0;

 public:
  TFMiniS(uint8_t addr);

  bool init();

  bool readData();

  int16_t getDist();
  int16_t getFlux();
  int16_t getTemp();

  bool isEnabled();
  void setIsEnabled(const bool isEnabled);

  void printValue();
};

}  // namespace sensors
}  // namespace hardware