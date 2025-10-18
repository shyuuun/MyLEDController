#include <FastLED.h>
#include <WiFi.h>
#include "wifi-manager.h"
#include "led/LED.h"
#include "defines.h"
#include "error-codes/error-codes.h"
#include "credentials.h"

void createAP() {
  bool isAPCreated = WiFi.softAP(DEFAULT_AP_WIFI, DEFAULT_AP_PASSWORD);

  if (isAPCreated) {
    showSuccess();
  } else {
    showErrorCode(ERROR_AP_CREATION);
  }
}

void setupWifi() {
  WiFi.begin(DEV_WIFI_SSID, DEV_WIFI_PASSWORD);

  int timeout = 20; 

  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(500);
    // TODO: Add a blinking LED effect to indicate connection attempt;
    Serial.print(".");
    timeout--;
  }

  if (WiFi.status() == WL_CONNECTED) {
    showSuccess();
  } else {
    showErrorCode(ERROR_WIFI_CONNECT);
  }



}