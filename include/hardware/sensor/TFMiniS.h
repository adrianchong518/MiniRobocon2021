#pragma once

#include <stdint.h>

namespace hardware {
namespace sensor {

class TFMiniS;
class TFMiniSBuilder;

/**
 * @brief Builder for `TFMiniS`
 */
class TFMiniSBuilder {
 public:
  /**
   * @brief Constructor for a new TFMiniSBuilder object
   *
   * @param addr      The I2C address of the TFMiniS sensor (7-bit)
   * @param framerate Poll frequency set for the sensor
   */
  TFMiniSBuilder(uint8_t addr, TFMiniS::Framerate framerate);

  /**
   * @brief Create the `TFMiniS` object and initialize the sensor
   *
   * @param[out] status Status of the initialization process
   *
   * @return TFMiniS
   */
  TFMiniS build(bool &status);

 private:
  uint8_t addr_;                  // I2C address of the device
  TFMiniS::Framerate framerate_;  // Poll frequency set for the device
};

/**
 * @brief Abstraction over a TFMiniS ToF sensor
 */
class TFMiniS {
  friend class TFMiniSBuilder;

 public:
  /**
   * @brief Return status of sending commands to TFMiniS
   */
  enum class Status : uint8_t {
    kOk = 0,         // No Error
    kSerialTimeout,  // Serial Timeout
    kHeader,         // No Header Found
    kChecksum,       // Invalid Checksum
    kI2CTimeout,     // I2C Timeout
    kPass,           // Reply from some system commands
    kFail,           // Reply from some system commands
    kI2CRead,        // I2C Read Error
    kI2CWrite,       // I2C Write Error
    kI2CLength,      // i2C Length Error
    kWeak,           // Signal Strength ≤ 100
    kStrong,         // Signal Strength Saturation
    kFlood,          // Ambient Light Saturation
    kMeasure,        // Measurement Error
  };

  enum class Framerate {
    kFrame0 = 0,
    kFrame1 = 1,
    kFrame2 = 2,
    kFrame5 = 5,
    kFrame10 = 10,
    kFrame20 = 20,
    kFrame25 = 25,
    kFrame50 = 50,
    kFrame100 = 100,
    kFrame125 = 125,
    kFrame200 = 200,
    kFrame250 = 250,
    kFrame500 = 500,
    kFrame1000 = 1000,
  };

  TFMiniS(TFMiniS &&) = default;
  TFMiniS &operator=(TFMiniS &&) = default;

  /**
   * @brief Create a builder for `TFMiniS`
   *
   * Using the builder is the only method of object construction.
   * This is to prevent calling other methods of `TFMiniS` without initializing
   * the sensor first.
   *
   * @param addr      The I2C address of the TFMiniS sensor (7-bit)
   * @param framerate Poll frequency set for the sensor
   *
   * @return TFMiniSBuilder Builder for `TFMiniS`
   */
  static TFMiniSBuilder Builder(uint8_t addr, Framerate framerate);

  /**
   * @brief Reset the sensor
   *
   * @return bool Whether the reset succeeded
   */
  bool Reset();

  /**
   * @brief Update loop of for the sensor
   *
   * This function can be called as often as possible but the sensor will
   * only be polled at the specified `framerate` with internal timing
   * logic.
   *
   * @return bool Status of polling the sensor
   */
  Status Update();

  /**
   * @brief Last polled distance reading
   *
   * @return int16_t distance
   */
  int16_t distance();

  /**
   * @brief Last polled flux reading
   *
   * @return int16_t flux
   */
  int16_t flux();

  /**
   * @brief Last polled temperature reading
   *
   * @return int16_t temperature
   */
  int16_t temperature();

 private:
  /**
   * @brief Internal constructor for a new TFMiniS object
   *
   * @param addr      The I2C address of the TFMiniS sensor (7-bit)
   * @param framerate Poll frequency set for the sensor
   */
  TFMiniS(uint8_t addr, Framerate framerate);

  /**
   * @brief Poll the reading from the sensor over I2C
   *
   * @returns Status Status of polling the sensor
   */
  Status Poll();

  uint8_t addr_;         // I2C address of the device
  Framerate framerate_;  // Poll frequency set for the device

  int16_t distance_ = 0;     // Distance read in the previous `Poll`
  int16_t flux_ = 0;         // Flux read in the previous `Poll`
  int16_t temperature_ = 0;  // Temperature read in the previous `Poll`

  uint16_t poll_interval_;           // Time interval between polling (`ms`)
  uint32_t next_poll_time_ = 0;      // Time for the next poll (`ms`)
  uint32_t previous_poll_time_ = 0;  // Timestamp of the last poll (`ms`)
};

}  // namespace sensor
}  // namespace hardware