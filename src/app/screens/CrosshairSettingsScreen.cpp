#include "CrosshairSettingsScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "UIWidgets.h"
#include "raygui.h"

void CrosshairSettingsScreen::Draw(Font uiFont, ScreenManager& manager) {
    auto& settings = manager.GetSettings();
    DrawTextEx(uiFont, "НАСТРОЙКИ ПРИЦЕЛА", { 40, 90 }, 24, 1, UITheme::ACCENT);

    UITheme::DrawTitledGroup(uiFont, { 40, 140, 350, 210 }, "ФОРМА");
    UIWidgets::DrawSliderBox(uiFont, 60, 180, "Длина линий", &settings.crosshair.length, 0.0f, 20.0f, lenBuffer, &lenEdit, true);
    UIWidgets::DrawSliderBox(uiFont, 60, 230, "Толщина", &settings.crosshair.thickness, 1.0f, 10.0f, thicBuffer, &thicEdit, true);
    UIWidgets::DrawSliderBox(uiFont, 60, 280, "Отступ (Gap)", &settings.crosshair.gap, 0.0f, 20.0f, gapBuffer, &gapEdit, true);

    UITheme::DrawTitledGroup(uiFont, { 40, 370, 350, 100 }, "ДОПОЛНИТЕЛЬНО");
    GuiCheckBox({ 60, 400, 20, 20 }, "Центральная точка", &settings.crosshair.dot);
    GuiCheckBox({ 60, 430, 20, 20 }, "Обводка (Outline)", &settings.crosshair.outline);

    UITheme::DrawTitledGroup(uiFont, { 40, 490, 350, 90 }, "ЦВЕТ ПРИЦЕЛА");
    Color colors[] = { WHITE, BLACK, YELLOW, PINK, SKYBLUE, ORANGE, RED };
    UIWidgets::DrawColorPickerRow(60, 520, &settings.crosshair.color, colors, 7);

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