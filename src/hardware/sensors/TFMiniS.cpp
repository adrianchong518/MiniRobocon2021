#include "hardware/sensors/TFMiniS.h"

#include "constants.h"
#include "hardware/interface.h"

TFMPI2C hardware::sensors::TFMiniS::tfmpI2C;

hardware::sensors::TFMiniS::TFMiniS(uint8_t addr) : m_addr(addr) {}

bool hardware::sensors::TFMiniS::init() {
  LOG_DEBUG("<TFMiniS>\tInitialising 0x" + String(m_addr, HEX) + "...");

  if (tfmpI2C.sendCommand(SOFT_RESET, 0, m_addr)) {
    LOG_DEBUG("<TFMiniS>\t0x" + String(m_addr, HEX) + "\tReset Succeeded");
  } else {
    LOG_ERROR("<TFMiniS>\t0x" + String(m_addr, HEX) + "\tReset Failed");
    return false;
  }

  if (tfmpI2C.sendCommand(SET_FRAME_RATE, FRAME_250, m_addr)) {
    LOG_DEBUG("<TFMiniS>\t0x" + String(m_addr, HEX) +
              "\tSet Frame Rate Succeeded");
  } else {
    LOG_ERROR("<TFMiniS>\t0x" + String(m_addr, HEX) +
              "\tSet Frame Rate Failed");
    return false;
  }

  if (tfmpI2C.sendCommand(DISABLE_OUTPUT, 0, m_addr)) {
    LOG_DEBUG("<TFMiniS>\t0x" + String(m_addr, HEX) +
              "\tDisable Output Stream Succeeded");
  } else {
    LOG_ERROR("<TFMiniS>\t0x" + String(m_addr, HEX) +
              "\tDisable Output Stream Failed");
    return false;
  }

  return true;
}

bool hardware::sensors::TFMiniS::readData() {
  tfmpI2C.getData(m_dist, m_flux, m_temp, m_addr);
  bool status = tfmpI2C.status == TFMP_READY;

  if (!status) {
    LOG_ERROR("<TFMiniS>\t0x" + String(m_addr, HEX) + "\tFailed to Read Data");
  }
  return status;
}

int16_t hardware::sensors::TFMiniS::getDist() const { return m_dist; }

int16_t hardware::sensors::TFMiniS::getFlux() const { return m_flux; }

int16_t hardware::sensors::TFMiniS::getTemp() const { return m_temp; }

bool hardware::sensors::TFMiniS::isEnabled() const { return m_isEnabled; }

void hardware::sensors::TFMiniS::setIsEnabled(const bool isEnabled) {
  m_isEnabled = isEnabled;
  LOG_DEBUG("<TFMiniS>\t0x" + String(m_addr, HEX) + "\t" +
            String(isEnabled ? "Enabled" : "Disabled"));
}

void hardware::sensors::TFMiniS::printValue() const {
  LOG_INFO("<TFMiniS>\t0x" + String(m_addr, HEX) + "\t" + String(m_dist) +
           "cm | " + String(m_flux) + " | " + String(m_temp) + "°C");
}
