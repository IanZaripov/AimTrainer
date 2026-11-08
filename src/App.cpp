#include "App.h"
#include "UITheme.h"
#include "raygui.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

App::App() : game(settings) {
    settings.Load();
    snprintf(sensBuffer, sizeof(sensBuffer), "%.3f", settings.mouse.valorantSens);
    game.Init();
}

void App::UpdateLogic() {
    if (currentScreen == AppScreen::PLAYING) {
        game.Update();
        if (!game.IsTrainingActive()) {
            HandleGameExit(game.GetExitReason());
        }
    }
}

void App::HandleGameExit(GameExitReason reason) {
    switch (reason) {
        case GameExitReason::TimeExpired:
            currentScreen = AppScreen::RESULTS;
            break;
        default:
            currentScreen = AppScreen::ROUTINES;
            break;
    }
}

void App::DrawUI(Font uiFont) {
    ClearBackground(UITheme::BG);

    if (currentScreen == AppScreen::PLAYING) {
        game.Draw(uiFont);
    } else if (currentScreen == AppScreen::RESULTS) {
        DrawResultsScreen(uiFont);
    } else {
        DrawMenuLayout(uiFont);
    }
}

void App::DrawMenuLayout(Font uiFont) {
    DrawTopBar(uiFont);
    switch (currentScreen) {
        case AppScreen::ROUTINES:           DrawRoutinesScreen(uiFont); break;
        case AppScreen::SETTINGS_MOUSE:     DrawMouseSettings(uiFont); break;
        case AppScreen::SETTINGS_CROSSHAIR: DrawCrosshairSettings(uiFont); break;
        case AppScreen::SETTINGS_ARENA:     DrawArenaSettings(uiFont); break;
        default: break;
    }
}

void App::DrawTopBar(Font uiFont) {
    DrawRectangle(0, 0, GetRenderWidth(), (int)UITheme::TopBarHeight, Color{ 20, 25, 30, 255 });
    DrawLine(0, (int)UITheme::TopBarHeight, GetRenderWidth(), (int)UITheme::TopBarHeight, UITheme::ACCENT);

    if (GuiButton({ UITheme::NavButton1X, UITheme::TopBarButtonY, UITheme::TopBarButtonW, UITheme::TopBarButtonH }, "Тренировки")) 
        currentScreen = AppScreen::ROUTINES;
    if (GuiButton({ UITheme::NavButton2X, UITheme::TopBarButtonY, UITheme::TopBarButtonW, UITheme::TopBarButtonH }, "Арена")) 
        currentScreen = AppScreen::SETTINGS_ARENA;
    if (GuiButton({ UITheme::NavButton3X, UITheme::TopBarButtonY, UITheme::TopBarButtonW, UITheme::TopBarButtonH }, "Мышь")) 
        currentScreen = AppScreen::SETTINGS_MOUSE;
    if (GuiButton({ UITheme::NavButton4X, UITheme::TopBarButtonY, UITheme::TopBarButtonW, UITheme::TopBarButtonH }, "Прицел")) 
        currentScreen = AppScreen::SETTINGS_CROSSHAIR;

    const char* title = "AIM TRAINER";
    float titleWidth = MeasureTextEx(uiFont, title, 24, 1).x;
    DrawTextEx(uiFont, title, { (GetRenderWidth() - titleWidth) / 2.0f, 18 }, 24, 1, WHITE);

    if (GuiButton({ UITheme::GetRightButtonX(), UITheme::TopBarButtonY, UITheme::TopBarButtonW, UITheme::TopBarButtonH }, "ВЫХОД")) 
        shouldExit = true;
}

