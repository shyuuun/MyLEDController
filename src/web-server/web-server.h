#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>

extern AsyncWebServer server;

String processor(const String& var);  

void serverRoutes();