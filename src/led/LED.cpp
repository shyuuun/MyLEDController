#include "defines.h"
#include "LED.h"

// Define the default brightness of the LEDs (0 to 255)
int8_t defaultBrightness  = 50;
const int8_t MAX_BRIGHTNESS = 255;

CRGB color = CRGB(80, 80, 80); 

CRGB leds[NUM_LEDS];

void setupLED() { 
  Serial.println("Setting up LEDs...");
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.clear(true);
}

void turnOn() { 
  fill_solid(leds, NUM_LEDS, color);
}

void turnOff() { 
  FastLED.clear(true);
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

void updateLed(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness, uint8_t led_state){
  FastLED.clear(true);
  setColor(r,g,b);
  setBrightness(brightness);
  fill_solid(leds, NUM_LEDS, color);
  if(led_state == 1) { 
    turnOn();
  } else { 
    turnOff();
  }
  FastLED.show();
}





