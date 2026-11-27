#pragma once
#include <memory>
#include "raylib.h"
#include "Settings.h"
#include "TrainingSession.h"
#include "GameMode.h"
#include "IScreen.h"

enum class ScreenID { 
    ROUTINES, 
    SETTINGS_MOUSE, 
    SETTINGS_CROSSHAIR, 
    SETTINGS_ARENA,
    SETTINGS_AUDIO,
    SETTINGS_LANGUAGE, 
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

    GameCategory GetRoutineCategory() const { return routineCategory; }
    void SetRoutineCategory(GameCategory c) { routineCategory = c; }
private:
    Settings settings;
    TrainingSession session;
    std::unique_ptr<IScreen> currentScreen;
    
    ScreenID currentScreenID;
    ScreenID pendingScreenID;
    GameCategory routineCategory = GameCategory::NORMAL;
    bool hasPendingScreen = false;
    bool shouldExit = false;

    void ApplyPendingScreenChange();
    void DrawTopBar(Font uiFont);
};