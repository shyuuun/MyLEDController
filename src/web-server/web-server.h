#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>

extern AsyncWebServer server;

/**
 * @brief Processes template variables in HTML files.
 * @param var The variable name to process.
 * @return The processed value for the variable.
 */
String processor(const String& var);

/**
 * @brief Configure all server routes and handlers.
 */
void serverRoutes();