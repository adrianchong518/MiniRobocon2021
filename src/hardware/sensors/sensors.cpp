#include "hardware/sensors/sensors.h"

#include "constants.h"
#include "hardware/interface.h"

hardware::sensors::TFMiniS hardware::sensors::distanceSensors[8] = {
    hardware::sensors::TFMiniS(I2C_ADDR_TFMINIS_0),
    hardware::sensors::TFMiniS(I2C_ADDR_TFMINIS_1),
    hardware::sensors::TFMiniS(I2C_ADDR_TFMINIS_2),
    hardware::sensors::TFMiniS(I2C_ADDR_TFMINIS_3),
    hardware::sensors::TFMiniS(I2C_ADDR_TFMINIS_4),
    hardware::sensors::TFMiniS(I2C_ADDR_TFMINIS_5),
    hardware::sensors::TFMiniS(I2C_ADDR_TFMINIS_6),
    hardware::sensors::TFMiniS(I2C_ADDR_TFMINIS_7)};

unsigned long hardware::sensors::distanceSensorsPrevPollTime = 0;

void hardware::sensors::init() {
  LOG_DEBUG("<Sensors>\tInitialising...");

  for (int i = 0; i < 8; i++) {
    distanceSensors[i].init();
  }
}

void hardware::sensors::loop() {
  const unsigned long currentTime = millis();
  if (currentTime - distanceSensorsPrevPollTime >= TFMINIS_POLL_INTERVAL) {
    for (int i = 0; i < 8; i++) {
      if (distanceSensors[i].isEnabled()) {
        distanceSensors[i].readData();
      }
      distanceSensorsPrevPollTime = currentTime;
    }
  }
}
