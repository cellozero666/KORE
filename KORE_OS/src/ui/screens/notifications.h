#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <Arduino.h>
#include "../../config/display_context.h"
#include "../../managers/mood_manager.h"

// --------------------------------------------------
// STATE
// --------------------------------------------------

#define MAX_NOTIFICATIONS 10

struct NotificationItem
{
  String app;
  String title;
  String body;
};

extern NotificationItem notificationQueue[MAX_NOTIFICATIONS];

extern int notificationHead;
extern int notificationTail;

extern bool notificationActive;
extern bool notificationWasDrawn;

extern FaceType notificationEmotion;
extern bool notificationEmotionActive;
extern unsigned long notificationEmotionStarted;

extern String notificationApp;
extern String notificationTitle;
extern String notificationBody;

extern unsigned long notificationStarted;

// --------------------------------------------------
// WRAPPERS (Interface)
// --------------------------------------------------

void onEnterNotification();
void updateNotification();
void renderNotification();

// --------------------------------------------------
// ICONS
// --------------------------------------------------

const unsigned char* getNotificationIcon(const String& app);

// --------------------------------------------------
// QUEUE
// --------------------------------------------------

bool notificationQueueEmpty();
bool notificationQueueFull();
void enqueueNotification(const String& app, const String& title, const String& body);
bool dequeueNotification();

// --------------------------------------------------
// PARSE COMMAND
// --------------------------------------------------

void parseNotificationCommand(String command);

// --------------------------------------------------
// DRAW SCREEN
// --------------------------------------------------

void drawNotificationScreen(Adafruit_ST7789 &tft, uint16_t color);

#endif
