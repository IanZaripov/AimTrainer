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
    // Темный фон в стиле Valorant
    ClearBackground(Color{ 18, 22, 28, 255 });

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
    DrawRectangle(0, 0, GetScreenWidth(), 60, Color{ 25, 30, 35, 255 });
    DrawLine(0, 60, GetScreenWidth(), 60, Color{ 255, 70, 85, 255 });

    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    // Стилизация кнопок raygui (темные с рамкой)
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x1E2328FF); 
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x3A424AFF);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xD0D0D0FF);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0xFF4655FF); 
    
    if (GuiButton({ 20, 15, 120, 30 }, "Тренировки")) currentScreen = AppScreen::ROUTINES;
    if (GuiButton({ 150, 15, 120, 30 }, "Мышь")) currentScreen = AppScreen::SETTINGS_MOUSE;
    if (GuiButton({ 280, 15, 120, 30 }, "Прицел")) currentScreen = AppScreen::SETTINGS_CROSSHAIR;

    const char* title = "AIM TRAINER";
    float titleWidth = MeasureTextEx(uiFont, title, 24, 1).x;
    DrawTextEx(uiFont, title, { (GetScreenWidth() - titleWidth) / 2.0f, 18 }, 24, 1, WHITE);
}

void App::DrawRoutinesScreen(Font uiFont) {
    DrawTextEx(uiFont, "ВЫБЕРИТЕ РУТИНУ:", { 40, 100 }, 20, 1, LIGHTGRAY);

    Rectangle card = { 40, 150, 250, 350 };
    bool hovered = CheckCollisionPointRec(GetMousePosition(), card);
    
    DrawRectangleRec(card, hovered ? Color{ 35, 45, 55, 255 } : Color{ 25, 30, 35, 255 });
    DrawRectangleLinesEx(card, hovered ? 3.0f : 1.0f, hovered ? Color{ 0, 220, 255, 255 } : Color{ 50, 60, 70, 255 });

    DrawCircle(40 + 125, 150 + 150, 40, Color{ 0, 220, 255, 255 });
    
    DrawTextEx(uiFont, "3D Арена", { 60, 150 + 260 }, 22, 1, WHITE);
    DrawTextEx(uiFont, "Статичные цели", { 60, 150 + 290 }, 16, 1, GRAY);

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining();
    }
}

void App::DrawMouseSettings(Font uiFont) {
    DrawTextEx(uiFont, "НАСТРОЙКИ МЫШИ", { 40, 100 }, 24, 1, Color{ 255, 70, 85, 255 });

    DrawTextEx(uiFont, "Сенса (Valorant):", { 40, 160 }, 18, 1, LIGHTGRAY);
    GuiSlider({ 40, 200, 300, 30 }, "0.1", "8.0", &settings.mouse.valorantSens, 0.1f, 8.0f);
    
    DrawTextEx(uiFont, "Множитель:", { 40, 250 }, 18, 1, LIGHTGRAY);
    GuiSlider({ 40, 290, 300, 30 }, "0.5", "5.0", &settings.mouse.sensMultiplier, 0.5f, 5.0f);

    DrawTextEx(uiFont, "Точное значение:", { 40, 350 }, 18, 1, LIGHTGRAY);
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
    DrawTextEx(uiFont, "НАСТРОЙКИ ПРИЦЕЛА", { 40, 90 }, 24, 1, Color{ 255, 70, 85, 255 });

    // --- ЛЕВАЯ ПАНЕЛЬ (НАСТРОЙКИ) ---
    int px = 40;
    int py = 140;

    // Линии
    DrawTextEx(uiFont, "ЛИНИИ", { (float)px, (float)py }, 18, 1, Color{ 0, 220, 255, 255 });
    py += 30;
    GuiSlider({ (float)px, (float)py, 150, 20 }, "0", "10", &settings.crosshair.thickness, 1.0f, 10.0f);
    DrawTextEx(uiFont, "Толщина", { (float)px + 160, (float)py }, 14, 1, LIGHTGRAY);
    py += 30;
    GuiSlider({ (float)px, (float)py, 150, 20 }, "0", "20", &settings.crosshair.length, 0.0f, 20.0f);
    DrawTextEx(uiFont, "Длина", { (float)px + 160, (float)py }, 14, 1, LIGHTGRAY);
    py += 30;
    GuiSlider({ (float)px, (float)py, 150, 20 }, "0", "20", &settings.crosshair.gap, 0.0f, 20.0f);
    DrawTextEx(uiFont, "Отступ", { (float)px + 160, (float)py }, 14, 1, LIGHTGRAY);
    py += 40;

    // Точка и Обводка
    DrawTextEx(uiFont, "ДОПОЛНИТЕЛЬНО", { (float)px, (float)py }, 18, 1, Color{ 0, 220, 255, 255 });
    py += 30;
    GuiCheckBox({ (float)px, (float)py, 20, 20 }, "Центральная точка", &settings.crosshair.dot);
    py += 30;
    GuiCheckBox({ (float)px, (float)py, 20, 20 }, "Обводка (Outline)", &settings.crosshair.outline);
    py += 30;
    GuiCheckBox({ (float)px, (float)py, 20, 20 }, "Хитмаркер", &settings.crosshair.hitmarker);
    py += 40;

    // Цвет (RGB)
    DrawTextEx(uiFont, "ЦВЕТ", { (float)px, (float)py }, 18, 1, Color{ 0, 220, 255, 255 });
    py += 30;
    
    int r = settings.crosshair.color.r, g = settings.crosshair.color.g, b = settings.crosshair.color.b;
    GuiSlider({ (float)px, (float)py, 150, 15 }, "R", "", (float*)&r, 0.0f, 255.0f); // Костыль raygui для int
    py += 20;
    GuiSlider({ (float)px, (float)py, 150, 15 }, "G", "", (float*)&g, 0.0f, 255.0f);
    py += 20;
    GuiSlider({ (float)px, (float)py, 150, 15 }, "B", "", (float*)&b, 0.0f, 255.0f);
    
    // Обновляем цвет, если ползунки сдвинули
    settings.crosshair.color = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };

    // Автосохранение
    static float lastSaveTime = 0.0f;
    if (GetTime() - lastSaveTime > 2.0f) { 
        settings.Save();
        lastSaveTime = GetTime();
    }

    // --- ПРАВАЯ ПАНЕЛЬ (ПРЕВЬЮ) ---
    Rectangle previewBox = { 350, 140, 500, 300 };
    // Фон "стены"
    DrawRectangleRec(previewBox, Color{ 150, 150, 150, 255 });
    DrawRectangleLinesEx(previewBox, 2.0f, Color{ 50, 60, 70, 255 });
    
    // Отрисовка прицела по центру превью
    float cx = previewBox.x + previewBox.width / 2.0f;
    float cy = previewBox.y + previewBox.height / 2.0f;
    
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
    
    if (settings.crosshair.dot) {
        DrawRectangle(cx - thic/2, cy - thic/2, thic, thic, col);
    }
}