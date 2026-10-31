#include "App.h"
#include "raygui.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

const Color COL_BG        = { 18, 22, 28, 255 };
const Color COL_PANEL     = { 25, 30, 35, 255 };
const Color COL_BORDER    = { 50, 60, 70, 255 };
const Color COL_ACCENT    = { 255, 70, 85, 255 };
const Color COL_TEXT      = { 220, 220, 220, 255 };
const Color COL_TEXT_DIM  = { 150, 150, 150, 255 };

App::App() : game(settings) {
    settings.Load();
    snprintf(sensBuffer, sizeof(sensBuffer), "%.3f", settings.mouse.valorantSens);
    game.Init();
}

void App::Update() {
    if (currentScreen == AppScreen::PLAYING) {
        game.Update();
        if (!game.IsTrainingActive()) {
            if (game.GetCurrentMode() == GameMode::TIMED && game.GetSessionTime() >= 60.0f) {
                currentScreen = AppScreen::RESULTS;
            } else {
                currentScreen = AppScreen::ROUTINES;
            }
        }
    }
}

void DrawPanel(Font font, Rectangle rect, const char* title) {
    DrawRectangleRounded(rect, 0.05f, 4, COL_PANEL);
    DrawRectangleLinesEx(rect, 1.0f, COL_BORDER);
    DrawTextEx(font, title, { rect.x + 15, rect.y + 10 }, 14, 1, COL_ACCENT);
    DrawLine((int)rect.x + 15, (int)rect.y + 30, (int)(rect.x + rect.width - 15), (int)rect.y + 30, COL_BORDER);
}

void App::Draw(Font uiFont) {
    ClearBackground(COL_BG);

    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(COL_TEXT));
    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt(COL_BORDER));
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(COL_PANEL));
    GuiSetStyle(CHECKBOX, BASE_COLOR_NORMAL, ColorToInt(COL_PANEL));
    GuiSetStyle(CHECKBOX, BORDER_COLOR_NORMAL, ColorToInt(COL_BORDER));
    GuiSetStyle(CHECKBOX, TEXT_COLOR_NORMAL, ColorToInt(COL_TEXT));
    GuiSetStyle(CHECKBOX, BASE_COLOR_PRESSED, ColorToInt(COL_ACCENT));
    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, ColorToInt(WHITE));
    GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, ColorToInt(COL_BORDER));
    GuiSetStyle(SLIDER, BASE_COLOR_PRESSED, ColorToInt(COL_ACCENT));
    GuiSetStyle(VALUEBOX, BASE_COLOR_NORMAL, ColorToInt(BLACK));
    GuiSetStyle(VALUEBOX, BORDER_COLOR_NORMAL, ColorToInt(WHITE));
    GuiSetStyle(TEXTBOX, BASE_COLOR_NORMAL, ColorToInt(COL_BG));
    GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, ColorToInt(COL_BORDER));

    if (currentScreen == AppScreen::PLAYING) {
        game.Draw(uiFont);
    } else if (currentScreen == AppScreen::RESULTS) {
        DrawResultsScreen(uiFont);
    } else {
        DrawTopBar(uiFont);
        if (currentScreen == AppScreen::ROUTINES) DrawRoutinesScreen(uiFont);
        else if (currentScreen == AppScreen::SETTINGS_MOUSE) DrawMouseSettings(uiFont);
        else if (currentScreen == AppScreen::SETTINGS_CROSSHAIR) DrawCrosshairSettings(uiFont);
        else if (currentScreen == AppScreen::SETTINGS_ARENA) DrawArenaSettings(uiFont);
    }
}

