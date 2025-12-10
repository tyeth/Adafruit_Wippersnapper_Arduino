// Adafruit IO WipperSnapper Beta (DEBUG BUILD ONLY!)
// Brent Rubell for Adafruit Industries, 2021 - 2023

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

  Serial.begin(115200); // wippersnapper serial
  Serial1.begin(115200);  // ESP-IDF messages serial
  Serial1.setDebugOutput(true); // Enable ESP-IDF messages over Serial1
  //while (!Serial) delay(10);

  wipper->connect();
}

void loop() {
  if (!wipper) {
    return;
  }
  wipper->run();
}