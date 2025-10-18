#include "functions.h"

// Global variable - default to AP mode (false)
bool isStationMode = true;

bool isWifiStationMode() { 
  return isStationMode;
}