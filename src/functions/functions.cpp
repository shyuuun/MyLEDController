#include "functions.h"
#include <math.h>
#include <Esp.h>

// Default to Station mode (connects to existing WiFi)
bool isStationMode = false;

int normalizeHslForWeb(int value,int max) { 
  return lround((value / 255.0) * max);
}

void rebootMyDevice() {
  ESP.restart();
}