void App::DrawRoutinesScreen(Font uiFont) {
    DrawTextEx(uiFont, "ВЫБЕРИТЕ РУТИНУ:", { 40, 100 }, 20, 1, UITheme::TEXT_DIM);

    float cw = 210.0f;
    float ch = 350.0f;
    float spacing = 20.0f;

    DrawCardStatic(uiFont, { 40, 150, cw, ch });
    DrawCardMoving(uiFont, { 40 + (cw + spacing), 150, cw, ch });
    DrawCardBouncing(uiFont, { 40 + (cw + spacing) * 2, 150, cw, ch });
    DrawCardTimed(uiFont, { 40 + (cw + spacing) * 3, 150, cw, ch });
    DrawCardMulti(uiFont, { 40 + (cw + spacing) * 4, 150, cw, ch });
}

void App::DrawCardStatic(Font font, Rectangle rect) {
    bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);
    UITheme::DrawCardBackground(rect, hovered);

    DrawCircle(rect.x + rect.width/2, rect.y + 120, 40, settings.arena.ballColor);
    DrawTextEx(font, "Статичные", { rect.x + 20, rect.y + 220 }, 20, 1, WHITE);
    DrawTextEx(font, "Появляются после", { rect.x + 15, rect.y + 250 }, 12, 1, UITheme::TEXT_DIM);
    DrawTextEx(font, "уничтожения", { rect.x + 15, rect.y + 270 }, 12, 1, UITheme::TEXT_DIM);

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::STATIC);
    }
}

void App::DrawCardMoving(Font font, Rectangle rect) {
    bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);
    UITheme::DrawCardBackground(rect, hovered);

    DrawCircle(rect.x + rect.width/2, rect.y + 120, 40, settings.arena.ballColor);
    DrawTriangle({rect.x + rect.width/2 + 50, rect.y + 120}, {rect.x + rect.width/2 + 70, rect.y + 110}, {rect.x + rect.width/2 + 70, rect.y + 130}, WHITE);
    DrawTriangle({rect.x + rect.width/2 - 50, rect.y + 120}, {rect.x + rect.width/2 - 70, rect.y + 110}, {rect.x + rect.width/2 - 70, rect.y + 130}, WHITE);
    
    DrawTextEx(font, "Движущаяся", { rect.x + 20, rect.y + 220 }, 20, 1, WHITE);
    DrawTextEx(font, "Летает влево", { rect.x + 15, rect.y + 250 }, 12, 1, UITheme::TEXT_DIM);
    DrawTextEx(font, "и вправо", { rect.x + 15, rect.y + 270 }, 12, 1, UITheme::TEXT_DIM);

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::MOVING);
    }
}

void App::DrawCardBouncing(Font font, Rectangle rect) {
    bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);
    UITheme::DrawCardBackground(rect, hovered);

    DrawCircle(rect.x + rect.width/2, rect.y + 120, 40, settings.arena.ballColor);
    DrawTriangle({rect.x + rect.width/2 + 50, rect.y + 120}, {rect.x + rect.width/2 + 70, rect.y + 110}, {rect.x + rect.width/2 + 70, rect.y + 130}, WHITE);
    DrawTriangle({rect.x + rect.width/2 - 50, rect.y + 120}, {rect.x + rect.width/2 - 70, rect.y + 110}, {rect.x + rect.width/2 - 70, rect.y + 130}, WHITE);
    DrawTriangle({rect.x + rect.width/2, rect.y + 120 - 50}, {rect.x + rect.width/2 - 10, rect.y + 120 - 70}, {rect.x + rect.width/2 + 10, rect.y + 120 - 70}, WHITE);
    DrawTriangle({rect.x + rect.width/2, rect.y + 120 + 50}, {rect.x + rect.width/2 - 10, rect.y + 120 + 70}, {rect.x + rect.width/2 + 10, rect.y + 120 + 70}, WHITE);

    DrawTextEx(font, "Прыгающая", { rect.x + 20, rect.y + 220 }, 20, 1, WHITE);
    DrawTextEx(font, "Отскакивает от", { rect.x + 15, rect.y + 250 }, 12, 1, UITheme::TEXT_DIM);
    DrawTextEx(font, "пола и стен", { rect.x + 15, rect.y + 270 }, 12, 1, UITheme::TEXT_DIM);

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::BOUNCING);
    }
}

