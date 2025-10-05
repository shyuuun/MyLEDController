#include <FastLED.h>

// Header for LED.cpp

// GPIO PIN for the LED
#define LED_PIN     3  

// Optional if your project uses a matrix of LEDs
// Define the dimensions of the LED matrix MATRIX_WIDTH x MATRIX_HEIGHT
#define MATRIX_WIDTH  5
#define MATRIX_HEIGHT 5

#define NUM_LEDS 10

#define COLOR_ORDER GRB

#define LED_TYPE WS2812B

// Define the default brightness of the LEDs (0 to 255)
#define DEFAULT_BRIGHTNESS 50

extern CRGB leds[NUM_LEDS];

void setupLED();

void turnOn();

void turnOff();
