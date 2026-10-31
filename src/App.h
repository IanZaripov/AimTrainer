#pragma once
#include "raylib.h"
#include "Game.h"
#include "Settings.h"

enum class AppScreen { ROUTINES, SETTINGS, PLAYING };

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
    void DrawSettingsScreen(Font uiFont);
};