void App::DrawCardTimed(Font font, Rectangle rect) {
    bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);
    float diffY = rect.y + 370; 
    const char* diffNames[] = { "Легко", "Сред", "Сложно" };
    bool clickedDiff = false;
    
    for (int i = 0; i < 3; i++) {
        Rectangle btn = { rect.x + 15 + i * 60.0f, diffY, 55, 25 };
        if (CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            settings.arena.timedDifficulty = i;
            settings.Save();
            clickedDiff = true;
        }
    }

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !clickedDiff) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::TIMED);
    }

    UITheme::DrawCardBackground(rect, hovered);
    
    DrawCircle(rect.x + rect.width/2, rect.y + 120, 40, settings.arena.ballColor);
    DrawCircleLines(rect.x + rect.width/2, rect.y + 120, 40, WHITE);
    DrawLineEx({rect.x + rect.width/2, rect.y + 120}, {rect.x + rect.width/2, rect.y + 95}, 3.0f, WHITE);
    
    DrawTextEx(font, "На время", { rect.x + 15, rect.y + 190 }, 20, 1, WHITE);
    
    for (int i = 0; i < 3; i++) {
        Rectangle btn = { rect.x + 15 + i * 60.0f, diffY, 55, 25 };
        bool btnHover = CheckCollisionPointRec(GetMousePosition(), btn);
        DrawRectangleRec(btn, settings.arena.timedDifficulty == i ? UITheme::ACCENT : UITheme::BG);
        DrawRectangleLinesEx(btn, 1.0f, btnHover ? WHITE : UITheme::BORDER);
        float tw = MeasureTextEx(font, diffNames[i], 12, 1).x;
        DrawTextEx(font, diffNames[i], { btn.x + (btn.width - tw)/2, btn.y + 5 }, 12, 1, WHITE);
    }
}

void App::DrawCardMulti(Font font, Rectangle rect) {
    bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);
    UITheme::DrawCardBackground(rect, hovered);

    DrawCircle(rect.x + rect.width/2 - 30, rect.y + 100, 15, settings.arena.ballColor);
    DrawCircle(rect.x + rect.width/2 + 30, rect.y + 100, 15, settings.arena.ballColor);
    DrawCircle(rect.x + rect.width/2, rect.y + 140, 15, settings.arena.ballColor);
    DrawCircle(rect.x + rect.width/2 - 20, rect.y + 180, 15, settings.arena.ballColor);
    DrawCircle(rect.x + rect.width/2 + 20, rect.y + 180, 15, settings.arena.ballColor);

    DrawTextEx(font, "Мульти-цель", { rect.x + 15, rect.y + 220 }, 20, 1, WHITE);
    DrawTextEx(font, "8 шаров одновременно", { rect.x + 15, rect.y + 250 }, 12, 1, UITheme::TEXT_DIM);
    DrawTextEx(font, "(Тренировка спрея)", { rect.x + 15, rect.y + 270 }, 12, 1, UITheme::TEXT_DIM);

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::MULTI_STATIC);
    }
}

void App::DrawSliderBox(Font font, float x, float y, const char* label, float* value, float min, float max, char* buffer, bool* editMode, bool isInt, int precision) {
    DrawTextEx(font, label, { x, y }, 16, 1, UITheme::TEXT);
    GuiSlider({ x, y + 25, 200, 20 }, "", "", value, min, max);
    
    if (!*editMode) {
        if (isInt) snprintf(buffer, 16, "%d", (int)*value);
        else if (precision == 3) snprintf(buffer, 16, "%.3f", *value);
        else snprintf(buffer, 16, "%.2f", *value);
    }

    Rectangle tbRect = { x + 220, y + 25, 80, 30 };
    if (GuiTextBox(tbRect, buffer, 16, *editMode)) {
        *editMode = !*editMode;
        if (!*editMode) {
            float val = atof(buffer);
            if (val >= min && val <= max) *value = val;
        }
    }
}

