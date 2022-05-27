#include "hardware/sensor/TFMiniS.h"

#include <Arduino.h>
#include <TFMPI2C.h>

#include "utils/log.h"

namespace hardware {
namespace sensor {

namespace {
TFMPI2C tfmpI2C;
}

TFMiniSBuilder::TFMiniSBuilder(uint8_t addr, TFMiniS::Framerate framerate)
    : addr_(addr), framerate_(framerate) {}

TFMiniS TFMiniSBuilder::build(bool& status) {
  TFMiniS sensor(addr_, framerate_);

  status = sensor.Reset();

  return sensor;
}

TFMiniS::TFMiniS(uint8_t addr, TFMiniS::Framerate framerate)
    : addr_(addr),
      framerate_(framerate),
      poll_interval_(1000 / static_cast<uint16_t>(framerate)) {}

TFMiniSBuilder TFMiniS::Builder(uint8_t addr, TFMiniS::Framerate framerate) {
  return TFMiniSBuilder(addr, framerate);
}

bool TFMiniS::Reset() {
  if (tfmpI2C.sendCommand(SOFT_RESET, 0, addr_)) {
    utils::log::debug("[TFMiniS] 0x%02x: Reset Succeeded", addr_);
  } else {
    utils::log::error("[TFMiniS] 0x%02x: Reset Failed", addr_);
    return false;
  }

  if (tfmpI2C.sendCommand(SET_FRAME_RATE, static_cast<uint16_t>(framerate_),
                          addr_)) {
    utils::log::debug("[TFMiniS] 0x%02x: Set Frame Rate Succeeded", addr_);
  } else {
    utils::log::error("[TFMiniS] 0x%02x Set Frame Rate Failed", addr_);
    return false;
  }

  if (tfmpI2C.sendCommand(DISABLE_OUTPUT, 0, addr_)) {
    utils::log::debug("[TFMiniS] 0x%02x Disable Output Stream Succeeded",
                      addr_);
  } else {
    utils::log::error("[TFMiniS] 0x%02x Disable Output Stream Failed", addr_);
    return false;
  }

  return true;
}

TFMiniS::Status TFMiniS::Update() {
  auto current_time = millis();

  if (current_time > next_poll_time_) {
    next_poll_time_ = current_time + poll_interval_;
    return Poll();
  }

  return Status::kOk;
}

TFMiniS::Status TFMiniS::Poll() {
  tfmpI2C.getData(distance_, flux_, temperature_, addr_);
  return static_cast<Status>(tfmpI2C.status);
}

int16_t TFMiniS::distance() { return distance_; }

int16_t TFMiniS::flux() { return flux_; }

int16_t TFMiniS::temperature() { return temperature_; }

}  // namespace sensor
}  // namespace hardware