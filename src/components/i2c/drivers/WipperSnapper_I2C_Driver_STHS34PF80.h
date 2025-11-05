/*!
 * @file WipperSnapper_I2C_Driver_STHS34PF80.h
 *
 * Device driver for the STHS34PF80 IR temperature and presence sensor.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) Tyeth Gundry 2025 for Adafruit Industries.
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */

#ifndef WipperSnapper_I2C_Driver_STHS34PF80_H
#define WipperSnapper_I2C_Driver_STHS34PF80_H

#include "WipperSnapper_I2C_Driver.h"
#include <Adafruit_STHS34PF80.h>
#include <Wire.h>

#define STHS34PF80_FASTTICK_INTERVAL_MS 1000 ///< Enforce ~1 Hz cadence

/**************************************************************************/
/*!
    @brief  Class that provides a driver interface for the STHS34PF80 sensor.
*/
/**************************************************************************/
class WipperSnapper_I2C_Driver_STHS34PF80 : public WipperSnapper_I2C_Driver {
public:
  /*******************************************************************************/
  /*!
      @brief    Constructor for a STHS34PF80 sensor.
      @param    i2c
                The I2C interface.
      @param    sensorAddress
                7-bit device address.
  */
  /*******************************************************************************/
  WipperSnapper_I2C_Driver_STHS34PF80(TwoWire *i2c, uint16_t sensorAddress)
      : WipperSnapper_I2C_Driver(i2c, sensorAddress) {
    _i2c = i2c;
    _sensorAddress = sensorAddress;
    _sths34pf80 = nullptr;
  }

  /*******************************************************************************/
  /*!
      @brief    Destructor for an STHS34PF80 sensor driver.
                Cleans up and deallocates the underlying Adafruit_STHS34PF80 object
                when the driver is destroyed.
  */
  /*******************************************************************************/
  ~WipperSnapper_I2C_Driver_STHS34PF80() {
    if (_sths34pf80) {
      delete _sths34pf80;
      _sths34pf80 = nullptr;
    }
  }

  /*******************************************************************************/
  /*!
      @brief    Initializes the STHS34PF80 sensor and begins I2C.
                Configures for one-shot mode with 32x oversampling and 1 Hz ODR.
      @returns  True if initialized successfully, False otherwise.
  */
  /*******************************************************************************/
  bool begin() {
    _sths34pf80 = new Adafruit_STHS34PF80();
    if (!_sths34pf80 || !_sths34pf80->begin(_sensorAddress, _i2c)) {
      delete _sths34pf80;
      _sths34pf80 = nullptr;
      return false;
    }

    // Configure for one-shot mode with 32x oversampling and 1 Hz ODR
    // Set object temperature averaging to 32 samples
    if (!_sths34pf80->setObjAveraging(STHS34PF80_AVG_TMOS_32)) {
      delete _sths34pf80;
      _sths34pf80 = nullptr;
      return false;
    }

    // Set output data rate to 1 Hz (though we'll use one-shot mode)
    if (!_sths34pf80->setOutputDataRate(STHS34PF80_ODR_1_HZ)) {
      delete _sths34pf80;
      _sths34pf80 = nullptr;
      return false;
    }

    // Set to power-down mode initially (one-shot will be triggered in fastTick)
    if (!_sths34pf80->setOutputDataRate(STHS34PF80_ODR_POWER_DOWN)) {
      delete _sths34pf80;
      _sths34pf80 = nullptr;
      return false;
    }

    // Initialize cached values
    _ambientTemp = 0.0f;
    _objectTemp = 0;
    _presenceValue = 0;
    _motionValue = 0;
    _tempShockValue = 0;
    _lastFastMs = millis() - STHS34PF80_FASTTICK_INTERVAL_MS;

    return true;
  }

  /*******************************************************************************/
  /*!
      @brief    Gets the sensor's current ambient temperature.
      @param    tempEvent
                Pointer to an Adafruit_Sensor event.
      @returns  True if the temperature was obtained successfully, False
                otherwise.
  */
  /*******************************************************************************/
  bool getEventAmbientTemp(sensors_event_t *tempEvent) override {
    if (!_sths34pf80)
      return false;
    tempEvent->temperature = _ambientTemp;
    return true;
  }

  /*******************************************************************************/
  /*!
      @brief    Gets the sensor's current object temperature.
      @param    objectTempEvent
                Pointer to an Adafruit_Sensor event.
      @returns  True if the object temperature was obtained successfully, False
                otherwise.
  */
  /*******************************************************************************/
  bool getEventObjectTemp(sensors_event_t *objectTempEvent) override {
    if (!_sths34pf80)
      return false;
    objectTempEvent->data[0] = (float)_objectTemp;
    return true;
  }

