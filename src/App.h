#pragma once
#include "raylib.h"
#include "Game.h"
#include "Settings.h"

enum class AppScreen { ROUTINES, SETTINGS_MOUSE, SETTINGS_CROSSHAIR, PLAYING };

class App {
public:
    App();
    void Update();
    void Draw(Font uiFont);

private:
    Settings settings;
    Game     game;
    AppScreen currentScreen = AppScreen::ROUTINES;

    char sensBuffer[16] = "0.255";
    bool sensEditMode = false;

    void DrawTopBar(Font uiFont);
    void DrawRoutinesScreen(Font uiFont);
    void DrawMouseSettings(Font uiFont);
    void DrawCrosshairSettings(Font uiFont);
};