#ifndef EMOTION_MANAGER_H
#define EMOTION_MANAGER_H

#include <Arduino.h>
#include "mood_manager.h"

struct EmotionRule {
    FaceType face;
    uint16_t duration;
    uint8_t priority;
    uint8_t keywordCount;
    const char* const* keywords;
};

FaceType detectEmotion(String text);
bool loadEmotionRules();
FaceType emotionNameToFace(String name);

#endif
