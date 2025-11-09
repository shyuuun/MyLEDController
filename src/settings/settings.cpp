#include "settings.h"
#include "defines.h"

Preferences preferences;
const char* NAMESPACE = "led_settings";

void initSettings() {
  // Open the preferences namespace in read-only mode initially
  preferences.begin(NAMESPACE, true);
  
  // Check if this is first-time initialization
  bool isInitialized = preferences.isKey("nvsInit");
  
  if (!isInitialized) {
    // First-time run: close RO mode and reopen in RW mode
    preferences.end();
    preferences.begin(NAMESPACE, false);
    
    // Set factory defaults
    preferences.putBool("led_state", DEFAULT_LED_STATE);
    preferences.putUChar("hue", DEFAULT_HUE);
    preferences.putUChar("saturation", DEFAULT_SATURATION);
    preferences.putUChar("brightness", DEFAULT_BRIGHTNESS);
    preferences.putBool("nvsInit", true);  // Mark as initialized
    
    // Close RW mode and reopen in RO mode
    preferences.end();
    preferences.begin(NAMESPACE, true);
  }
  
  // Close after initialization - will reopen as needed
  preferences.end();
}

bool getLedState() {
  preferences.begin(NAMESPACE, true);
  bool state = preferences.getBool("led_state", DEFAULT_LED_STATE);
  preferences.end();
  return state;
}

void setLedState(bool state) {
  preferences.begin(NAMESPACE, false);  // Open in RW mode
  preferences.putBool("led_state", state);
  preferences.end();  // Close and commit
}

uint8_t getHue() {
  preferences.begin(NAMESPACE, true);
  uint8_t hue = preferences.getUChar("hue", DEFAULT_HUE);
  preferences.end();
  return hue;
}

void setHue(uint8_t hue) {
  preferences.begin(NAMESPACE, false);  // Open in RW mode
  preferences.putUChar("hue", hue);
  preferences.end();  // Close and commit
}

uint8_t getSaturation() {
  preferences.begin(NAMESPACE, true);
  uint8_t saturation = preferences.getUChar("saturation", DEFAULT_SATURATION);
  preferences.end();
  return saturation;
}

void setSaturation(uint8_t saturation) {
  preferences.begin(NAMESPACE, false);  // Open in RW mode
  preferences.putUChar("saturation", saturation);
  preferences.end();  // Close and commit
}

uint8_t getBrightness() {
  preferences.begin(NAMESPACE, true);
  uint8_t brightness = preferences.getUChar("brightness", DEFAULT_BRIGHTNESS);
  preferences.end();
  return brightness;
}

void setBrightness(uint8_t brightness) {
  preferences.begin(NAMESPACE, false);  // Open in RW mode
  preferences.putUChar("brightness", brightness);
  preferences.end();  // Close and commit
}

void saveLedSettings(bool state, uint8_t h, uint8_t s, uint8_t v) {
  Serial.println("Saving settings...");
  preferences.begin(NAMESPACE, false);  // Open in RW mode (not RO!)
  preferences.putBool("led_state", state);
  preferences.putUChar("hue", h);
  preferences.putUChar("saturation", s);
  preferences.putUChar("brightness", v);
  preferences.end();  // Close and commit to flash
  Serial.println("Settings saved");
}

void clearAllSettings() {
  preferences.begin(NAMESPACE, false);  // Open in RW mode
  preferences.clear();
  preferences.end();  // Close and commit
}

void setDeviceName(char* deviceName) { 
  preferences.begin(NAMESPACE, false);
  preferences.putString("device_name", deviceName);
  preferences.end();
}

String getDeviceName(){ 
  preferences.begin(NAMESPACE, true);
  String deviceName = preferences.getString("device_name");
  preferences.end();
  return deviceName;
}