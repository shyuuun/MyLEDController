#include <FastLED.h>
#include "LED.h"
#include "effects.h"

void fadeInOut() {
    static uint8_t brightness = 0;
    static int8_t direction = 1;

    brightness += direction;
    if (brightness == 0 || brightness == 255) {
        direction = -direction;
    }

    fill_solid(leds, NUM_LEDS, CRGB::Purple);
    FastLED.setBrightness(brightness);
    FastLED.show();
}

void runningLed() { 
  // position of the led
  static uint8_t xPos = 0; 
  static int8_t modifier = 1;

  // clear the current LED before moving
  leds[xPos] = CRGB::Black;

  // Move to next position
  xPos += modifier;

  // check boundaries and reverse direction
  if (xPos >= NUM_LEDS - 1) {
    modifier = -1;
    xPos = NUM_LEDS - 1;
  } 

  if (xPos <= 0) { 
    modifier = 1;
    xPos= 0;
  }

  leds[xPos] = CRGB::Purple;


  FastLED.setBrightness(100);
  FastLED.show();
  FastLED.delay(50);
}