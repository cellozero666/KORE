#ifndef FACE_CONTROLLER_H
#define FACE_CONTROLLER_H

#include "mood_manager.h"

#define FC_MAX_REQUESTS 8

struct FcRequest {
    const char* id;
    FaceType face;
    int priority;
    unsigned long startMs;
    unsigned long durationMs;
    bool active;
};

void fcInit();
bool fcRequest(const char* id, FaceType face, int priority, unsigned long durationMs);
void fcRelease(const char* id);
void fcUpdate();

#endif
