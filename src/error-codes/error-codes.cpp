#include "error-codes.h"
#include <Arduino.h>

void showErrorCode(ErrorCode code) {
  // Clear all LEDs first
  FastLED.clear();

  switch (code) {
    case ERROR_FILESYSTEM_INIT:
      // 2 Red LEDs for filesystem initialization failure
      leds[0] = CRGB::Red;
      leds[1] = CRGB::Red;
      Serial.println("ERROR: LittleFS initialization failed");
      break;

    case ERROR_AP_CREATION:
      // 3 Red LEDs for Access Point creation failure
      leds[0] = CRGB::Red;
      leds[1] = CRGB::Red;
      leds[2] = CRGB::Red;
      Serial.println("ERROR: Access Point creation failed");
      break;

    case ERROR_SERVER_INIT:
      // 4 Red LEDs for server initialization failure
      leds[0] = CRGB::Red;
      leds[1] = CRGB::Red;
      leds[2] = CRGB::Red;
      leds[3] = CRGB::Red;
      Serial.println("ERROR: Web server initialization failed");
      break;

    case ERROR_WIFI_CONNECT:
      // 5 Red LEDs for WiFi connection failure
      leds[0] = CRGB::Red;
      leds[1] = CRGB::Red;
      leds[2] = CRGB::Red;
      leds[3] = CRGB::Red;
      leds[4] = CRGB::Red;
      Serial.println("ERROR: WiFi connection failed");
      break;

    case ERROR_FILE_NOT_FOUND:
      // 2 Yellow LEDs for file not found
      leds[0] = CRGB::Yellow;
      leds[1] = CRGB::Yellow;
      Serial.println("WARNING: File not found");
      break;

    default:
      // Unknown error - show alternating red pattern
      leds[0] = CRGB::Red;
      leds[2] = CRGB::Red;
      leds[4] = CRGB::Red;
      Serial.println("ERROR: Unknown error code");
      break;
  }

  FastLED.show();
}

void showSuccess() {
  // Brief green flash on first LED
  leds[0] = CRGB::Green;
  FastLED.show();
  FastLED.delay(500);
  
  // Clear all LEDs and restore saved state
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  
  if (ledState) {
    fill_solid(leds, NUM_LEDS, color);
  }
  FastLED.show();
}

void showWarning(int ledIndex) {
  leds[ledIndex] = CRGB::Yellow;
  FastLED.show();
}
