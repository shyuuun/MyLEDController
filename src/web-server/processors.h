#include <ESPAsyncWebServer.h>

/**
 * @brief Processes template variables in index.HTML
 * @param var The variable name to process.
 * @return The processed value for the variable.
 */
String indexProcessor(const String& var);

/**
 * @brief Processes template variables in settings.HTML
 * @param var The variable name to process.
 * @return The processed value for the variable.
 */
String settingsProcessor(const String& var);

/**
 * @brief Processes template variables in wifi.HTML
 * @param var The variable name to process.
 * @return The processed value for the variable.
 */
String wifiProcessor(const String& var);