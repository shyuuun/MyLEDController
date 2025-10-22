#include "defines.h"
#include "LED.h"

// Define the default brightness of the LEDs (0 to 255)
int8_t defaultBrightness = 50;
const int8_t MAX_BRIGHTNESS = 255;

boolean ledState = false;

// Default startup color (Orangy)
CHSV color = CHSV(28, 153, 128); 

CRGB leds[NUM_LEDS];

void setupLED() {
  Serial.println("Setting up LEDs...");
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  turnOff();
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
    ledState = false;
    fill_solid(leds, NUM_LEDS, CHSV(h, s, l));
  }

  FastLED.show();
}





