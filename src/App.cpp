#include "App.h"
#include "raygui.h"
#include <cstdio>
#include <cstdlib>

App::App() : game(settings) {
    settings.Load();
    snprintf(sensBuffer, sizeof(sensBuffer), "%.3f", settings.valorantSens);
    game.Init();
}

void App::Update() {
    if (currentScreen == AppScreen::PLAYING) {
        game.Update();
        if (!game.IsTrainingActive()) {
            currentScreen = AppScreen::ROUTINES;
        }
    }
}

void App::Draw(Font uiFont) {
    // Темно-синеватый фон, если смотреть за пределы арены
    ClearBackground(Color{ 20, 25, 35, 255 });

    if (currentScreen == AppScreen::PLAYING) {
        game.Draw(uiFont);
    } else {
        DrawTopBar(uiFont);
        if (currentScreen == AppScreen::ROUTINES) DrawRoutinesScreen(uiFont);
        else if (currentScreen == AppScreen::SETTINGS) DrawSettingsScreen(uiFont);
    }
}

void App::DrawTopBar(Font uiFont) {
    DrawRectangle(0, 0, GetScreenWidth(), 60, Color{ 25, 25, 30, 255 });
    DrawLine(0, 60, GetScreenWidth(), 60, Color{ 255, 70, 85, 255 });

    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x252530ff); 
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xd0d0d0ff);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0xff4655ff); 
    
    if (GuiButton({ 20, 15, 120, 30 }, "Тренировки")) currentScreen = AppScreen::ROUTINES;
    if (GuiButton({ 150, 15, 120, 30 }, "Настройки")) currentScreen = AppScreen::SETTINGS;

    const char* title = "AIM TRAINER";
    float titleWidth = MeasureTextEx(uiFont, title, 24, 1).x;
    DrawTextEx(uiFont, title, { (GetScreenWidth() - titleWidth) / 2.0f, 18 }, 24, 1, WHITE);
}

void App::DrawRoutinesScreen(Font uiFont) {
    DrawTextEx(uiFont, "ВЫБЕРИТЕ РУТИНУ:", { 40, 100 }, 20, 1, GRAY);

    Rectangle card = { 40, 150, 250, 350 };
    bool hovered = CheckCollisionPointRec(GetMousePosition(), card);
    
    Color cardColor = hovered ? Color{ 60, 60, 70, 255 } : Color{ 35, 35, 45, 255 };
    DrawRectangleRec(card, cardColor);
    DrawRectangleLinesEx(card, hovered ? 3.0f : 1.0f, hovered ? Color{ 255, 70, 85, 255 } : Color{ 80, 80, 90, 255 });

    DrawCircle(40 + 125, 150 + 150, 40, Color{ 220, 60, 60, 255 });
    
    DrawTextEx(uiFont, "3D Арена", { 60, 150 + 260 }, 22, 1, WHITE);
    DrawTextEx(uiFont, "Статичные цели", { 60, 150 + 290 }, 16, 1, GRAY);

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining();
    }
}

void App::DrawSettingsScreen(Font uiFont) {
    DrawTextEx(uiFont, "НАСТРОЙКИ МЫШИ", { 40, 100 }, 24, 1, Color{ 255, 70, 85, 255 });

    DrawTextEx(uiFont, "Сенса (Valorant 0.1 - 8.0):", { 40, 160 }, 18, 1, LIGHTGRAY);
    
    GuiSlider({ 40, 200, 300, 30 }, "0.1", "8.0", &settings.valorantSens, 0.1f, 8.0f);
    
    DrawTextEx(uiFont, "Точное значение:", { 40, 250 }, 18, 1, LIGHTGRAY);
    
    if (!sensEditMode) {
        snprintf(sensBuffer, sizeof(sensBuffer), "%.3f", settings.valorantSens);
    }

    Rectangle textBoxRec = { 40, 280, 100, 30 };
    if (GuiTextBox(textBoxRec, sensBuffer, 16, sensEditMode)) {
        sensEditMode = !sensEditMode;
        if (!sensEditMode) {
            float val = atof(sensBuffer);
            if (val >= 0.1f && val <= 8.0f) {
                settings.valorantSens = val;
                settings.Save();
            }
        }
    }

    DrawTextEx(uiFont, "Сенса адаптирована под 3D и FOV 103.", { 40, 330 }, 16, 1, DARKGRAY);
}