void App::DrawTopBar(Font uiFont) {
    DrawRectangle(0, 0, GetScreenWidth(), 60, Color{ 20, 25, 30, 255 });
    DrawLine(0, 60, GetScreenWidth(), 60, COL_ACCENT);

    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(COL_BG)); 
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(COL_BORDER));
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(COL_ACCENT)); 
    
    if (GuiButton({ 20, 15, 120, 30 }, "Тренировки")) currentScreen = AppScreen::ROUTINES;
    if (GuiButton({ 150, 15, 120, 30 }, "Арена")) currentScreen = AppScreen::SETTINGS_ARENA;
    if (GuiButton({ 280, 15, 120, 30 }, "Мышь")) currentScreen = AppScreen::SETTINGS_MOUSE;
    if (GuiButton({ 410, 15, 120, 30 }, "Прицел")) currentScreen = AppScreen::SETTINGS_CROSSHAIR;

    const char* title = "AIM TRAINER";
    float titleWidth = MeasureTextEx(uiFont, title, 24, 1).x;
    DrawTextEx(uiFont, title, { (GetScreenWidth() - titleWidth) / 2.0f, 18 }, 24, 1, WHITE);

    if (GuiButton({ (float)GetScreenWidth() - 140, 15, 120, 30 }, "ВЫХОД")) shouldExit = true;
}

