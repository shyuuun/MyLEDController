#include <web-server/web-server.h>
#include <led/LED.h>

AsyncWebServer server(80);

String processor(const String& var) {
  Serial.println(var); // See what placeholder the HTML is asking for

  if (var == "DEVICE_NAME") {
    return "My ESP32 Web Thing";
  }

  // Return an empty string or the original variable if not found
  return String();
}

void serverRoutes() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (LittleFS.exists("/index.html")) {
      request->send(LittleFS, "/index.html", "text/html", false, processor);
    } else {
      Serial.println("Could not find index.html");
      request->send(404, "text/plain", "404: Not Found");
    }
  });

  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request) {
    String state;
    if (request->hasParam("state")) {
      state = request->getParam("state")->value();
      if (state == "on") {
        turnOn();
      } else if (state == "off") {
        turnOff();
      }
    }
    request->send(200, "text/plain", "OK");
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
      request->send(404, "text/plain", "404: Not Found");
    }
  });

}

