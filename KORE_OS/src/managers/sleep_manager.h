#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

#include <Arduino.h>

#include "clock_manager.h"
#include "mood_manager.h"
#include "display_manager.h"

// --------------------------------------------------
// CONFIG
// --------------------------------------------------

#define IDLE_SLEEP_TIME 900000UL

// --------------------------------------------------
// EXTERNALS
// --------------------------------------------------

extern unsigned long lastActivity;

// --------------------------------------------------
// UPDATE
// --------------------------------------------------

void updateSleepManager()
{
    FaceType newDefault = FACE_HAPPY;

    // Sleep por horário (tem prioridade)
    bool nightSleep =
        clockState.hour >= 22 ||
        clockState.hour < 7;

    // Sleep por inatividade (somente durante o dia)
    bool idleSleep =
        !nightSleep &&
        (millis() - lastActivity >= IDLE_SLEEP_TIME);

    if (nightSleep)
    {
        newDefault = FACE_SLEEP;
    }
    else if (idleSleep)
    {
        newDefault = FACE_SLEEP;
    }

    // Nada mudou
    if (newDefault == defaultFace)
    {
        return;
    }

    defaultFace = newDefault;

    // Só redesenha se estiver mostrando a tela de emoção
    if (currentMode == DISPLAY_EMOTION)
    {
        setFace(defaultFace);
    }
}

#endif