void App::DrawColorPickerRow(float x, float y, Color* targetColor, const Color* palette, int paletteSize) {
    for (int i = 0; i < paletteSize; i++) {
        Rectangle btn = { x + i * 40.0f, y, 30, 30 };
        DrawRectangleRec(btn, palette[i]);
        bool isSelected = (targetColor->r == palette[i].r && targetColor->g == palette[i].g && targetColor->b == palette[i].b);
        DrawRectangleLinesEx(btn, isSelected ? 2.0f : 1.0f, isSelected ? UITheme::ACCENT : UITheme::BORDER);
        
        if (CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *targetColor = palette[i];
        }
    }
}

void App::DrawMouseSettings(Font uiFont) {
    DrawTextEx(uiFont, "НАСТРОЙКИ МЫШИ", { 40, 90 }, 24, 1, UITheme::ACCENT);
    
    UITheme::DrawTitledGroup(uiFont, { 40, 140, 350, 100 }, "СЕНСА (VALORANT)");
    DrawSliderBox(uiFont, 60, 180, "Чувствительность", &settings.mouse.valorantSens, 0.1f, 8.0f, sensBuffer, &sensEditMode, false, 3);

    static char multBuffer[16] = "3.15";
    static bool multEditMode = false;
    UITheme::DrawTitledGroup(uiFont, { 40, 260, 350, 100 }, "МНОЖИТЕЛЬ (ПОДГОНКА)");
    DrawSliderBox(uiFont, 60, 300, "Множитель", &settings.mouse.sensMultiplier, 0.5f, 5.0f, multBuffer, &multEditMode);

    static float lastSaveTime = 0.0f;
    if (GetTime() - lastSaveTime > 2.0f) { settings.Save(); lastSaveTime = GetTime(); }
}

void App::DrawArenaSettings(Font uiFont) {
    DrawTextEx(uiFont, "НАСТРОЙКИ АРЕНЫ", { 40, 90 }, 24, 1, UITheme::ACCENT);
    
    static char distBuffer[16] = "15";
    static bool distEdit = false;
    UITheme::DrawTitledGroup(uiFont, { 40, 140, 350, 100 }, "ДИСТАНЦИЯ ДО ЦЕЛЕЙ");
    DrawSliderBox(uiFont, 60, 180, "Метры", &settings.arena.distance, 5.0f, 30.0f, distBuffer, &distEdit, true);

    UITheme::DrawTitledGroup(uiFont, { 40, 260, 350, 100 }, "ЦВЕТ ШАРОВ");
    Color colors[] = { { 0, 220, 255, 255 }, WHITE, YELLOW, PINK, ORANGE, RED, GREEN };
    DrawColorPickerRow(60, 300, &settings.arena.ballColor, colors, 7);

    static char sizeBuffer[16] = "0.11";
    static bool sizeEdit = false;
    UITheme::DrawTitledGroup(uiFont, { 40, 380, 350, 100 }, "РАЗМЕР ШАРОВ");
    DrawSliderBox(uiFont, 60, 420, "Радиус (метры)", &settings.arena.targetRadius, 0.02f, 2.0f, sizeBuffer, &sizeEdit, false);

    Rectangle previewBox = { 420, 140, 500, 340 };
    DrawRectangleRounded(previewBox, 0.02f, 4, Color{ 30, 35, 40, 255 });
    DrawRectangleLinesEx(previewBox, 2.0f, UITheme::BORDER);
    DrawLineEx({previewBox.x, previewBox.y + 250}, {previewBox.x + previewBox.width, previewBox.y + 250}, 2.0f, UITheme::BORDER);
    
    float cx = previewBox.x + previewBox.width / 2.0f, cy = previewBox.y + previewBox.height / 2.0f - 30;
    float aspect = (float)GetRenderWidth() / (float)GetRenderHeight();
    float vFovRad = 2.0f * atanf(tanf((settings.fovDegrees * DEG2RAD) / 2.0f) / aspect);
    float pxRadius = (settings.arena.targetRadius / settings.arena.distance) * (GetRenderHeight() / 2.0f) / tanf(vFovRad / 2.0f);
    if (pxRadius < 0.5f) pxRadius = 0.5f; 

    DrawCircle(cx, cy, pxRadius, settings.arena.ballColor);

    const char* infoText = TextFormat("Диаметр: %.1f см (%.0f px)", settings.arena.targetRadius * 200.0f, pxRadius * 2.0f);
    float tw = MeasureTextEx(uiFont, infoText, 18, 1).x;
    DrawTextEx(uiFont, infoText, { previewBox.x + (previewBox.width - tw) / 2.0f, previewBox.y + previewBox.height - 40 }, 18, 1, UITheme::TEXT);
    
    static float lastSaveTime = 0.0f;
    if (GetTime() - lastSaveTime > 2.0f) { settings.Save(); lastSaveTime = GetTime(); }
}

