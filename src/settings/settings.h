#include <Preferences.h>

extern Preferences preferences;

/**
 * @brief Initializes the preferences storage system.
 * Must be called before any other settings functions.
 */
void initSettings();

/**
 * @brief Retrieves the saved LED power state.
 * @return true if LED is on, false if LED is off.
 */
bool getLedState();

/**
 * @brief Saves the LED power state to persistent storage.
 * @param state true to save LED as on, false to save as off.
 */
void setLedState(bool state);

/**
 * @brief Retrieves the saved hue value.
 * @return Hue value (0-255).
 */
uint8_t getHue();

/**
 * @brief Saves the hue value to persistent storage.
 * @param hue Hue value (0-255).
 */
void setHue(uint8_t hue);

/**
 * @brief Retrieves the saved saturation value.
 * @return Saturation value (0-255).
 */
uint8_t getSaturation();

/**
 * @brief Saves the saturation value to persistent storage.
 * @param saturation Saturation value (0-255).
 */
void setSaturation(uint8_t saturation);

/**
 * @brief Retrieves the saved brightness value.
 * @return Brightness value (0-255).
 */
uint8_t getBrightness();

/**
 * @brief Saves the brightness value to persistent storage.
 * @param brightness Brightness value (0-255).
 */
void setBrightness(uint8_t brightness);

/**
 * @brief Saves all LED settings to persistent storage in a single operation.
 * @param state LED power state (true = on, false = off).
 * @param h Hue value (0-255).
 * @param s Saturation value (0-255).
 * @param v Brightness/Value (0-255).
 */
void saveLedSettings(bool state, uint8_t h, uint8_t s, uint8_t v);

/**
 * @brief Clears all saved settings from persistent storage.
 */
void clearAllSettings();