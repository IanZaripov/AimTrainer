#pragma once
#include "raylib.h"
#include "Game.h"
#include "Settings.h"

enum class AppScreen { ROUTINES, SETTINGS_MOUSE, SETTINGS_CROSSHAIR, SETTINGS_ARENA, PLAYING, RESULTS };

class App {
public:
    App();
    void UpdateLogic();
    void DrawUI(Font uiFont);
    bool ShouldExit() const { return shouldExit; }

private:
    Settings settings;
    Game     game;
    AppScreen currentScreen = AppScreen::ROUTINES;
    bool shouldExit = false;

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

    void DrawCardStatic(Font font, Rectangle rect);
    void DrawCardMoving(Font font, Rectangle rect);
    void DrawCardBouncing(Font font, Rectangle rect);
    void DrawCardTimed(Font font, Rectangle rect);
    void DrawCardMulti(Font font, Rectangle rect);
    
    void DrawSliderBox(Font font, float x, float y, const char* label, float* value, float min, float max, char* buffer, bool* editMode, bool isInt = false, int precision = 2);
    void DrawColorPickerRow(float x, float y, Color* targetColor, const Color* palette, int paletteSize);
};