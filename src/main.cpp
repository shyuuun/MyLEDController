#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include <LittleFS.h>
#include <led/LED.h>
#include "wifi-manager/wifi-manager.h"
#include <web-server/web-server.h>
#include <error-codes/error-codes.h>

void setup() {
  Serial.begin(115200);
  setupLED();

  if (!LittleFS.begin()) {
    showErrorCode(ERROR_FILESYSTEM_INIT);
    return;
  }

  createAP();
  serverRoutes();
  server.begin();

  showSuccess();
}

void loop() {
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  delay(1000);
}
