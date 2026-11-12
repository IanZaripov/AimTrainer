#include "ArenaSettingsScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "UIWidgets.h"
#include <cmath>

void ArenaSettingsScreen::Draw(Font uiFont, ScreenManager& manager) {
    auto& settings = manager.GetSettings();
    DrawTextEx(uiFont, "НАСТРОЙКИ АРЕНЫ", { 40, 90 }, 24, 1, UITheme::ACCENT);

    UITheme::DrawTitledGroup(uiFont, { 40, 140, 350, 100 }, "ДИСТАНЦИЯ ДО ЦЕЛЕЙ");
    UIWidgets::DrawSliderBox(uiFont, 60, 180, "Метры", &settings.arena.distance, 5.0f, 30.0f, distBuffer, &distEdit, true);

    UITheme::DrawTitledGroup(uiFont, { 40, 260, 350, 100 }, "ЦВЕТ ШАРОВ");
    Color colors[] = { { 0, 220, 255, 255 }, WHITE, YELLOW, PINK, ORANGE, RED, GREEN };
    UIWidgets::DrawColorPickerRow(60, 300, &settings.arena.ballColor, colors, 7);

    UITheme::DrawTitledGroup(uiFont, { 40, 380, 350, 100 }, "РАЗМЕР ШАРОВ");
    UIWidgets::DrawSliderBox(uiFont, 60, 420, "Радиус (метры)", &settings.arena.targetRadius, 0.02f, 2.0f, sizeBuffer, &sizeEdit, false);

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