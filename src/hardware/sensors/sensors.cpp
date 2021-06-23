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

uint8_t hardware::sensors::collisionButtonsPrevState = 0xFF;
void (*hardware::sensors::collisionHandler)(uint8_t) = nullptr;

void hardware::sensors::init() {
  LOG_DEBUG("<Sensors>\tInitialising...");

  for (int i = 0; i < 8; i++) {
    distanceSensors[i].init();
  }

  PORT_COLLISION_BUTTONS_DDR = 0x00;
  PORT_COLLISION_BUTTONS_PORT = 0xFF;
  collisionHandler = [](uint8_t buttonsState) {
    LOG_INFO("<Sensors>\tCollision Buttons State:\t" +
             String(buttonsState, BIN));
  };
}

void hardware::sensors::loop() {
  const unsigned long currentTime = millis();
  if (currentTime - distanceSensorsPrevPollTime >= TFMINIS_POLL_INTERVAL) {
    for (int i = 0; i < 8; i++) {
      if (distanceSensors[i].isEnabled()) {
        distanceSensors[i].readData();
      }
    }
    distanceSensorsPrevPollTime = currentTime;
  }

  uint8_t collisionButtonsState = PORT_COLLISION_BUTTONS_PIN;
  if (collisionButtonsState != collisionButtonsPrevState) {
    if (collisionHandler) {
      (*collisionHandler)(collisionButtonsState);
    }
    collisionButtonsPrevState = collisionButtonsState;
  }
}
