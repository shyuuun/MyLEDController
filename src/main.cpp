#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include <LittleFS.h>
#include <led/LED.h>
#include <led/effects.h>
#include <ESPmDNS.h>
#include <defines.h>
#include "wifi-manager/wifi-manager.h"
#include <web-server/web-server.h>
#include <error-codes/error-codes.h>
#include <functions/functions.h>
#include "settings/settings.h"

// Status LED pin
#define STATUS_LED_PIN 15

char* mDNSName = (char*)"myled";
char* DEFAULT_DEVICE_NAME = (char*)"LEDController32";

void setup() {
  Serial.begin(115200);

  initSettings();

  if (isStationMode) {
    setupWifi();
  } else {
    createAP();
  }

  if(!MDNS.begin(mDNSName)) {
    Serial.println("Error setting up MDNS responder!");
    while(1) {
      delay(1000);
    }
  }

  setupLED();

  if (!LittleFS.begin()) {
    showErrorCode(ERROR_FILESYSTEM_INIT);
    return;
  }

  setupRoutes();
  server.begin();

  showSuccess();
}

void loop() {
  static unsigned long lastPrint = 0;
  static unsigned long lastLedUpdate = 0;

  // Update status LED based on WiFi status
  if (millis() - lastLedUpdate > 1000) {
    if (isStationMode) {
      if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(STATUS_LED_PIN, HIGH);  // Solid on when connected
      } else {
        // Blink if disconnected
        digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));
      }
    } else {
      // In AP mode, blink slowly if clients connected, solid if no clients
      if (WiFi.softAPgetStationNum() > 0) {
        digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));
      } else {
        digitalWrite(STATUS_LED_PIN, HIGH);
      }
    }
    lastLedUpdate = millis();
  }

  // Periodic status update to avoid flooding serial output
  if (millis() - lastPrint > 10000) {
    if (isStationMode) {
      Serial.println("\n=== Station Mode Status ===");
      Serial.print("WiFi Status: ");
      switch (WiFi.status()) {
        case WL_CONNECTED:
          Serial.println("Connected");
          Serial.print("SSID: ");
          Serial.println(WiFi.SSID());
          Serial.print("IP Address: ");
          Serial.println(WiFi.localIP());
          Serial.print("Signal Strength: ");
          Serial.print(WiFi.RSSI());
          Serial.println(" dBm");
          Serial.print("Gateway: ");
          Serial.println(WiFi.gatewayIP());
          Serial.print("DNS: ");
          Serial.println(WiFi.dnsIP());
          break;
        case WL_NO_SSID_AVAIL:
          Serial.println("SSID not available");
          break;
        case WL_CONNECT_FAILED:
          Serial.println("Connection failed");
          break;
        case WL_CONNECTION_LOST:
          Serial.println("Connection lost");
          break;
        case WL_DISCONNECTED:
          Serial.println("Disconnected");
          break;
        case WL_IDLE_STATUS:
          Serial.println("Idle");
          break;
        default:
          Serial.print("Unknown (");
          Serial.print(WiFi.status());
          Serial.println(")");
      }
    } else {
      Serial.println("\n=== Access Point Mode Status ===");
      Serial.print("AP SSID: ");
      Serial.println(WiFi.softAPSSID());
      Serial.print("AP IP: ");
      Serial.println(WiFi.softAPIP());
      Serial.print("Connected Clients: ");
      Serial.println(WiFi.softAPgetStationNum());
      Serial.print("AP MAC: ");
      Serial.println(WiFi.softAPmacAddress());
    }
    Serial.print("Free Heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");
    Serial.print("Uptime: ");
    Serial.print(millis() / 1000);
    Serial.println(" seconds");
    Serial.println("===========================\n");
    
    lastPrint = millis();
  }

  // Prevent watchdog timer resets on ESP32
  delay(10);

  // testing
  // fadeInOut();

  // runningLed();
}
