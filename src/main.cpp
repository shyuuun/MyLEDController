#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN     3        
#define MATRIX_WIDTH  5
#define MATRIX_HEIGHT 5
#define NUM_LEDS  (MATRIX_WIDTH * MATRIX_HEIGHT)
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define BRIGHTNESS 10 

CRGB leds[NUM_LEDS];

// Convert (x, y) to LED index for zigzag layout
uint16_t XY(uint8_t x, uint8_t y) {
  if (y % 2 == 0) {
    return y * MATRIX_WIDTH + x;           // Left → Right
  } else {
    return y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x); // Right → Left
  }
}

float posX = 0;    // Current X position (float for smooth motion)
float posY = 0;    // Current Y position
float velX = 0.5;  // Velocity in X
float velY = 0.4;  // Velocity in Y
uint8_t hue = 0;   // Ball color hue

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);
}

void loop() {
  // Clear all LEDs (fade trail a bit)
  fadeToBlackBy(leds, NUM_LEDS, 40);

  // Update position
  posX += velX;
  posY += velY;

  // Bounce on X edges
  if (posX < 0) {
    posX = 0;
    velX = -velX;
  } else if (posX > MATRIX_WIDTH - 1) {
    posX = MATRIX_WIDTH - 1;
    velX = -velX;
  }

  // Bounce on Y edges
  if (posY < 0) {
    posY = 0;
    velY = -velY;
  } else if (posY > MATRIX_HEIGHT - 1) {
    posY = MATRIX_HEIGHT - 1;
    velY = -velY;
  }

  // Draw the ball
  leds[XY((int)round(posX), (int)round(posY))] = CHSV(hue, 255, 255);

  // Slowly change color
  hue++;

  FastLED.show();
  delay(50);
}
