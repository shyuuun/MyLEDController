#include <web-server/web-server.h>
#include <defines.h>
#include <led/LED.h>
#include "functions/functions.h"
#include "settings/settings.h"

AsyncWebServer server(80);

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

void serverRoutes() {
  // Browser download and caches the static files
  // Next 24 hours: Browser uses cached files from disk
  server.serveStatic("/css/", LittleFS, "/css/").setCacheControl("max-age=86400"); // Cache CSS files for 24 hours
  server.serveStatic("/js/", LittleFS, "/js/").setCacheControl("max-age=86400"); // Cache JS files for 24 hours

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (LittleFS.exists("/index.html")) {
      request->send(LittleFS, "/index.html", "text/html", false, indexProcessor);
    } else {
      Serial.println("Could not find index.html");
      request->send(HTTP_NOT_FOUND, "text/plain", "404: Not Found");
    }
  });

  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (LittleFS.exists("/settings.html")) {
      request->send(LittleFS, "/settings.html", "text/html", false, indexProcessor);
    } else {
      Serial.println("Could not find settings.html");
      request->send(HTTP_NOT_FOUND, "text/plain", "404: Not Found");
    }
  });

  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Validate required query parameters
    if (!request->hasParam("ledState") || !request->hasParam("h") || !request->hasParam("s") || !request->hasParam("l")) {
      request->send(HTTP_BAD_REQUEST, "text/plain", "Missing params");
      return;
    }

    uint8_t ledState = request->getParam("ledState")->value().toInt();
    uint8_t hue = request->getParam("h")->value().toInt();
    uint8_t saturate = request->getParam("s")->value().toInt();
    uint8_t lightness = request->getParam("l")->value().toInt();

    if(request->hasParam("save")) { 
      // values will save to preferences
      saveLedSettings(ledState, hue, saturate, lightness);
      Serial.print("saved to preferences");
    }

    // Validate HSL range to prevent invalid values
    if (hue > 255 || saturate > 255 || lightness > 255) {
      request->send(HTTP_BAD_REQUEST, "text/plain", "Invalid RGB values");
      return;
    }

    updateLed(hue, saturate, lightness, ledState);
    request->send(HTTP_OK, "text/plain", "OK");
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    String path = request->url();
    String contentType = "text/plain";
    bool knownType = false;

    if (path.endsWith(".css")) {
      contentType = "text/css";
      knownType = true;
    } else if (path.endsWith(".js")) {
      contentType = "application/javascript";
      knownType = true;
    }

    if (knownType && LittleFS.exists(path)) {
      request->send(LittleFS, path, contentType);
    } else {
      Serial.printf("NOT_FOUND: %s\n", request->url().c_str());
      request->send(HTTP_NOT_FOUND, "text/plain", "404: Not Found");
    }
  });

}

