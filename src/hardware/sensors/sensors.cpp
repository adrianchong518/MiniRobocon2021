#include "hardware/sensors/sensors.h"

#include "constants.h"
#include "hardware/interface.h"
#include "utils/time.h"

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

uint8_t hardware::sensors::collisionButtonsState = 0xFF;

void hardware::sensors::init() {
  LOG_DEBUG("<Sensors>\tInitialising...");

  for (int i = 0; i < 8; i++) {
    distanceSensors[i].init();
  }

  PORT_COLLISION_BUTTONS_DDR = 0x00;
  PORT_COLLISION_BUTTONS_PORT = 0xFF;
}

void hardware::sensors::loop() {
  if (time::currentTimeMillis - distanceSensorsPrevPollTime >=
      TFMINIS_POLL_INTERVAL) {
    for (int i = 0; i < 8; i++) {
      if (distanceSensors[i].isEnabled()) {
        distanceSensors[i].readData();
      }
    }
    distanceSensorsPrevPollTime = time::currentTimeMillis;
  }

  collisionButtonsState = PORT_COLLISION_BUTTONS_PIN;
}
