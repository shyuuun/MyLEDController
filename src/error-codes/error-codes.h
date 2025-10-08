#ifndef ERROR_CODES_H
#define ERROR_CODES_H

#include <FastLED.h>
#include <led/LED.h>

/**
 * @brief Error codes for system failures.
 * Each error displays a unique pattern on the first few LEDs.
 */
enum ErrorCode {
  ERROR_FILESYSTEM_INIT = 0,  // 2 Red LEDs - LittleFS initialization failed
  ERROR_AP_CREATION = 1,      // 3 Red LEDs - Access Point creation failed
  ERROR_SERVER_INIT = 2,      // 4 Red LEDs - Web server initialization failed
  ERROR_WIFI_CONNECT = 3,     // 5 Red LEDs - WiFi connection failed
  ERROR_FILE_NOT_FOUND = 4    // 2 Yellow LEDs - File not found
};

/**
 * @brief Display an error code using LEDs.
 * @param code The error code to display.
 *
 * This function clears all LEDs and displays a specific pattern
 * based on the error code. The system will halt after displaying
 * the error (return from setup or loop as needed).
 */
void showErrorCode(ErrorCode code);

/**
 * @brief Display a success indicator using LEDs.
 *
 * Shows a brief green flash on the first LED to indicate
 * successful operation completion.
 */
void showSuccess();

/**
 * @brief Display a warning using LEDs.
 * @param ledIndex The LED index to use for the warning (default: 0).
 *
 * Shows a yellow LED to indicate a non-critical warning.
 */
void showWarning(int ledIndex = 0);

#endif