void App::DrawCrosshairSettings(Font uiFont) {
    DrawTextEx(uiFont, "НАСТРОЙКИ ПРИЦЕЛА", { 40, 90 }, 24, 1, UITheme::ACCENT);
    
    UITheme::DrawTitledGroup(uiFont, { 40, 140, 350, 210 }, "ФОРМА");
    static char lenBuffer[16] = "4", thicBuffer[16] = "1", gapBuffer[16] = "0";
    static bool lenEdit = false, thicEdit = false, gapEdit = false;
    DrawSliderBox(uiFont, 60, 180, "Длина линий", &settings.crosshair.length, 0.0f, 20.0f, lenBuffer, &lenEdit, true);
    DrawSliderBox(uiFont, 60, 230, "Толщина", &settings.crosshair.thickness, 1.0f, 10.0f, thicBuffer, &thicEdit, true);
    DrawSliderBox(uiFont, 60, 280, "Отступ (Gap)", &settings.crosshair.gap, 0.0f, 20.0f, gapBuffer, &gapEdit, true);

    UITheme::DrawTitledGroup(uiFont, { 40, 370, 350, 100 }, "ДОПОЛНИТЕЛЬНО");
    GuiCheckBox({ 60, 400, 20, 20 }, "Центральная точка", &settings.crosshair.dot);
    GuiCheckBox({ 60, 430, 20, 20 }, "Обводка (Outline)", &settings.crosshair.outline);

    UITheme::DrawTitledGroup(uiFont, { 40, 490, 350, 90 }, "ЦВЕТ ПРИЦЕЛА");
    Color colors[] = { WHITE, BLACK, YELLOW, PINK, SKYBLUE, ORANGE, RED };
    DrawColorPickerRow(60, 520, &settings.crosshair.color, colors, 7);

    Rectangle previewBox = { 420, 140, 500, 440 };
    DrawRectangleRounded(previewBox, 0.02f, 4, Color{ 30, 35, 40, 255 });
    DrawRectangleLinesEx(previewBox, 2.0f, UITheme::BORDER);
    DrawLineEx({previewBox.x, previewBox.y + 300}, {previewBox.x + previewBox.width, previewBox.y + 300}, 2.0f, UITheme::BORDER);
    
    float cx = previewBox.x + previewBox.width / 2.0f, cy = previewBox.y + previewBox.height / 2.0f - 50;
    Color col = settings.crosshair.color;
    float len = settings.crosshair.length, thic = settings.crosshair.thickness, gap = settings.crosshair.gap;

    if (settings.crosshair.outline) {
        Color out = BLACK; float oT = thic + 2.0f, oL = len + 2.0f;
        DrawRectanglePro({cx, cy - gap - len/2.0f, oT, oL}, {oT/2.0f, oL/2.0f}, 0.0f, out);
        DrawRectanglePro({cx, cy + gap + len/2.0f, oT, oL}, {oT/2.0f, oL/2.0f}, 0.0f, out);
        DrawRectanglePro({cx - gap - len/2.0f, cy, oL, oT}, {oL/2.0f, oT/2.0f}, 0.0f, out);
        DrawRectanglePro({cx + gap + len/2.0f, cy, oL, oT}, {oL/2.0f, oT/2.0f}, 0.0f, out);
    }
    DrawRectanglePro({cx, cy - gap - len/2.0f, thic, len}, {thic/2.0f, len/2.0f}, 0.0f, col);
    DrawRectanglePro({cx, cy + gap + len/2.0f, thic, len}, {thic/2.0f, len/2.0f}, 0.0f, col);
    DrawRectanglePro({cx - gap - len/2.0f, cy, len, thic}, {len/2.0f, thic/2.0f}, 0.0f, col);
    DrawRectanglePro({cx + gap + len/2.0f, cy, len, thic}, {len/2.0f, thic/2.0f}, 0.0f, col);
    if (settings.crosshair.dot) DrawRectanglePro({cx, cy, thic, thic}, {thic/2.0f, thic/2.0f}, 0.0f, col);

    static float lastSaveTime = 0.0f;
    if (GetTime() - lastSaveTime > 2.0f) { settings.Save(); lastSaveTime = GetTime(); }
}

