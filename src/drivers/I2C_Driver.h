/*!
 * @file I2C_Driver.h
 *
 * Base class for a generic I2C sensor device driver.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) Brent Rubell 2021 for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */
#ifndef I2C_Driver_H
#define I2C_Driver_H

#include "Wippersnapper.h"

#include <Adafruit_AHTX0.h>

class I2C_Driver {
    public:
        // GENERIC, shared
        I2C_Driver(uint16_t deviceAddress, TwoWire *i2c);
        ~I2C_Driver();
        void setPeriod(float period);
        virtual bool initSensor();
        virtual void pollSensor();

        bool initAHTX0();
        void enableAHTX0Temperature();
        // Generic
        TwoWire *_i2c = NULL;

        Adafruit_AHTX0 *_ahtx0 = NULL;
        Adafruit_Sensor *_ahtTemperature = NULL;

    private:
        // Generic
        float _pollPeriod;
};

#endif // I2C_Driver_H