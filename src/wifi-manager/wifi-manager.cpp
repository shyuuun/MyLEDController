#include <FastLED.h> 
#include <WiFi.h>
#include "wifi-manager.h"
#include "led/LED.h"
#include "defines.h"


void createAP(){ 
  bool isAPCreated = WiFi.softAP(DEFAULT_AP_WIFI, DEFAULT_AP_PASSWORD);

  if(isAPCreated) {
    leds[0] = CRGB::Green; // Set the first LED to green to indicate AP creation success
    FastLED.show(); // Update the LED state
  } else {
    leds[0] = CRGB::Red; // Set the first LED to red to indicate AP creation failure
    FastLED.show(); // Update the LED state
  }
}

void setupWifi() { 
  // TODO : Implement WiFi setup logic here
}