void App::DrawResultsScreen(Font uiFont) {
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), Fade(BLACK, 0.8f));
    
    float pw = 500, ph = 450;
    Rectangle panel = { (GetRenderWidth() - pw) / 2.0f, (GetRenderHeight() - ph) / 2.0f, pw, ph };
    DrawRectangleRounded(panel, 0.05f, 4, UITheme::PANEL);
    DrawRectangleLinesEx(panel, 2.0f, UITheme::ACCENT);

    const char* title = "РЕЗУЛЬТАТЫ";
    float tw = MeasureTextEx(uiFont, title, 32, 1).x;
    DrawTextEx(uiFont, title, { panel.x + (pw - tw) / 2.0f, panel.y + 30 }, 32, 1, UITheme::ACCENT);
    DrawLineEx({panel.x + 20, panel.y + 80}, {panel.x + pw - 20, panel.y + 80}, 1.0f, UITheme::BORDER);

    float textY = panel.y + 110;
    
    DrawTextEx(uiFont, "Время:", { panel.x + 50, textY }, 20, 1, UITheme::TEXT);
    DrawTextEx(uiFont, "60 сек", { panel.x + 300, textY }, 20, 1, WHITE);
    textY += 40;

    DrawTextEx(uiFont, "Сгенерировано шаров:", { panel.x + 50, textY }, 20, 1, UITheme::TEXT);
    DrawTextEx(uiFont, TextFormat("%d", game.GetSpawnedBalls()), { panel.x + 300, textY }, 20, 1, WHITE);
    textY += 40;

    DrawTextEx(uiFont, "Уничтожено:", { panel.x + 50, textY }, 20, 1, UITheme::TEXT);
    DrawTextEx(uiFont, TextFormat("%d", game.GetPoppedCount()), { panel.x + 300, textY }, 20, 1, WHITE);
    textY += 40;

    float accuracy = (game.GetSpawnedBalls() > 0) ? 100.0f * game.GetPoppedCount() / game.GetSpawnedBalls() : 0.0f;
    DrawTextEx(uiFont, "Точность:", { panel.x + 50, textY }, 20, 1, UITheme::TEXT);
    DrawTextEx(uiFont, TextFormat("%.1f%%", accuracy), { panel.x + 300, textY }, 20, 1, WHITE);
    
    if (GuiButton({ panel.x + 50, panel.y + 350, 180, 40 }, "ЗАНОВО")) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::TIMED);
    }
    if (GuiButton({ panel.x + 270, panel.y + 350, 180, 40 }, "В МЕНЮ")) {
        currentScreen = AppScreen::ROUTINES;
    }
}