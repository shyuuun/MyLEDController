#include "defines.h"
#include "LED.h"


CRGB leds[NUM_LEDS];

void setupLED() { 
  Serial.println("Setting up LEDs...");
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(DEFAULT_BRIGHTNESS);
  FastLED.clear(true);
}

void turnOn() { 
  fill_solid(leds, NUM_LEDS, CRGB::Amethyst);
  FastLED.show();
}

void turnOff() { 
  FastLED.clear(true);
  FastLED.show();
}


