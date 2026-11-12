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
    auto& settings = manager.GetSettings();

    DrawTitle(uiFont);
    
    isDirty |= DrawDistanceGroup(uiFont, settings);
    isDirty |= DrawColorGroup(uiFont, settings);
    isDirty |= DrawSizeGroup(uiFont, settings);

    DrawPreview(uiFont, settings);
}

void ArenaSettingsScreen::DrawTitle(Font uiFont) const {
    using namespace UITheme::Screens::Settings;
    DrawTextEx(uiFont, "НАСТРОЙКИ АРЕНЫ", { TitleX, TitleY }, TitleFontSize, 1, UITheme::ACCENT);
}

bool ArenaSettingsScreen::DrawDistanceGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, ArenaSettings::DistGroupY, GroupWidth, ArenaSettings::DistGroupH }, "ДИСТАНЦИЯ ДО ЦЕЛЕЙ");
    return UIWidgets::DrawSliderBox(
        uiFont, ArenaSettings::DistLabelX, ArenaSettings::DistLabelY, 
        "Метры", 
        &settings.arena.distance, 5.0f, 30.0f, 
        distBuffer, &distEdit, true
    );
}

bool ArenaSettingsScreen::DrawColorGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, ArenaSettings::ColorGroupY, GroupWidth, ArenaSettings::ColorGroupH }, "ЦВЕТ ШАРОВ");
    Color colors[] = { { 0, 220, 255, 255 }, WHITE, YELLOW, PINK, ORANGE, RED, GREEN };
    
    return UIWidgets::DrawColorPickerRow(
        ArenaSettings::ColorPickerX, ArenaSettings::ColorPickerY, 
        &settings.arena.ballColor, colors, 7
    );
}

bool ArenaSettingsScreen::DrawSizeGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, ArenaSettings::SizeGroupY, GroupWidth, ArenaSettings::SizeGroupH }, "РАЗМЕР ШАРОВ");
    return UIWidgets::DrawSliderBox(
        uiFont, ArenaSettings::SizeLabelX, ArenaSettings::SizeLabelY, 
        "Радиус (метры)", 
        &settings.arena.targetRadius, 0.02f, 2.0f, 
        sizeBuffer, &sizeEdit, false
    );
}

// Draws the preview box and delegates rendering
void ArenaSettingsScreen::DrawPreview(Font uiFont, const Settings& settings) const {
    using namespace UITheme::Screens::Settings;

    Rectangle previewBox = { 
        ArenaSettings::PreviewX, 
        ArenaSettings::PreviewY, 
        ArenaSettings::PreviewW, 
        ArenaSettings::PreviewH 
    };

    drawBackGroundAndFlorPreview(previewBox);
    DrawTargetPreview(uiFont, previewBox, settings);
}

void ArenaSettingsScreen::drawBackGroundAndFlorPreview(Rectangle previewBox) const {
    using namespace UITheme::Screens::Settings;

    // Background
    DrawRectangleRounded(previewBox, ArenaSettings::PreviewRoundness, 4, Color{ 30, 35, 40, 255 });
    
    // Border
    DrawRectangleLinesEx(previewBox, ArenaSettings::PreviewBorderThickness, UITheme::BORDER);
    
    // Floor line
    DrawLineEx(
        { previewBox.x, previewBox.y + ArenaSettings::PreviewFloorY }, 
        { previewBox.x + previewBox.width, previewBox.y + ArenaSettings::PreviewFloorY }, 
        2.0f, 
        UITheme::BORDER
    );
}

// Calculates pixel size, draws the target circle, and the info text
void ArenaSettingsScreen::DrawTargetPreview(Font uiFont, Rectangle previewBox, const Settings& settings) const {
    float pxRadius = CalculatePixelRadius(settings);
    
    DrawTargetCircle(previewBox, settings, pxRadius);
    DrawInfoText(uiFont, previewBox, settings, pxRadius);
}

float ArenaSettingsScreen::CalculatePixelRadius(const Settings& settings) const {
    float aspect = (float)GetRenderWidth() / (float)GetRenderHeight();
    float vFovRad = 2.0f * atanf(tanf((settings.fovDegrees * DEG2RAD) / 2.0f) / aspect);
    
    // Radius in pixels
    float pxRadius = (settings.arena.targetRadius / settings.arena.distance) * (GetRenderHeight() / 2.0f) / tanf(vFovRad / 2.0f);
    
    // Clamp to avoid invisible or infinitely large circles
    if (pxRadius < 0.5f) pxRadius = 0.5f;
    
    return pxRadius;
}

void ArenaSettingsScreen::DrawTargetCircle(Rectangle previewBox, const Settings& settings, float pxRadius) const {
    using namespace UITheme::Screens::Settings;
    
    float cx = previewBox.x + previewBox.width / 2.0f;
    float cy = previewBox.y + previewBox.height / 2.0f + ArenaSettings::PreviewCenterYOffset;
    
    DrawCircle(cx, cy, pxRadius, settings.arena.ballColor);
}

void ArenaSettingsScreen::DrawInfoText(Font uiFont, Rectangle previewBox, const Settings& settings, float pxRadius) const {
    using namespace UITheme::Screens::Settings;

    const char* infoText = TextFormat("Диаметр: %.1f см (%.0f px)", settings.arena.targetRadius * 200.0f, pxRadius * 2.0f);
    float tw = MeasureTextEx(uiFont, infoText, 18, 1).x;
    
    DrawTextEx(
        uiFont, infoText, 
        { previewBox.x + (previewBox.width - tw) / 2.0f, previewBox.y + previewBox.height + ArenaSettings::PreviewInfoYOffset }, 
        18, 1, UITheme::TEXT
    );
}