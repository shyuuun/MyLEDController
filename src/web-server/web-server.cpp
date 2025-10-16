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
    return ledState ? "1" : "0"; // or "ON"
  } else if (var == "LED_COLOR_RGB") {
    // Return the actual LED color in R,G,B format for display
    return String(color.r) + "," + String(color.g) + "," + String(color.b);
  } else if ( var == "RED") { 
    return String(color.r);
  }
  else if ( var == "BLUE") { 
    return String(color.b);
  }
else if ( var == "GREEN") { 
    return String(color.g);
  }

  
  else { 
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

    // Validate if there is query params
    if(!request->hasParam("ledState") || !request->hasParam("r") || !request->hasParam("g") || !request->hasParam("b")){ 
      request->send(400, "text/plain", "Missing params");
      return;
    }

    // TODO: Validate if the rgb is below 0 and exceeds to 255 range


    uint8_t ledState = request->getParam("ledState")->value().toInt();
    uint8_t red =  request->getParam("r")->value().toInt();
    uint8_t blue =  request->getParam("b")->value().toInt();
    uint8_t green = request->getParam("g")->value().toInt();


    Serial.println(red);
    Serial.println(blue);
    Serial.println(green);
    Serial.println(ledState);

    // Call the updateLed function with the parsed values
    updateLed(red, green, blue, ledState);

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

