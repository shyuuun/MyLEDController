#include "web-server/processors.h"
#include "functions/functions.h"
#include "led/LED.h"
#include "settings/settings.h"

// Ensure ledState is declared as extern if defined elsewhere
extern bool ledState;

String indexProcessor(const String& var) {
  if (var == "DEVICE_NAME") {
    return "ESP32 LED Controller";
  } else if (var == "LED_STATUS") {
    return ledState ? "1" : "0";
  } else if (var == "HUE") {
    return String(normalizeHslForWeb(getHue(), 360));
  } else if (var == "SATURATE") {
    return String(normalizeHslForWeb(getSaturation(), 100));
  } else if (var == "LIGHT") {
    return String(normalizeHslForWeb(getBrightness(), 100));
  } else {
    return String();
  }
}

String settingsProcessor(const String& var) {
  if (var == "DEVICE_NAME") {
    return "ESP32 LED Controller";
  } else if (var == "yo"){ 
    return String();
  } else {
    return String();
  }
}

String wifiProcessor(const String& var) { 
  // TODO: Implement this function 
  return String();
}