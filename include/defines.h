#define SerialEmulation Serial
#include <Arduino.h>

// HTTP response codes (most commonly used in the project. prefer to add more as needed)
const int HTTP_OK = 200;
const int HTTP_NOT_FOUND = 404;
const int HTTP_BAD_REQUEST = 400;
const int HTTP_INTERNAL_SERVER_ERROR = 500;
const int HTTP_UNAUTHORIZED = 401;
const int HTTP_FORBIDDEN = 403;

// Default startup color (Orangy)
const uint8_t DEFAULT_HUE = 28;
const uint8_t DEFAULT_SATURATION = 153;
const uint8_t DEFAULT_BRIGHTNESS = 128;
const boolean DEFAULT_LED_STATE = true;

extern char* mDNSName;
extern char* DEFAULT_DEVICE_NAME;



