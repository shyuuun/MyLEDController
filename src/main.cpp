#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include <LittleFS.h>
#include <led/LED.h>
#include "wifi-manager/wifi-manager.h"
#include <web-server/web-server.h>

void setup() {
  Serial.begin(115200);
  setupLED();
  if(!LittleFS.begin()){
    leds[0] = CRGB::Red;
    leds[1] = CRGB::Red;
    FastLED.show(); // Update the LED state
    return;
  }
  createAP(); 
  serverRoutes();
  server.begin(); // Start the server

}

void loop() {

IPAddress IP = WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.println(IP);
  delay(1000);
}
