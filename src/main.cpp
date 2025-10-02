#include <Arduino.h>
#include <FastLED.h> // Include the FastLED library

#define NUM_LEDS 25 // Total LEDs (5x5)
#define DATA_PIN 39 // Digital pin connected to the LED matrix data line
#define LED_TYPE WS2812 // Type of LEDs in your matrix

CRGB leds[NUM_LEDS]; // Array to hold LED color data

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // Initialize the LED strip/matrix
  FastLED.setBrightness(20); // Set initial brightness (0-255)
  FastLED.clear(); // Turn all LEDs off initially
  FastLED.show(); // Display initial state
}

void loop() {
  // Your animation or pattern code goes here
  // For example, to turn all LEDs red:
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red; // Set each LED to red
  }
  FastLED.show(); // Update the LEDs with the new colors

  delay(1000); // Wait for a second
}

// WIP: NOT WORKING YET