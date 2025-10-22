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


int normalizeHslForWeb(int value, int max);

