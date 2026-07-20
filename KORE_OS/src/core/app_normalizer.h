#ifndef APP_NORMALIZER_H
#define APP_NORMALIZER_H

#include <Arduino.h>

struct AppMapping {
  const char* bundleId;
  const char* displayName;
  const char* iconName;
};

const AppMapping* lookupApp(const String& bundleId);
String normalizeNotificationCommand(const String& command);

#endif
