#include <Arduino.h>
#include <string.h>
#include "face_controller.h"

static FcRequest fcRequests[FC_MAX_REQUESTS];

void fcInit()
{
    for (int i = 0; i < FC_MAX_REQUESTS; i++)
    {
        fcRequests[i].active = false;
        fcRequests[i].id = nullptr;
    }
}

bool fcRequest(const char* id, FaceType face, int priority, unsigned long durationMs)
{
    for (int i = 0; i < FC_MAX_REQUESTS; i++)
    {
        if (fcRequests[i].active && fcRequests[i].id != nullptr && strcmp(fcRequests[i].id, id) == 0)
        {
            fcRequests[i].face = face;
            fcRequests[i].priority = priority;
            fcRequests[i].startMs = millis();
            fcRequests[i].durationMs = durationMs;
            return true;
        }
    }

    for (int i = 0; i < FC_MAX_REQUESTS; i++)
    {
        if (!fcRequests[i].active)
        {
            fcRequests[i].id = id;
            fcRequests[i].face = face;
            fcRequests[i].priority = priority;
            fcRequests[i].startMs = millis();
            fcRequests[i].durationMs = durationMs;
            fcRequests[i].active = true;
            return true;
        }
    }

    return false;
}

void fcRelease(const char* id)
{
    for (int i = 0; i < FC_MAX_REQUESTS; i++)
    {
        if (fcRequests[i].active && fcRequests[i].id != nullptr && strcmp(fcRequests[i].id, id) == 0)
        {
            fcRequests[i].active = false;
            return;
        }
    }
}

void fcUpdate()
{
    unsigned long now = millis();

    for (int i = 0; i < FC_MAX_REQUESTS; i++)
    {
        if (fcRequests[i].active && fcRequests[i].durationMs > 0)
        {
            if (now - fcRequests[i].startMs >= fcRequests[i].durationMs)
            {
                fcRequests[i].active = false;
            }
        }
    }

    int bestIdx = -1;
    int bestPriority = -1;

    for (int i = 0; i < FC_MAX_REQUESTS; i++)
    {
        if (fcRequests[i].active)
        {
            if (fcRequests[i].priority > bestPriority)
            {
                bestPriority = fcRequests[i].priority;
                bestIdx = i;
            }
        }
    }

    if (bestIdx >= 0)
    {
        FaceType resolvedFace = fcRequests[bestIdx].face;
        if (resolvedFace != currentFace)
        {
            currentFace = resolvedFace;
            resetFaceAnimationState();
            faceNeedsRedraw = true;
        }
    }
}
