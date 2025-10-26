#include "defines.h"
#include "LED.h"
#include "settings/settings.h"

// Define the default brightness of the LEDs (0 to 255)
const uint8_t MAX_BRIGHTNESS = 255;

// LED Values - will be loaded in setupLED()
uint8_t hue;
uint8_t saturation;
uint8_t brightness;
boolean ledState;

CHSV color;

CRGB leds[NUM_LEDS];

void setupLED() {
  Serial.println("Setting up LEDs...");
  
  // Load saved values from preferences
  hue = getHue();
  saturation = getSaturation();
  brightness = getBrightness();
  ledState = getLedState();
  
  color = CHSV(hue, saturation, brightness);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  ledState ? turnOn() : turnOff();
}

void turnOn() {
  ledState = true;
  fill_solid(leds, NUM_LEDS, color);
}

void turnOff() {
  ledState = false;
  // Black provides consistent off state across all LED types
  fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0));
}

void setColor(uint8_t hue, uint8_t saturation, uint8_t brightness) {
  color = CHSV(hue, saturation, brightness);
}

void updateLed(uint8_t h, uint8_t s, uint8_t l, uint8_t led_state) {
  // Update color first to ensure correct color is used when turning on
  setColor(h, s, l);

  if (led_state == 1) {
    ledState = true;
    fill_solid(leds, NUM_LEDS, color);
  } else {
    turnOff();
  }

  FastLED.show();
}





