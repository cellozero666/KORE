#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

// --- Definição de Modos ---
enum DisplayMode { DISPLAY_NOTIFICATION, DISPLAY_WEATHER, DISPLAY_SPOTIFY, DISPLAY_EMOTION };

// --- Contratos (Forward Declarations) ---
void onEnterNotification(); void updateNotification(); void renderNotification();
void onEnterWeather();      void updateWeather();      void renderWeather();
void onEnterSpotify();      void updateSpotify();      void renderSpotify();
void onEnterEmotion();      void updateEmotion();      void renderEmotion();

// --- Estados Globais Externos ---
extern bool notificationActive;
extern bool spotifyActive;
extern bool weatherActive;
extern DisplayMode currentMode;
extern bool modeChanged;
extern bool notificationEmotionActive;

// --- Implementação (Inline) ---

inline void updateDisplayState() {
    DisplayMode nextMode;
    
    // Lógica de prioridade: Notificação > Weather > Spotify > Emotion
    if (notificationActive) nextMode = DISPLAY_NOTIFICATION;
    else if (notificationEmotionActive) nextMode = DISPLAY_EMOTION;
    else if (weatherActive) nextMode = DISPLAY_WEATHER;
    else if (spotifyActive) nextMode = DISPLAY_SPOTIFY;
    else nextMode = DISPLAY_EMOTION;

    // Detecção de transição
    if (nextMode != currentMode) {
        currentMode = nextMode;
        modeChanged = true;
    }
}

inline void handleDisplayTransition() {
    if (modeChanged) {
        switch (currentMode) {
            case DISPLAY_NOTIFICATION: onEnterNotification(); break;
            case DISPLAY_WEATHER:      onEnterWeather();      break;
            case DISPLAY_SPOTIFY:      onEnterSpotify();      break;
            case DISPLAY_EMOTION:      onEnterEmotion();      break;
        }
        modeChanged = false;
    }
}

inline void updateActiveModule() {
    updateNotification();
    switch (currentMode) {
        case DISPLAY_NOTIFICATION: updateNotification(); break;
        case DISPLAY_WEATHER:      updateWeather();      break;
        case DISPLAY_SPOTIFY:      updateSpotify();      break;
        case DISPLAY_EMOTION:      updateEmotion();      break;
    }
}

inline void renderCurrentDisplay() {
    switch (currentMode) {
        case DISPLAY_NOTIFICATION: renderNotification(); break;
        case DISPLAY_WEATHER:      renderWeather();      break;
        case DISPLAY_SPOTIFY:      renderSpotify();      break;
        case DISPLAY_EMOTION:      renderEmotion();      break;
    }
}

#endif
