#include "ArenaSettingsScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "UIWidgets.h"
#include <cmath>

void ArenaSettingsScreen::Update(ScreenManager& manager) {
    if (isDirty) {
        manager.GetSettings().Save();
        isDirty = false;
    }
}

void ArenaSettingsScreen::Draw(Font uiFont, ScreenManager& manager) {
    using namespace UITheme::Screens::Settings;
    auto& settings = manager.GetSettings();
    
    DrawTextEx(uiFont, "НАСТРОЙКИ АРЕНЫ", { TitleX, TitleY }, TitleFontSize, 1, UITheme::ACCENT);

    UITheme::DrawTitledGroup(uiFont, { GroupX, ArenaSettings::DistGroupY, GroupWidth, ArenaSettings::DistGroupH }, "ДИСТАНЦИЯ ДО ЦЕЛЕЙ");
    isDirty |= UIWidgets::DrawSliderBox(uiFont, ArenaSettings::DistLabelX, ArenaSettings::DistLabelY, "Метры", &settings.arena.distance, 5.0f, 30.0f, distBuffer, &distEdit, true);

    UITheme::DrawTitledGroup(uiFont, { GroupX, ArenaSettings::ColorGroupY, GroupWidth, ArenaSettings::ColorGroupH }, "ЦВЕТ ШАРОВ");
    Color colors[] = { { 0, 220, 255, 255 }, WHITE, YELLOW, PINK, ORANGE, RED, GREEN };
    isDirty |= UIWidgets::DrawColorPickerRow(ArenaSettings::ColorPickerX, ArenaSettings::ColorPickerY, &settings.arena.ballColor, colors, 7);

    UITheme::DrawTitledGroup(uiFont, { GroupX, ArenaSettings::SizeGroupY, GroupWidth, ArenaSettings::SizeGroupH }, "РАЗМЕР ШАРОВ");
    isDirty |= UIWidgets::DrawSliderBox(uiFont, ArenaSettings::SizeLabelX, ArenaSettings::SizeLabelY, "Радиус (метры)", &settings.arena.targetRadius, 0.02f, 2.0f, sizeBuffer, &sizeEdit, false);

    Rectangle previewBox = { ArenaSettings::PreviewX, ArenaSettings::PreviewY, ArenaSettings::PreviewW, ArenaSettings::PreviewH };
    DrawRectangleRounded(previewBox, ArenaSettings::PreviewRoundness, 4, Color{ 30, 35, 40, 255 });
    DrawRectangleLinesEx(previewBox, ArenaSettings::PreviewBorderThickness, UITheme::BORDER);
    DrawLineEx({previewBox.x, previewBox.y + ArenaSettings::PreviewFloorY}, {previewBox.x + previewBox.width, previewBox.y + ArenaSettings::PreviewFloorY}, 2.0f, UITheme::BORDER);

    float cx = previewBox.x + previewBox.width / 2.0f;
    float cy = previewBox.y + previewBox.height / 2.0f + ArenaSettings::PreviewCenterYOffset;
    
    float aspect = (float)GetRenderWidth() / (float)GetRenderHeight();
    float vFovRad = 2.0f * atanf(tanf((settings.fovDegrees * DEG2RAD) / 2.0f) / aspect);
    float pxRadius = (settings.arena.targetRadius / settings.arena.distance) * (GetRenderHeight() / 2.0f) / tanf(vFovRad / 2.0f);
    if (pxRadius < 0.5f) pxRadius = 0.5f;

    DrawCircle(cx, cy, pxRadius, settings.arena.ballColor);
    
    const char* infoText = TextFormat("Диаметр: %.1f см (%.0f px)", settings.arena.targetRadius * 200.0f, pxRadius * 2.0f);
    float tw = MeasureTextEx(uiFont, infoText, 18, 1).x;
    DrawTextEx(uiFont, infoText, { previewBox.x + (previewBox.width - tw) / 2.0f, previewBox.y + previewBox.height + ArenaSettings::PreviewInfoYOffset }, 18, 1, UITheme::TEXT);
}