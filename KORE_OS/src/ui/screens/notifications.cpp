#include "notifications.h"
#include <Arduino.h>
#include "../../config/display_context.h"
#include "../../managers/mood_manager.h"
#include "../../managers/emotion_manager.h"
#include "../../managers/face_controller.h"
#include "../assets/notification_icons.h"

// --------------------------------------------------
// STATE DEFINITIONS
// --------------------------------------------------

NotificationItem notificationQueue[MAX_NOTIFICATIONS];

int notificationHead = 0;
int notificationTail = 0;

bool notificationActive = false;
bool notificationWasDrawn = false;

FaceType notificationEmotion = FACE_HAPPY;
bool notificationEmotionActive = false;
unsigned long notificationEmotionStarted = 0;

String notificationApp = "";
String notificationTitle = "";
String notificationBody = "";

unsigned long notificationStarted = 0;

// --------------------------------------------------
// WRAPPERS (Interface)
// --------------------------------------------------

void onEnterNotification()
{
  tft.fillScreen(ST77XX_BLACK);
  notificationWasDrawn = false;
}

void updateNotification()
{
  if (notificationActive &&
    millis() - notificationStarted >= 8000)
  {
    notificationActive = false;
    notificationWasDrawn = false;

    fcRequest("notif_emotion", notificationEmotion, 150, 5000);

    notificationEmotionActive = true;
    notificationEmotionStarted = millis();
  }

  if (notificationEmotionActive &&
    millis() - notificationEmotionStarted >= 5000)
  {
    notificationEmotionActive = false;
    dequeueNotification();
  }
}

void renderNotification()
{
  if (notificationActive && !notificationWasDrawn)
  {
    drawNotificationScreen(tft, KORE_CYAN);
    notificationWasDrawn = true;
  }
}

// --------------------------------------------------
// ICONS
// --------------------------------------------------

const unsigned char* getNotificationIcon(
  const String& app
)
{
  String appName = app;
  appName.toLowerCase();

  if (
    appName.indexOf("whatsapp") >= 0
  )
  {
    return (const unsigned char*)
      pgm_read_ptr(
        &icons[ICON_WHATSAPP]
      );
  }

  if (
    appName.indexOf("calendar") >= 0 ||
    appName.indexOf("calendário") >= 0
  )
  {
    return (const unsigned char*)
      pgm_read_ptr(
        &icons[ICON_CALENDAR]
      );
  }

  if (
    appName.indexOf("mail") >= 0 ||
    appName.indexOf("email") >= 0
  )
  {
    return (const unsigned char*)
      pgm_read_ptr(
        &icons[ICON_ENVELOPE]
      );
  }

  if (
    appName.indexOf("messages") >= 0 ||
    appName.indexOf("mensagens") >= 0 ||
    appName.indexOf("sms") >= 0
  )
  {
    return (const unsigned char*)
      pgm_read_ptr(
        &icons[ICON_SMS]
      );
  }

  if (
    appName.indexOf("settings") >= 0 ||
    appName.indexOf("system") >= 0
  )
  {
    return (const unsigned char*)
      pgm_read_ptr(
        &icons[ICON_GEAR]
      );
  }

  return (const unsigned char*)
    pgm_read_ptr(
      &icons[ICON_OTHER]
    );
}

// --------------------------------------------------
// QUEUE
// --------------------------------------------------

bool notificationQueueEmpty()
{
  return notificationHead == notificationTail;
}

bool notificationQueueFull()
{
  return (
    (notificationTail + 1) %
    MAX_NOTIFICATIONS
  ) == notificationHead;
}

void enqueueNotification(
  const String& app,
  const String& title,
  const String& body
)
{
  if (notificationQueueFull())
  {
    return;
  }

  notificationQueue[
    notificationTail
  ] = {
    app,
    title,
    body
  };

  notificationTail =
    (notificationTail + 1) %
    MAX_NOTIFICATIONS;
}

bool dequeueNotification()
{
  if (notificationQueueEmpty())
  {
    return false;
  }

  notificationApp =
    notificationQueue[
      notificationHead
    ].app;

  notificationTitle =
    notificationQueue[
      notificationHead
    ].title;

  notificationBody =
    notificationQueue[
      notificationHead
    ].body;

  notificationHead =
    (notificationHead + 1) %
    MAX_NOTIFICATIONS;

  notificationStarted =
    millis();

  notificationActive = true;

  return true;
}

// --------------------------------------------------
// PARSE COMMAND
// --------------------------------------------------

void parseNotificationCommand(
  String command
)
{
  int p1 =
    command.indexOf('|');

  int p2 =
    command.indexOf(
      '|',
      p1 + 1
    );

  int p3 =
    command.indexOf(
      '|',
      p2 + 1
    );

  if (
    p1 < 0 ||
    p2 < 0 ||
    p3 < 0
  )
  {
    return;
  }

  String app =
    command.substring(
      p1 + 1,
      p2
    );

  String title =
    command.substring(
      p2 + 1,
      p3
    );

  String body =
    command.substring(
      p3 + 1
    );

  notificationEmotion =
    detectEmotion(
      title + " " + body
    );

  enqueueNotification(
    app,
    title,
    body
  );

  if (!notificationActive)
  {
    dequeueNotification();
  }
}

// --------------------------------------------------
// DRAW SCREEN
// --------------------------------------------------

void drawNotificationScreen(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  tft.fillScreen(
    ST77XX_BLACK
  );

  tft.drawRoundRect(
    10,
    10,
    300,
    220,
    10,
    color
  );

  u8g2.setForegroundColor(
    color
  );

  // ÍCONE

  const unsigned char* icon =
    getNotificationIcon(
      notificationApp
    );

  tft.drawBitmap(
    120,
    20,
    icon,
    80,
    80,
    color
  );

  // APP

  u8g2.setFont(
    u8g2_font_helvB14_tf
  );

  int16_t appWidth =
    u8g2.getUTF8Width(
      notificationApp.c_str()
    );

  u8g2.drawUTF8(
    (SCREEN_WIDTH - appWidth) / 2,
    125,
    notificationApp.c_str()
  );

  // TÍTULO

  String title =
    notificationTitle;

  if (
    title.length() > 18
  )
  {
    title =
      title.substring(
        0,
        18
      );
  }

  u8g2.setFont(
    u8g2_font_helvB18_tf
  );

  u8g2.drawUTF8(
    20,
    155,
    title.c_str()
  );

  // MENSAGEM

  String body =
    notificationBody;

  if (
    body.length() > 48
  )
  {
    body =
      body.substring(
        0,
        48
      );
  }

  u8g2.setFont(
    u8g2_font_helvB14_tf
  );

  // Divide a mensagem em duas linhas apenas se necessário
  String line1 = body;
  String line2 = "";

  if (body.length() > 24)
  {
    int split = body.lastIndexOf(' ', 24);
    if (split == -1) split = 24;

    line1 = body.substring(0, split);
    line2 = body.substring(split + 1);
  }

  u8g2.drawUTF8(
    20,
    190,
    line1.c_str()
  );

  if (line2.length() > 0)
  {
    u8g2.drawUTF8(
      20,
      215,
      line2.c_str()
    );
  }
}
