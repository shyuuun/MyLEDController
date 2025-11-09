/**
 * @brief Global flag indicating the current WiFi mode.
 * True = Station mode (connects to existing WiFi)
 * False = Access Point mode (creates its own WiFi network)
 */
extern bool isStationMode;

/**
 * @brief Check if the device is in WiFi Station mode.
 * @return True if in Station mode, false if in AP mode.
 */
bool isWifiStationMode();

/**
 * @brief Converts HSV/HSL values from ESP32 range to web interface range.
 * ESP32 uses 0-255 for HSV values, while the web interface uses different ranges
 * (Hue: 0-360, Saturation: 0-100, Value: 0-100).
 * @param value The value to convert (0-255).
 * @param max The maximum value for the target range (360 for hue, 100 for saturation/value).
 * @return The normalized value in the web interface range.
 */
int normalizeHslForWeb(int value, int max);

/**
 * @brief reboots the device
 */
void rebootMyDevice();
