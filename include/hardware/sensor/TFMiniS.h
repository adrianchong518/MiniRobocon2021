// Copyright (c) 2022 adrianchong518
// License: Apache-2.0 (see LICENSE for details)

// Abstractions over the initialization and interface of TFMiniS ToF sensors.

#pragma once

#include <stdint.h>

namespace hardware {
namespace sensor {

class TFMiniS;
class TFMiniSBuilder;

// Abstraction over a TFMiniS ToF sensor
class TFMiniS {
  friend class TFMiniSBuilder;

 public:
  // Return status of sending commands to TFMiniS
  enum class Status : uint8_t {
    // No Error
    kOk = 0,
    // Serial Timeout
    kSerialTimeout,
    // No Header Found
    kHeader,
    // Invalid Checksum
    kChecksum,
    // I2C Timeout
    kI2CTimeout,
    // Reply from some system commands
    kPass,
    // Reply from some system commands
    kFail,
    // I2C Read Error
    kI2CRead,
    // I2C Write Error
    kI2CWrite,
    // i2C Length Error
    kI2CLength,
    // Signal Strength ≤ 100
    kWeak,
    // Signal Strength Saturation
    kStrong,
    // Ambient Light Saturation
    kFlood,
    // Measurement Error
    kMeasure,
  };

  // Supported framerate / poll rate of TFMiniS
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

  // Creates and returns a `TFMiniSBuilder` for `TFMiniS` with the desired I2C
  // `addr` and `framerate` of the sensor
  //
  // Using the builder is the only method of object construction.
  static TFMiniSBuilder Builder(uint8_t addr, Framerate framerate);

  // Resets the sensor to the known state and returns whether the reset
  // succeeded
  [[nodiscard]] bool Reset();

  // The update loop of for the sensor, returning the `Status` of polling the
  // sensor
  //
  // This method can be called as often as possible but the sensor will
  // only be polled at the specified `framerate` with internal timing
  // logic.
  Status Update();

  // Getter for `distance_`
  int16_t distance();

  // Getter for `flux_`
  int16_t flux();

  // Getter for `temperature_`
  int16_t temperature();

 private:
  // Internal constructor for a new TFMiniS object, taking in the desired I2C
  // `addr` and `framerate` of the sensor
  TFMiniS(uint8_t addr, Framerate framerate);

  // Polls the reading from the sensor over I2C and returns the `Status` of
  // polling the sensor
  Status Poll();

  // I2C address of the device
  uint8_t addr_;
  // Poll frequency set for the device
  Framerate framerate_;

  // Distance read in the previous `Poll`
  int16_t distance_ = 0;
  // Flux read in the previous `Poll`
  int16_t flux_ = 0;
  // Temperature read in the previous `Poll`
  int16_t temperature_ = 0;

  // Time interval between polling (`ms`)
  uint16_t poll_interval_;
  // Time for the next poll (`ms`)
  uint32_t next_poll_time_ = 0;
  // Timestamp of the last poll (`ms`)
  uint32_t previous_poll_time_ = 0;
};

// Builder for `TFMiniS`
//
// A builder pattern is used to prevent the usage of a `TFMiniS` sensor without
// first initializing it to a known, desired state.
class TFMiniSBuilder {
 public:
  // Constructor for a new `TFMiniSBuilder` object, taking in the desired I2C
  // `addr` and `framerate` for the sensor
  TFMiniSBuilder(uint8_t addr, TFMiniS::Framerate framerate);

  /**
   * @brief Create the `TFMiniS` object and initialize the sensor
   *
   * @param[out] status Status of the initialization process
   *
   * @return TFMiniS
   */
  // Creates the `TFMiniS` object and initializes the sensor before returning
  // the object. The initialization status is returned through the `status`
  // out parameter.
  TFMiniS Build(bool &status);

 private:
  // I2C address of the device
  uint8_t addr_;
  // Poll frequency set for the device
  TFMiniS::Framerate framerate_;
};

}  // namespace sensor
}  // namespace hardware