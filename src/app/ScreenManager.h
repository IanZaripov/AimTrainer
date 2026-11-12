#pragma once
#include <memory>
#include "raylib.h"
#include "Settings.h"
#include "TrainingSession.h"
#include "IScreen.h"

enum class ScreenID { 
    ROUTINES, 
    SETTINGS_MOUSE, 
    SETTINGS_CROSSHAIR, 
    SETTINGS_ARENA, 
    PLAYING, 
    RESULTS 
};

class ScreenManager {
public:
    ScreenManager();
    void UpdateLogic();
    void DrawUI(Font uiFont);
    bool ShouldExit() const { return shouldExit; }

    // Navigation
    void GoTo(ScreenID id);

    // Accessors
    Settings& GetSettings() { return settings; }
    TrainingSession& GetSession() { return session; }

private:
    Settings settings;
    TrainingSession session;
    std::unique_ptr<IScreen> currentScreen;
    
    ScreenID currentScreenID;
    ScreenID pendingScreenID;
    bool hasPendingScreen = false;

    bool shouldExit = false;

    void ApplyPendingScreenChange();
    void DrawTopBar(Font uiFont);
};