#include <web-server/web-server.h>

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
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if (LittleFS.exists("/index.html")) {
        request->send(LittleFS, "/index.html", "text/html", false, processor);
    } else {
        Serial.println("Could not find index.html");
        request->send(404, "text/plain", "404: Not Found");
    }
  });

}

