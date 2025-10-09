#include "defines.h"
#include "LED.h"

// Define the default brightness of the LEDs (0 to 255)
int8_t defaultBrightness  = 50;
const int8_t MAX_BRIGHTNESS = 255;

boolean ledState = false; // Default LED state (off)

// NOTE: As of now it is white
CRGB color = CRGB(100, 100, 100); 

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
  fill_solid(leds, NUM_LEDS, CRGB::Black); // Use Black instead of clear
}

void setColor(uint8_t r, uint8_t g, uint8_t b) { 
  color = CRGB(r, g, b);
}

void setBrightness(uint8_t brightness){ 
  if (brightness > MAX_BRIGHTNESS) { 
    brightness = MAX_BRIGHTNESS;
  }

  FastLED.setBrightness(brightness);
}

void updateLed(uint8_t r, uint8_t g, uint8_t b, uint8_t led_state){

  if(led_state == 1) { 
    ledState = true;
    fill_solid(leds, NUM_LEDS, color);
  } else { 
    ledState = false;
    fill_solid(leds, NUM_LEDS, CRGB::Black);
 }

  setColor(r,g,b);

  FastLED.show();
}





