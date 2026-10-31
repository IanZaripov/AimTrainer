#pragma once
#include "raylib.h"
#include "Game.h"
#include "Settings.h"

enum class AppScreen {
    ROUTINES, // Выбор тренировки
    SETTINGS, // Настройки
    PLAYING   // В процессе игры
};

class App {
public:
    App();
    void Update();
    void Draw();

private:
    Settings settings;
    Game     game;
    AppScreen currentScreen = AppScreen::ROUTINES;

    void DrawTopBar();
    void DrawRoutinesScreen();
    void DrawSettingsScreen();
};