#include "app_normalizer.h"

static const AppMapping appTable[] = {
  {"net.whatsapp.WhatsApp",      "WhatsApp",   "whatsappIcon"},
  {"com.facebook.Facebook",      "Facebook",   "facebookIcon"},
  {"com.facebook.Messenger",     "Messenger",  "facebook_messengerIcon"},
  {"com.burbn.instagram",        "Instagram",  "instagramIcon"},
  {"com.linkedin.LinkedIn",      "LinkedIn",   "linkedinIcon"},
  {"com.reddit.Reddit",          "Reddit",     "redditIcon"},
  {"com.burbn.threads",          "Threads",    "threadsIcon"},
  {"com.zhiliaoapp.musically",   "TikTok",     "tiktokIcon"},
  {"com.apple.MobileSMS",        "Messages",   "smsIcon"},
  {"com.apple.mobilemail",       "Mail",       "envelopeIcon"},
  {"com.apple.mobilecal",        "Calendar",   "calendarIcon"},
  {"com.apple.Preferences",      "Settings",   "gearIcon"},
};

static constexpr size_t appTableSize = sizeof(appTable) / sizeof(appTable[0]);

const AppMapping* lookupApp(const String& bundleId)
{
  for (size_t i = 0; i < appTableSize; i++)
  {
    if (bundleId == appTable[i].bundleId)
    {
      return &appTable[i];
    }
  }
  return nullptr;
}

String normalizeNotificationCommand(const String& command)
{
  if (!command.startsWith("notification|"))
  {
    return command;
  }

  int p1 = command.indexOf('|');
  int p2 = command.indexOf('|', p1 + 1);
  if (p1 < 0 || p2 < 0) return command;

  String bundleId = command.substring(p1 + 1, p2);
  const AppMapping* mapping = lookupApp(bundleId);

  if (mapping == nullptr)
  {
    int p3 = command.indexOf('|', p2 + 1);
    if (p3 < 0) return command;

    String result = "notification|";
    result += bundleId;
    result += "|otherIcon";
    result += command.substring(p2);
    return result;
  }

  int p3 = command.indexOf('|', p2 + 1);
  if (p3 < 0) return command;

  String result = "notification|";
  result += mapping->displayName;
  result += "|";
  result += mapping->iconName;
  result += command.substring(p2);
  return result;
}
