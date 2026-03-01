#include <FastLED.h>
#include <WiFi.h>
#include "wifi-manager.h"
#include "led/LED.h"
#include "defines.h"
#include "error-codes/error-codes.h"
#include "credentials.h"

// Status LED pin
#define STATUS_LED_PIN 15

void createAP() {
  pinMode(STATUS_LED_PIN, OUTPUT);
  
  bool isAPCreated = WiFi.softAP(DEFAULT_AP_WIFI, DEFAULT_AP_PASSWORD);

  if (isAPCreated) {
    digitalWrite(STATUS_LED_PIN, HIGH);  // Turn on status LED
    showSuccess();
  } else {
    digitalWrite(STATUS_LED_PIN, LOW);
    showErrorCode(ERROR_AP_CREATION);
  }
}

void setupWifi() {
  pinMode(STATUS_LED_PIN, OUTPUT);
  
  WiFi.begin(DEV_WIFI_SSID, DEV_WIFI_PASSWORD);

  int timeout = 60; 

  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(500);
    Serial.print(".");
    
    // Blink LED while connecting
    digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));
    
    timeout--;
  }

  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(STATUS_LED_PIN, HIGH);  // Solid on when connected
    showSuccess();
  } else {
    digitalWrite(STATUS_LED_PIN, LOW);   // Off on failure
    showErrorCode(ERROR_WIFI_CONNECT);
  }

}