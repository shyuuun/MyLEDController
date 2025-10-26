#include "functions.h"
#include <math.h>

// Default to Station mode (connects to existing WiFi)
bool isStationMode = true;

bool isWifiStationMode() {
  return isStationMode;
}

int normalizeHslForWeb(int value,int max) { 
  return lround((value / 255.0) * max);
}