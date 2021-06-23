#pragma once

#include <stdint.h>

#include <TFMPI2C.h>

namespace hardware {
namespace sensors {

class TFMiniS {
 private:
  static TFMPI2C tfmpI2C;

  bool m_isEnabled = false;
  const uint8_t m_addr;

  int16_t m_dist = 0;
  int16_t m_flux = 0;
  int16_t m_temp = 0;

 public:
  TFMiniS(const uint8_t addr);

  bool init();

  bool readData();

  int16_t getDist() const;
  int16_t getFlux() const;
  int16_t getTemp() const;

  bool isEnabled() const;
  void setIsEnabled(const bool isEnabled);

  void printValue() const;
};

}  // namespace sensors
}  // namespace hardware