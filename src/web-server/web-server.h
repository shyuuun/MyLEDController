#include <AsyncTCP.h>
// NOTE: Template is confused when there is '%' in the html. 
// NOTE: https://github.com/me-no-dev/ESPAsyncWebServer/pull/366
// NOTE: Replaced the template from '%' to '&'
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>

extern AsyncWebServer server;

/**
 * @brief Processes template variables in index.HTML
 * @param var The variable name to process.
 * @return The processed value for the variable.
 */
String indexProcessor(const String& var);

/**
 * @brief Configure all server routes and handlers.
 */
void serverRoutes();