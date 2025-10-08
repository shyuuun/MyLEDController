#include <web-server/web-server.h>
#include <defines.h>
#include <led/LED.h>

AsyncWebServer server(80);

String processor(const String& var) {
  Serial.println(var); // See what placeholder the HTML is asking for


  if (var == "DEVICE_NAME") {
    return "My ESP32 Web Thing";
  } else if (var == "LED_STATUS") {
    // Here you would return the actual LED status
    return "OFF"; // or "ON"
  } else if (var == "BRIGHTNESS") {
    // Here you would return the actual brightness level
    return "50"; // Example brightness level
  } else if (var == "LED_COLOR") {
    // Here you would return the actual LED color
    return "255,0,0"; // Example color (red)
  } else { 
    return String();
  }

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

  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request){
    // if (request->hasParam("state")) {
    //   state = request->getParam("state")->value();
    //   if (state == "on") {
    //     turnOn();
    //   } else if (state == "off") {
    //     turnOff();
    //   }
    // }
    if(!request->hasParam("ledState") || !request->hasParam("brightness") || !request->hasParam("ledColor")){ 
      request->send(400, "text/plain", "Missing params");
      return;
    }

    String ledStateStr = request->getParam("ledState")->value();
    String brightnessStr = request->getParam("brightness")->value();
    String ledColorStr = request->getParam("ledColor")->value();

    // Convert brightness string to uint8_t
    uint8_t brightnessVal = (uint8_t)brightnessStr.toInt();

    // Convert ledState string ("1" or "0") to uint8_t
    uint8_t led_state = (uint8_t)ledStateStr.toInt();

    // Parse the hex color string (e.g., "#ff0000")
    long colorValue = strtol(ledColorStr.c_str() + 1, NULL, 16);
    uint8_t r = (colorValue >> 16) & 0xFF;
    uint8_t g = (colorValue >> 8) & 0xFF;
    uint8_t b = colorValue & 0xFF;

    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
    Serial.println(brightnessVal);
    Serial.println(led_state);

    // Call the updateLed function with the parsed values
    updateLed(r, g, b, brightnessVal, led_state);

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

