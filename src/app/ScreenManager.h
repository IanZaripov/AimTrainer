#pragma once
#include <vector>
#include <memory>
#include "raylib.h"
#include "Settings.h"
#include "TrainingSession.h"
#include "TrainingCard.h"

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

private:
    Settings settings;
    TrainingSession session;
    ScreenID currentScreen = ScreenID::ROUTINES;
    bool shouldExit = false;
    const char* title = "AIM TRAINER";

    std::vector<std::unique_ptr<TrainingCard>> trainingCards;

    char sensBuffer[16] = "0.255";
    bool sensEditMode = false;

    void HandleGameExit(GameExitReason reason);
    void DrawMenuLayout(Font uiFont);
    void DrawTopBar(Font uiFont);

    void DrawRoutinesScreen(Font uiFont);
    void DrawMouseSettings(Font uiFont);
    void DrawCrosshairSettings(Font uiFont);
    void DrawArenaSettings(Font uiFont);
    void DrawResultsScreen(Font uiFont);

    void DrawSliderBox(Font font, float x, float y, const char* label, float* value, float min, float max, char* buffer, bool* editMode, bool isInt = false, int precision = 2);
    void DrawColorPickerRow(float x, float y, Color* targetColor, const Color* palette, int paletteSize);
};