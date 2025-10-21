#include <web-server/web-server.h>
#include <defines.h>
#include <led/LED.h>

AsyncWebServer server(80);

// TODO: if there is another processor function, consider renaming this one to avoid confusion
String processor(const String& var) {
  if (var == "DEVICE_NAME") {
    return "My ESP32 Web Thing";
  } else if (var == "LED_STATUS") {
    return ledState ? "1" : "0";
  } else if (var == "LED_COLOR_RGB") {
    return String(color.r) + "," + String(color.g) + "," + String(color.b);
  } else if (var == "RED") {
    return String(color.r);
  } else if (var == "BLUE") {
    return String(color.b);
  } else if (var == "GREEN") {
    return String(color.g);
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
      request->send(LittleFS, "/index.html", "text/html", false, processor);
    } else {
      Serial.println("Could not find index.html");
      request->send(HTTP_NOT_FOUND, "text/plain", "404: Not Found");
    }
  });

  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (LittleFS.exists("/settings.html")) {
      request->send(LittleFS, "/settings.html", "text/html", false, processor);
    } else {
      Serial.println("Could not find settings.html");
      request->send(HTTP_NOT_FOUND, "text/plain", "404: Not Found");
    }
  });

  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Validate required query parameters
    if (!request->hasParam("ledState") || !request->hasParam("r") || !request->hasParam("g") || !request->hasParam("b")) {
      request->send(HTTP_BAD_REQUEST, "text/plain", "Missing params");
      return;
    }

    uint8_t ledState = request->getParam("ledState")->value().toInt();
    uint8_t red = request->getParam("r")->value().toInt();
    uint8_t blue = request->getParam("b")->value().toInt();
    uint8_t green = request->getParam("g")->value().toInt();

    // Validate RGB range to prevent invalid values
    if (red > 255 || green > 255 || blue > 255) {
      request->send(HTTP_BAD_REQUEST, "text/plain", "Invalid RGB values");
      return;
    }

    updateLed(red, green, blue, ledState);
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