void App::DrawRoutinesScreen(Font uiFont) {
    DrawTextEx(uiFont, "ВЫБЕРИТЕ РУТИНУ:", { 40, 100 }, 20, 1, COL_TEXT_DIM);

    float cw = 240.0f;
    float ch = 350.0f; // Уменьшили высоту карточек, чтобы влезли кнопки сложности

    // --- КАРТОЧКА 1: СТАТИЧНЫЕ ---
    Rectangle card1 = { 40, 150, cw, ch };
    bool hover1 = CheckCollisionPointRec(GetMousePosition(), card1);
    if (hover1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::STATIC);
    }
    DrawRectangleRec(card1, hover1 ? Color{ 30, 35, 45, 255 } : COL_PANEL);
    DrawRectangleLinesEx(card1, hover1 ? 2.0f : 1.0f, hover1 ? COL_ACCENT : COL_BORDER);
    DrawCircle(40 + cw/2, 150 + 120, 40, settings.arena.ballColor);
    DrawTextEx(uiFont, "Статичные цели", { card1.x + 20, 150 + 220 }, 22, 1, WHITE);
    DrawTextEx(uiFont, "Появляются после", { card1.x + 20, 150 + 250 }, 14, 1, COL_TEXT_DIM);
    DrawTextEx(uiFont, "уничтожения", { card1.x + 20, 150 + 270 }, 14, 1, COL_TEXT_DIM);

    // --- КАРТОЧКА 2: ДВИЖУЩАЯСЯ ---
    Rectangle card2 = { 40 + cw + 30, 150, cw, ch };
    bool hover2 = CheckCollisionPointRec(GetMousePosition(), card2);
    if (hover2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::MOVING);
    }
    DrawRectangleRec(card2, hover2 ? Color{ 30, 35, 45, 255 } : COL_PANEL);
    DrawRectangleLinesEx(card2, hover2 ? 2.0f : 1.0f, hover2 ? COL_ACCENT : COL_BORDER);
    DrawCircle(card2.x + cw/2, 150 + 120, 40, settings.arena.ballColor);
    DrawTriangle({card2.x + cw/2 + 50, 150 + 120}, {card2.x + cw/2 + 70, 150 + 110}, {card2.x + cw/2 + 70, 150 + 130}, WHITE);
    DrawTriangle({card2.x + cw/2 - 50, 150 + 120}, {card2.x + cw/2 - 70, 150 + 110}, {card2.x + cw/2 - 70, 150 + 130}, WHITE);
    DrawTextEx(uiFont, "Движущаяся цель", { card2.x + 20, 150 + 220 }, 22, 1, WHITE);
    DrawTextEx(uiFont, "Один шар, летающий", { card2.x + 20, 150 + 250 }, 14, 1, COL_TEXT_DIM);
    DrawTextEx(uiFont, "влево и вправо", { card2.x + 20, 150 + 270 }, 14, 1, COL_TEXT_DIM);

    // --- КАРТОЧКА 3: ПРЫГАЮЩАЯ ---
    Rectangle card3 = { 40 + (cw + 30) * 2, 150, cw, ch };
    bool hover3 = CheckCollisionPointRec(GetMousePosition(), card3);
    if (hover3 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::BOUNCING);
    }
    DrawRectangleRec(card3, hover3 ? Color{ 30, 35, 45, 255 } : COL_PANEL);
    DrawRectangleLinesEx(card3, hover3 ? 2.0f : 1.0f, hover3 ? COL_ACCENT : COL_BORDER);
    DrawCircle(card3.x + cw/2, 150 + 120, 40, settings.arena.ballColor);
    DrawTriangle({card3.x + cw/2 + 50, 150 + 120}, {card3.x + cw/2 + 70, 150 + 110}, {card3.x + cw/2 + 70, 150 + 130}, WHITE);
    DrawTriangle({card3.x + cw/2 - 50, 150 + 120}, {card3.x + cw/2 - 70, 150 + 110}, {card3.x + cw/2 - 70, 150 + 130}, WHITE);
    DrawTriangle({card3.x + cw/2, 150 + 120 - 50}, {card3.x + cw/2 - 10, 150 + 120 - 70}, {card3.x + cw/2 + 10, 150 + 120 - 70}, WHITE);
    DrawTriangle({card3.x + cw/2, 150 + 120 + 50}, {card3.x + cw/2 - 10, 150 + 120 + 70}, {card3.x + cw/2 + 10, 150 + 120 + 70}, WHITE);
    DrawTextEx(uiFont, "Прыгающая цель", { card3.x + 20, 150 + 220 }, 22, 1, WHITE);
    DrawTextEx(uiFont, "Отскакивает от пола", { card3.x + 20, 150 + 250 }, 14, 1, COL_TEXT_DIM);
    DrawTextEx(uiFont, "и стен", { card3.x + 20, 150 + 270 }, 14, 1, COL_TEXT_DIM);

    // --- КАРТОЧКА 4: НА ВРЕМЯ ---
    Rectangle card4 = { 40 + (cw + 30) * 3, 150, cw, ch };
    bool hover4 = CheckCollisionPointRec(GetMousePosition(), card4);
    
    // Кнопки сложности ВЫНЕСЕНЫ ПОД карточку, чтобы не мешать клику
    float diffY = 520; 
    const char* diffNames[] = { "Легко", "Сред", "Сложно" };
    bool clickedDiff = false;
    
    for (int i = 0; i < 3; i++) {
        Rectangle btn = { card4.x + 20 + i * 65.0f, diffY, 60, 25 };
        if (CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            settings.arena.timedDifficulty = i;
            settings.Save();
            clickedDiff = true;
        }
    }

    if (hover4 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !clickedDiff) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::TIMED);
    }

    DrawRectangleRec(card4, hover4 ? Color{ 30, 35, 45, 255 } : COL_PANEL);
    DrawRectangleLinesEx(card4, hover4 ? 2.0f : 1.0f, hover4 ? COL_ACCENT : COL_BORDER);
    
    DrawCircle(card4.x + cw/2, 150 + 120, 40, settings.arena.ballColor);
    DrawCircleLines(card4.x + cw/2, 150 + 120, 40, WHITE);
    DrawLineEx({card4.x + cw/2, 150 + 120}, {card4.x + cw/2, 150 + 95}, 3.0f, WHITE);
    
    DrawTextEx(uiFont, "На время", { card4.x + 20, 150 + 190 }, 22, 1, WHITE);
    
    // Отрисовка кнопок сложности
    for (int i = 0; i < 3; i++) {
        Rectangle btn = { card4.x + 20 + i * 65.0f, diffY, 60, 25 };
        bool btnHover = CheckCollisionPointRec(GetMousePosition(), btn);
        
        DrawRectangleRec(btn, settings.arena.timedDifficulty == i ? COL_ACCENT : COL_BG);
        DrawRectangleLinesEx(btn, 1.0f, btnHover ? WHITE : COL_BORDER);
        
        float tw = MeasureTextEx(uiFont, diffNames[i], 14, 1).x;
        DrawTextEx(uiFont, diffNames[i], { btn.x + (btn.width - tw)/2, btn.y + 5 }, 14, 1, WHITE);
    }
}

