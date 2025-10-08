#include <FastLED.h>
#include <WiFi.h>
#include "wifi-manager.h"
#include "led/LED.h"
#include "defines.h"
#include "error-codes/error-codes.h"

void createAP() {
  bool isAPCreated = WiFi.softAP(DEFAULT_AP_WIFI, DEFAULT_AP_PASSWORD);

  if (isAPCreated) {
    showSuccess();
  } else {
    showErrorCode(ERROR_AP_CREATION);
  }
}

void setupWifi() {
  // TODO : Implement WiFi setup logic here
}