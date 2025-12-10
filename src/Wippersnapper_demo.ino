// Adafruit IO WipperSnapper Beta
//
//
// NOTE: This software is a BETA release and in active development.
// Please report bugs or errors to https://github.com/adafruit/Adafruit_Wippersnapper_Arduino/issues
//
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Brent Rubell for Adafruit Industries, 2021-2022
//
// All text above must be included in any redistribution.

#include "Wippersnapper_Networking.h"
static Wippersnapper_WiFi *wipper = nullptr; // Allocate at runtime to save DRAM

// Enable debug output for beta builds
#define WS_DEBUG

void setup() {
  if (!wipper) {
    wipper = new Wippersnapper_WiFi();
    if (!wipper) {
      WS_PRINTER.begin(115200);
      while (true) {
        WS_DEBUG_PRINTLN("Failed to allocate Wippersnapper_WiFi instance");
        delay(1000);
      }
    }
  }

  // Provisioning must occur prior to serial init.
  wipper->provision();

  Serial.begin(115200);
  // while (!Serial) delay(10);

  wipper->connect();

}

void loop() {
  if (!wipper) {
    return;
  }
  wipper->run();
}