void DrawSliderBox(Font font, float x, float y, const char* label, float* value, float min, float max, char* buffer, bool* editMode, bool isInt = false, int precision = 2) {
    DrawTextEx(font, label, { x, y }, 16, 1, COL_TEXT);
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

void App::DrawMouseSettings(Font uiFont) {
    DrawTextEx(uiFont, "НАСТРОЙКИ МЫШИ", { 40, 90 }, 24, 1, COL_ACCENT);
    DrawPanel(uiFont, { 40, 140, 350, 100 }, "СЕНСА (VALORANT)");
    DrawSliderBox(uiFont, 60, 180, "Чувствительность", &settings.mouse.valorantSens, 0.1f, 8.0f, sensBuffer, &sensEditMode, false, 3);
    static char multBuffer[16] = "3.15";
    static bool multEditMode = false;
    DrawPanel(uiFont, { 40, 260, 350, 100 }, "МНОЖИТЕЛЬ (ПОДГОНКА)");
    DrawSliderBox(uiFont, 60, 300, "Множитель", &settings.mouse.sensMultiplier, 0.5f, 5.0f, multBuffer, &multEditMode);
    static float lastSaveTime = 0.0f;
    if (GetTime() - lastSaveTime > 2.0f) { settings.Save(); lastSaveTime = GetTime(); }
}

void App::DrawArenaSettings(Font uiFont) {
    DrawTextEx(uiFont, "НАСТРОЙКИ АРЕНЫ", { 40, 90 }, 24, 1, COL_ACCENT);
    static char distBuffer[16] = "15";
    static bool distEdit = false;
    DrawPanel(uiFont, { 40, 140, 350, 100 }, "ДИСТАНЦИЯ ДО ЦЕЛЕЙ");
    DrawSliderBox(uiFont, 60, 180, "Метры", &settings.arena.distance, 5.0f, 30.0f, distBuffer, &distEdit, true);

    DrawPanel(uiFont, { 40, 260, 350, 100 }, "ЦВЕТ ШАРОВ");
    Color colors[] = { { 0, 220, 255, 255 }, WHITE, YELLOW, PINK, ORANGE, RED, GREEN };
    for (int i = 0; i < 7; i++) {
        Rectangle btn = { 60.0f + i * 40.0f, 300, 30, 30 };
        DrawRectangleRec(btn, colors[i]);
        DrawRectangleLinesEx(btn, (settings.arena.ballColor.r == colors[i].r && settings.arena.ballColor.g == colors[i].g) ? 2.0f : 1.0f, (settings.arena.ballColor.r == colors[i].r && settings.arena.ballColor.g == colors[i].g) ? COL_ACCENT : COL_BORDER);
        if (CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) settings.arena.ballColor = colors[i];
    }

    static char sizeBuffer[16] = "0.11";
    static bool sizeEdit = false;
    DrawPanel(uiFont, { 40, 380, 350, 100 }, "РАЗМЕР ШАРОВ");
    DrawSliderBox(uiFont, 60, 420, "Радиус (метры)", &settings.arena.targetRadius, 0.02f, 2.0f, sizeBuffer, &sizeEdit, false);

    Rectangle previewBox = { 420, 140, 500, 340 };
    DrawRectangleRounded(previewBox, 0.02f, 4, Color{ 30, 35, 40, 255 });
    DrawRectangleLinesEx(previewBox, 2.0f, COL_BORDER);
    DrawLineEx({previewBox.x, previewBox.y + 250}, {previewBox.x + previewBox.width, previewBox.y + 250}, 2.0f, COL_BORDER);
    float cx = previewBox.x + previewBox.width / 2.0f, cy = previewBox.y + previewBox.height / 2.0f - 30;
    float aspect = (float)GetScreenWidth() / (float)GetScreenHeight();
    float vFovRad = 2.0f * atanf(tanf((settings.fovDegrees * DEG2RAD) / 2.0f) / aspect);
    float pxRadius = (settings.arena.targetRadius / settings.arena.distance) * (GetScreenHeight() / 2.0f) / tanf(vFovRad / 2.0f);
    if (pxRadius < 0.5f) pxRadius = 0.5f; 

    DrawCircle(cx, cy, pxRadius, settings.arena.ballColor);
    Color chCol = settings.crosshair.color;
    float len = settings.crosshair.length, thic = settings.crosshair.thickness, gap = settings.crosshair.gap;
    DrawRectanglePro({cx, cy - gap - len/2.0f, thic, len}, {thic/2.0f, len/2.0f}, 0.0f, chCol);
    DrawRectanglePro({cx, cy + gap + len/2.0f, thic, len}, {thic/2.0f, len/2.0f}, 0.0f, chCol);
    DrawRectanglePro({cx - gap - len/2.0f, cy, len, thic}, {len/2.0f, thic/2.0f}, 0.0f, chCol);
    DrawRectanglePro({cx + gap + len/2.0f, cy, len, thic}, {len/2.0f, thic/2.0f}, 0.0f, chCol);
    if (settings.crosshair.dot) DrawRectanglePro({cx, cy, thic, thic}, {thic/2.0f, thic/2.0f}, 0.0f, chCol);

    const char* infoText = TextFormat("Диаметр: %.1f см (%.0f px)", settings.arena.targetRadius * 200.0f, pxRadius * 2.0f);
    float tw = MeasureTextEx(uiFont, infoText, 18, 1).x;
    DrawTextEx(uiFont, infoText, { previewBox.x + (previewBox.width - tw) / 2.0f, previewBox.y + previewBox.height - 40 }, 18, 1, COL_TEXT);
    static float lastSaveTime = 0.0f;
    if (GetTime() - lastSaveTime > 2.0f) { settings.Save(); lastSaveTime = GetTime(); }
}

void App::DrawCrosshairSettings(Font uiFont) {
    DrawTextEx(uiFont, "НАСТРОЙКИ ПРИЦЕЛА", { 40, 90 }, 24, 1, COL_ACCENT);
    DrawPanel(uiFont, { 40, 140, 350, 210 }, "ФОРМА");
    static char lenBuffer[16] = "4", thicBuffer[16] = "1", gapBuffer[16] = "0";
    static bool lenEdit = false, thicEdit = false, gapEdit = false;
    DrawSliderBox(uiFont, 60, 180, "Длина линий", &settings.crosshair.length, 0.0f, 20.0f, lenBuffer, &lenEdit, true);
    DrawSliderBox(uiFont, 60, 230, "Толщина", &settings.crosshair.thickness, 1.0f, 10.0f, thicBuffer, &thicEdit, true);
    DrawSliderBox(uiFont, 60, 280, "Отступ (Gap)", &settings.crosshair.gap, 0.0f, 20.0f, gapBuffer, &gapEdit, true);

    DrawPanel(uiFont, { 40, 370, 350, 130 }, "ДОПОЛНИТЕЛЬНО");
    GuiCheckBox({ 60, 400, 20, 20 }, "Центральная точка", &settings.crosshair.dot);
    GuiCheckBox({ 60, 430, 20, 20 }, "Обводка (Outline)", &settings.crosshair.outline);
    GuiCheckBox({ 60, 460, 20, 20 }, "Хитмаркер", &settings.crosshair.hitmarker);

    DrawPanel(uiFont, { 40, 520, 350, 90 }, "ЦВЕТ ПРИЦЕЛА");
    Color colors[] = { WHITE, BLACK, YELLOW, PINK, SKYBLUE, ORANGE, RED };
    for (int i = 0; i < 7; i++) {
        Rectangle btn = { 60.0f + i * 40.0f, 550, 30, 30 };
        DrawRectangleRec(btn, colors[i]);
        DrawRectangleLinesEx(btn, (settings.crosshair.color.r == colors[i].r && settings.crosshair.color.g == colors[i].g) ? 2.0f : 1.0f, (settings.crosshair.color.r == colors[i].r && settings.crosshair.color.g == colors[i].g) ? COL_ACCENT : COL_BORDER);
        if (CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) settings.crosshair.color = colors[i];
    }

    Rectangle previewBox = { 420, 140, 500, 400 };
    DrawRectangleRounded(previewBox, 0.02f, 4, Color{ 30, 35, 40, 255 });
    DrawRectangleLinesEx(previewBox, 2.0f, COL_BORDER);
    DrawLineEx({previewBox.x, previewBox.y + 300}, {previewBox.x + previewBox.width, previewBox.y + 300}, 2.0f, COL_BORDER);
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
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.8f));
    
    float pw = 500, ph = 450;
    Rectangle panel = { (GetScreenWidth() - pw) / 2.0f, (GetScreenHeight() - ph) / 2.0f, pw, ph };
    DrawRectangleRounded(panel, 0.05f, 4, COL_PANEL);
    DrawRectangleLinesEx(panel, 2.0f, COL_ACCENT);

    const char* title = "РЕЗУЛЬТАТЫ";
    float tw = MeasureTextEx(uiFont, title, 32, 1).x;
    DrawTextEx(uiFont, title, { panel.x + (pw - tw) / 2.0f, panel.y + 30 }, 32, 1, COL_ACCENT);
    DrawLineEx({panel.x + 20, panel.y + 80}, {panel.x + pw - 20, panel.y + 80}, 1.0f, COL_BORDER);

    float textY = panel.y + 110;
    
    DrawTextEx(uiFont, "Время:", { panel.x + 50, textY }, 20, 1, COL_TEXT);
    DrawTextEx(uiFont, "60 сек", { panel.x + 300, textY }, 20, 1, WHITE);
    textY += 40;

    DrawTextEx(uiFont, "Сгенерировано шаров:", { panel.x + 50, textY }, 20, 1, COL_TEXT);
    DrawTextEx(uiFont, TextFormat("%d", game.GetSpawnedBalls()), { panel.x + 300, textY }, 20, 1, WHITE);
    textY += 40;

    DrawTextEx(uiFont, "Уничтожено:", { panel.x + 50, textY }, 20, 1, COL_TEXT);
    DrawTextEx(uiFont, TextFormat("%d", game.GetPoppedCount()), { panel.x + 300, textY }, 20, 1, WHITE);
    textY += 40;

    float accuracy = (game.GetSpawnedBalls() > 0) ? 100.0f * game.GetPoppedCount() / game.GetSpawnedBalls() : 0.0f;

    DrawTextEx(uiFont, "Точность:", { panel.x + 50, textY }, 20, 1, COL_TEXT);
    DrawTextEx(uiFont, TextFormat("%.1f%%", accuracy), { panel.x + 300, textY }, 20, 1, WHITE);
    
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(COL_BG)); 
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(COL_BORDER));
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(COL_ACCENT)); 

    if (GuiButton({ panel.x + 50, panel.y + 350, 180, 40 }, "ЗАНОВО")) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining(GameMode::TIMED);
    }
    if (GuiButton({ panel.x + 270, panel.y + 350, 180, 40 }, "В МЕНЮ")) {
        currentScreen = AppScreen::ROUTINES;
    }
}