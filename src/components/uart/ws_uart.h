/*!
 * @file ws_uart.h
 *
 * Base class that provides an interface between WipperSnapper's app
 * and the device's UART bus.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) Brent Rubell 2023 for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */
#ifndef WS_UART_H
#define WS_UART_H

#include "Wippersnapper.h"
#include "drivers/ws_uart_drv.h"
#include "drivers/ws_uart_drv_pm25aqi.h"

/**************************************************************************/
/*!
    @brief  Class that provides an interface between WipperSnapper's app
            and the device's UART bus.
*/
/**************************************************************************/
class ws_uart {
public:
  ws_uart(){};
  ~ws_uart(void);

  bool begin(wippersnapper_uart_v1_UARTDeviceAttachRequest
                 *msgUARTRequest); ///< Initializes the UART bus.
  void update(); ///< Updates the UART device at every polling interval, must be
                 ///< called by main app.
private:
#ifdef USE_SW_UART
  SoftwareSerial *_swSerial = nullptr; ///< SoftwareSerial instance
#else
  HardwareSerial *_hwSerial = nullptr; ///< HardwareSerial instance
#endif
  ws_uart_drv_pm25aqi *_pm25aqi = nullptr; ///< Pointer to a PM25 AQI device
};

#endif // WS_UART_H