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


extern CRGB leds[NUM_LEDS];

/**
 * @brief Initialize the LED strip with default settings.
 */
void setupLED();

/**
 * @brief Turn on all LEDs with a preset color.
 */
void turnOn();

/**
 * @brief Turn off all LEDs.
 */
void turnOff();

void setColor(uint8_t r, uint8_t g, uint8_t b);
void setBrightness(uint8_t brightness);
void updateLed(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness, uint8_t led_state);
