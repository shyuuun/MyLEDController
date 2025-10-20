#include "functions.h"

// Default to Station mode (connects to existing WiFi)
bool isStationMode = true;

bool isWifiStationMode() {
  return isStationMode;
}