#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include <LittleFS.h>
#include <led/LED.h>
#include "wifi-manager/wifi-manager.h"
#include <web-server/web-server.h>
#include <error-codes/error-codes.h>
#include <functions/functions.h>

void setup() {
  Serial.begin(115200);
  setupLED();
  if (!LittleFS.begin()) {
    showErrorCode(ERROR_FILESYSTEM_INIT);
    return;
  }

  if (isStationMode) {
    setupWifi();
  } else {
    createAP();
  }

  serverRoutes();
  server.begin();

  showSuccess();
}

void loop() {
  static unsigned long lastPrint = 0;

  // Periodic status update to avoid flooding serial output
  if (millis() - lastPrint > 10000) {
    if (isStationMode) {
      Serial.print("Station IP: ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.print("AP IP: ");
      Serial.println(WiFi.softAPIP());
    }
    lastPrint = millis();
  }

  // Prevent watchdog timer resets on ESP32
  delay(10);
}
