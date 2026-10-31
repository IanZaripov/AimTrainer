#include "App.h"
#include "raygui.h"
#include <cstdio>
#include <cstdlib>

App::App() : game(settings) {
    settings.Load();
    snprintf(sensBuffer, sizeof(sensBuffer), "%.3f", settings.mouse.valorantSens);
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
    ClearBackground(Color{ 200, 205, 210, 255 });

    if (currentScreen == AppScreen::PLAYING) {
        game.Draw(uiFont);
    } else {
        DrawTopBar(uiFont);
        if (currentScreen == AppScreen::ROUTINES) DrawRoutinesScreen(uiFont);
        else if (currentScreen == AppScreen::SETTINGS_MOUSE) DrawMouseSettings(uiFont);
        else if (currentScreen == AppScreen::SETTINGS_CROSSHAIR) DrawCrosshairSettings(uiFont);
    }
}

void App::DrawTopBar(Font uiFont) {
    DrawRectangle(0, 0, GetScreenWidth(), 60, Color{ 30, 35, 40, 255 });
    DrawLine(0, 60, GetScreenWidth(), 60, Color{ 255, 70, 85, 255 });

    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x252530ff); 
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xd0d0d0ff);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0xff4655ff); 
    
    if (GuiButton({ 20, 15, 120, 30 }, "Тренировки")) currentScreen = AppScreen::ROUTINES;
    if (GuiButton({ 150, 15, 120, 30 }, "Мышь")) currentScreen = AppScreen::SETTINGS_MOUSE;
    if (GuiButton({ 280, 15, 120, 30 }, "Прицел")) currentScreen = AppScreen::SETTINGS_CROSSHAIR;

    const char* title = "AIM TRAINER";
    float titleWidth = MeasureTextEx(uiFont, title, 24, 1).x;
    DrawTextEx(uiFont, title, { (GetScreenWidth() - titleWidth) / 2.0f, 18 }, 24, 1, WHITE);
}

void App::DrawRoutinesScreen(Font uiFont) {
    DrawTextEx(uiFont, "ВЫБЕРИТЕ РУТИНУ:", { 40, 100 }, 20, 1, DARKGRAY);

    Rectangle card = { 40, 150, 250, 350 };
    bool hovered = CheckCollisionPointRec(GetMousePosition(), card);
    
    Color cardColor = hovered ? Color{ 240, 240, 240, 255 } : Color{ 220, 220, 220, 255 };
    DrawRectangleRec(card, cardColor);
    DrawRectangleLinesEx(card, hovered ? 3.0f : 1.0f, hovered ? Color{ 0, 150, 200, 255 } : GRAY);

    DrawCircle(40 + 125, 150 + 150, 40, Color{ 0, 220, 255, 255 });
    
    DrawTextEx(uiFont, "3D Арена", { 60, 150 + 260 }, 22, 1, BLACK);
    DrawTextEx(uiFont, "Статичные цели", { 60, 150 + 290 }, 16, 1, DARKGRAY);

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining();
    }
}

void App::DrawMouseSettings(Font uiFont) {
    DrawTextEx(uiFont, "НАСТРОЙКИ МЫШИ", { 40, 100 }, 24, 1, Color{ 200, 50, 60, 255 });

    DrawTextEx(uiFont, "Сенса (Valorant):", { 40, 160 }, 18, 1, DARKGRAY);
    GuiSlider({ 40, 200, 300, 30 }, "0.1", "8.0", &settings.mouse.valorantSens, 0.1f, 8.0f);
    
    DrawTextEx(uiFont, "Множитель (подгонка):", { 40, 250 }, 18, 1, DARKGRAY);
    GuiSlider({ 40, 290, 300, 30 }, "0.5", "5.0", &settings.mouse.sensMultiplier, 0.5f, 5.0f);

    DrawTextEx(uiFont, "Точное значение сенсы:", { 40, 350 }, 18, 1, DARKGRAY);
    if (!sensEditMode) {
        snprintf(sensBuffer, sizeof(sensBuffer), "%.3f", settings.mouse.valorantSens);
    }
    Rectangle textBoxRec = { 40, 380, 100, 30 };
    if (GuiTextBox(textBoxRec, sensBuffer, 16, sensEditMode)) {
        sensEditMode = !sensEditMode;
        if (!sensEditMode) {
            float val = atof(sensBuffer);
            if (val >= 0.1f && val <= 8.0f) {
                settings.mouse.valorantSens = val;
                settings.Save();
            }
        }
    }
}

void App::DrawCrosshairSettings(Font uiFont) {
    DrawTextEx(uiFont, "НАСТРОЙКА ПРИЦЕЛА", { 40, 100 }, 24, 1, Color{ 200, 50, 60, 255 });

    DrawTextEx(uiFont, "Длина:", { 40, 160 }, 18, 1, DARKGRAY);
    GuiSlider({ 40, 185, 200, 25 }, "0", "20", &settings.crosshair.length, 0.0f, 20.0f);

    DrawTextEx(uiFont, "Толщина:", { 260, 160 }, 18, 1, DARKGRAY);
    GuiSlider({ 260, 185, 200, 25 }, "1", "10", &settings.crosshair.thickness, 1.0f, 10.0f);

    DrawTextEx(uiFont, "Отступ (Gap):", { 40, 230 }, 18, 1, DARKGRAY);
    GuiSlider({ 40, 255, 200, 25 }, "0", "20", &settings.crosshair.gap, 0.0f, 20.0f);

    GuiCheckBox({ 40, 310, 20, 20 }, "Обводка (Outline)", &settings.crosshair.outline);
    GuiCheckBox({ 40, 340, 20, 20 }, "Точка в центре", &settings.crosshair.dot);
    GuiCheckBox({ 40, 370, 20, 20 }, "Хитмаркер при попадании", &settings.crosshair.hitmarker);

    DrawTextEx(uiFont, "Цвет:", { 40, 410 }, 18, 1, DARKGRAY);
    GuiColorPicker({ 40, 440, 150, 150 }, nullptr, &settings.crosshair.color);

    static float lastSaveTime = 0.0f;
    if (GetTime() - lastSaveTime > 2.0f) { 
        settings.Save();
        lastSaveTime = GetTime();
    }

    // Превью
    DrawTextEx(uiFont, "Превью:", { 400, 160 }, 18, 1, DARKGRAY);
    float cx = 450, cy = 300;
    Color col = settings.crosshair.color;
    float len = settings.crosshair.length;
    float thic = settings.crosshair.thickness;
    float gap = settings.crosshair.gap;

    if (settings.crosshair.outline) {
        Color out = BLACK;
        float outThic = thic + 2.0f;
        DrawRectangle(cx - outThic/2, cy - gap - len - 1, outThic, len + 2, out);
        DrawRectangle(cx - outThic/2, cy + gap - 1, outThic, len + 2, out);
        DrawRectangle(cx - gap - len - 1, cy - outThic/2, len + 2, outThic, out);
        DrawRectangle(cx + gap - 1, cy - outThic/2, len + 2, outThic, out);
    }
    DrawRectangle(cx - thic/2, cy - gap - len, thic, len, col);
    DrawRectangle(cx - thic/2, cy + gap, thic, len, col);
    DrawRectangle(cx - gap - len, cy - thic/2, len, thic, col);
    DrawRectangle(cx + gap, cy - thic/2, len, thic, col);
    if (settings.crosshair.dot) DrawRectangle(cx - thic/2, cy - thic/2, thic, thic, col);
}