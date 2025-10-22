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
extern boolean ledState;
extern CHSV color;

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

/**
 * @brief Set the color in HSL format for all LEDs.
 * @param hue (0-255).
 * @param saturation (0-255).
 * @param lightness (0-255).
 */
void setColor(uint8_t hue, uint8_t saturation, uint8_t lightness);


/**
 * @brief Update LED state and color in one operation.
 * @param h Hue (0-255)
 * @param s Saturation (0-255)
 * @param l Lightness (0-255) 
 * @param led_state LED power state (1 = on, 0 = off).
 */
void updateLed(uint8_t h, uint8_t s, uint8_t l, uint8_t led_state);
