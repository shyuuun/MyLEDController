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

  if(isStationMode) {
    setupWifi();
  } else {
    createAP();
  }

  serverRoutes();
  server.begin();

  showSuccess();
}

void loop() {
  if(isStationMode) { 
    IPAddress IP = WiFi.localIP();
    Serial.print("Station IP address: ");
    Serial.println(IP);
    Serial.print("Station MAC address: ");
    Serial.println(WiFi.macAddress());
  } else { 

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
  }
  delay(1000);
}