  /*******************************************************************************/
  /*!
      @brief    Gets the sensor's current presence detection value.
      @param    presenceEvent
                Pointer to an Adafruit_Sensor event.
      @returns  True if the presence value was obtained successfully, False
                otherwise.
  */
  /*******************************************************************************/
  bool getEventPresence(sensors_event_t *presenceEvent) override {
    if (!_sths34pf80)
      return false;
    presenceEvent->data[0] = (float)_presenceValue;
    return true;
  }

  /*******************************************************************************/
  /*!
      @brief    Gets the sensor's current motion detection value.
      @param    motionEvent
                Pointer to an Adafruit_Sensor event.
      @returns  True if the motion value was obtained successfully, False
                otherwise.
  */
  /*******************************************************************************/
  bool getEventMotion(sensors_event_t *motionEvent) override {
    if (!_sths34pf80)
      return false;
    motionEvent->data[0] = (float)_motionValue;
    return true;
  }

  /*******************************************************************************/
  /*!
      @brief    Gets the sensor's current temperature shock value.
      @param    tempShockEvent
                Pointer to an Adafruit_Sensor event.
      @returns  True if the temperature shock value was obtained successfully, False
                otherwise.
  */
  /*******************************************************************************/
  bool getEventTempShock(sensors_event_t *tempShockEvent) override {
    if (!_sths34pf80)
      return false;
    tempShockEvent->data[0] = (float)_tempShockValue;
    return true;
  }

  /*******************************************************************************/
  /*!
      @brief  Performs background sampling for the STHS34PF80.

              This method enforces a ~1 Hz cadence using one-shot mode.
              On each call, it checks the elapsed time since the last
              poll using `millis()`. If at least STHS34PF80_FASTTICK_INTERVAL_MS ms
              have passed, it triggers a one-shot measurement. On subsequent calls,
              it checks if data is ready and reads all sensor values
              (ambient temperature, object temperature, presence, motion,
              and temperature shock) and caches them.

              Cached results are later returned by the getter methods
              without re-triggering I2C traffic.

      @note   Called automatically from
              `WipperSnapper_Component_I2C::update()` once per loop iteration.
              Must be non-blocking (no delays). The millis-based guard ensures
              the sensor is not over-polled.
  */
  /*******************************************************************************/
  void fastTick() override {
    if (!_sths34pf80)
      return;

    uint32_t now = millis();

    // State machine for non-blocking operation
    if (_measurementState == IDLE) {
      // Check if it's time to start a new measurement
      if (now - _lastFastMs >= STHS34PF80_FASTTICK_INTERVAL_MS) {
        // Trigger one-shot measurement
        _sths34pf80->triggerOneshot();
        _measurementState = WAITING_FOR_DATA;
        _measurementStartMs = now;
      }
    } else if (_measurementState == WAITING_FOR_DATA) {
      // Check if data is ready or timeout occurred
      if (_sths34pf80->isDataReady()) {
        // Read all sensor values and cache them
        _ambientTemp = _sths34pf80->readAmbientTemperature();
        _objectTemp = _sths34pf80->readObjectTemperature();
        _presenceValue = _sths34pf80->readPresence();
        _motionValue = _sths34pf80->readMotion();
        _tempShockValue = _sths34pf80->readTempShock();

        _lastFastMs = now;
        _measurementState = IDLE;
      } else if (now - _measurementStartMs > 2000) {
        // Timeout after 2 seconds, skip this reading
        _measurementState = IDLE;
        _lastFastMs = now; // Prevent immediate retry
      }
    }
  }

protected:
  Adafruit_STHS34PF80 *_sths34pf80; ///< Pointer to STHS34PF80 sensor object

  /**
   * State machine for non-blocking measurements
   */
  enum MeasurementState {
    IDLE,              ///< Not measuring, waiting for next interval
    WAITING_FOR_DATA   ///< One-shot triggered, waiting for data ready
  };

  MeasurementState _measurementState = IDLE; ///< Current measurement state
  uint32_t _measurementStartMs = 0;          ///< Timestamp when measurement was triggered

  /**
   * Cached latest measurements from the sensor.
   */
  float _ambientTemp = 0.0f;    ///< Cached ambient temperature (°C)
  int16_t _objectTemp = 0;      ///< Cached object temperature (raw)
  int16_t _presenceValue = 0;   ///< Cached presence detection value
  int16_t _motionValue = 0;     ///< Cached motion detection value
  int16_t _tempShockValue = 0;  ///< Cached temperature shock value
  uint32_t _lastFastMs = 0;     ///< Last poll timestamp to enforce 1 Hz cadence
};

#endif // WipperSnapper_I2C_Driver_STHS34PF80_H
