#pragma once
#include "raylib.h"
#include "Game.h"
#include "Settings.h"

enum class AppScreen { ROUTINES, SETTINGS_MOUSE, SETTINGS_CROSSHAIR, SETTINGS_ARENA, PLAYING, RESULTS };

class App {
public:
    App();
    void Update();
    void Draw(Font uiFont);
    bool ShouldExit() const { return shouldExit; }

private:
    Settings settings;
    Game     game;
    AppScreen currentScreen = AppScreen::ROUTINES;
    bool shouldExit = false;

    char sensBuffer[16] = "0.255";
    bool sensEditMode = false;

    void DrawTopBar(Font uiFont);
    void DrawRoutinesScreen(Font uiFont);
    void DrawMouseSettings(Font uiFont);
    void DrawCrosshairSettings(Font uiFont);
    void DrawArenaSettings(Font uiFont);
    void DrawResultsScreen(Font uiFont); // Новый метод
};