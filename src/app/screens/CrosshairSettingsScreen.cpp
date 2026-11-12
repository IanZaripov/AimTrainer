#include "CrosshairSettingsScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "UIWidgets.h"
#include "raygui.h"

void CrosshairSettingsScreen::Update(ScreenManager& manager) {
    if (isDirty) {
        manager.GetSettings().Save();
        isDirty = false;
    }
}

void CrosshairSettingsScreen::Draw(Font uiFont, ScreenManager& manager) {
    auto& settings = manager.GetSettings();

    DrawTitle(uiFont);
    
    isDirty |= DrawFormGroup(uiFont, settings);
    isDirty |= DrawExtraGroup(uiFont, settings);
    isDirty |= DrawColorGroup(uiFont, settings);
    
    DrawPreview(uiFont, settings);
}

void CrosshairSettingsScreen::DrawTitle(Font uiFont) const {
    using namespace UITheme::Screens::Settings;
    DrawTextEx(uiFont, "НАСТРОЙКИ ПРИЦЕЛА", { TitleX, TitleY }, TitleFontSize, 1, UITheme::ACCENT);
}

// Draws the sliders for length, thickness, and gap
bool CrosshairSettingsScreen::DrawFormGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    bool changed = false;

    UITheme::DrawTitledGroup(uiFont, { GroupX, Crosshair::FormGroupY, GroupWidth, Crosshair::FormGroupH }, "ФОРМА");
    changed |= UIWidgets::DrawSliderBox(uiFont, Crosshair::FormLabelX, Crosshair::FormLabelStartY, "Длина линий", &settings.crosshair.length, 0.0f, 20.0f, lenBuffer, &lenEdit, true);
    changed |= UIWidgets::DrawSliderBox(uiFont, Crosshair::FormLabelX, Crosshair::FormLabelStartY + Crosshair::FormRowSpacing, "Толщина", &settings.crosshair.thickness, 1.0f, 10.0f, thicBuffer, &thicEdit, true);
    changed |= UIWidgets::DrawSliderBox(uiFont, Crosshair::FormLabelX, Crosshair::FormLabelStartY + Crosshair::FormRowSpacing * 2, "Отступ (Gap)", &settings.crosshair.gap, 0.0f, 20.0f, gapBuffer, &gapEdit, true);

    return changed;
}

// Draws the checkboxes for dot and outline
bool CrosshairSettingsScreen::DrawExtraGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, Crosshair::ExtraGroupY, GroupWidth, Crosshair::ExtraGroupH }, "ДОПОЛНИТЕЛЬНО");
    
    bool oldDot = settings.crosshair.dot;
    GuiCheckBox({ Crosshair::ExtraCheckboxX, Crosshair::ExtraCheckbox1Y, 20, 20 }, "Центральная точка", &settings.crosshair.dot);
    
    bool oldOutline = settings.crosshair.outline;
    GuiCheckBox({ Crosshair::ExtraCheckboxX, Crosshair::ExtraCheckbox2Y, 20, 20 }, "Обводка (Outline)", &settings.crosshair.outline);

    return (oldDot != settings.crosshair.dot || oldOutline != settings.crosshair.outline);
}

bool CrosshairSettingsScreen::DrawColorGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, Crosshair::ColorGroupY, GroupWidth, Crosshair::ColorGroupH }, "ЦВЕТ ПРИЦЕЛА");
    Color colors[] = { WHITE, BLACK, YELLOW, PINK, SKYBLUE, ORANGE, RED };
    
    return UIWidgets::DrawColorPickerRow(Crosshair::ColorPickerX, Crosshair::ColorPickerY, &settings.crosshair.color, colors, 7);
}

void CrosshairSettingsScreen::DrawPreview(Font uiFont, const Settings& settings) const {
    using namespace UITheme::Screens::Settings;

    Rectangle previewBox = { Crosshair::PreviewX, Crosshair::PreviewY, Crosshair::PreviewW, Crosshair::PreviewH };
    
    drawBackGroundAndFlorPreview(previewBox);
    DrawCrosshairPreview(settings);
}

void CrosshairSettingsScreen::drawBackGroundAndFlorPreview(Rectangle previewBox) const {
    using namespace UITheme::Screens::Settings;
    // Background
    DrawRectangleRounded(previewBox, Crosshair::PreviewRoundness, 4, Color{ 30, 35, 40, 255 });
    // Border
    DrawRectangleLinesEx(previewBox, Crosshair::PreviewBorderThickness, UITheme::BORDER);
    // Floor line
    DrawLineEx(
        { previewBox.x, previewBox.y + Crosshair::PreviewFloorY }, 
        { previewBox.x + previewBox.width, previewBox.y + Crosshair::PreviewFloorY }, 
        2.0f, 
        UITheme::BORDER
    );
}

void CrosshairSettingsScreen::DrawCrosshairPreview(const Settings& settings) const {
    using namespace UITheme::Screens::Settings;

    float cx = Crosshair::PreviewX + Crosshair::PreviewW / 2.0f;
    float cy = Crosshair::PreviewY + Crosshair::PreviewH / 2.0f + Crosshair::PreviewCenterYOffset;
    Color col = settings.crosshair.color;
    float len = settings.crosshair.length;
    float thic = settings.crosshair.thickness;
    float gap = settings.crosshair.gap;
    if (settings.crosshair.outline) {
        DrawOutline(cx, cy, len, thic, gap);
    }
    DrawMainLines(cx, cy, len, thic, gap, col);
    if (settings.crosshair.dot) {
        DrawCenterDot(cx, cy, thic, col);
    }
}

void CrosshairSettingsScreen::DrawOutline(float cx, float cy, float len, float thic, float gap) const {
    Color out = BLACK; 
    float oT = thic + 2.0f; 
    float oL = len + 2.0f;
    
    DrawRectanglePro({cx, cy - gap - len/2.0f, oT, oL}, {oT/2.0f, oL/2.0f}, 0.0f, out);
    DrawRectanglePro({cx, cy + gap + len/2.0f, oT, oL}, {oT/2.0f, oL/2.0f}, 0.0f, out);
    DrawRectanglePro({cx - gap - len/2.0f, cy, oL, oT}, {oL/2.0f, oT/2.0f}, 0.0f, out);
    DrawRectanglePro({cx + gap + len/2.0f, cy, oL, oT}, {oL/2.0f, oT/2.0f}, 0.0f, out);
}

void CrosshairSettingsScreen::DrawMainLines(float cx, float cy, float len, float thic, float gap, Color color) const {
    DrawRectanglePro({cx, cy - gap - len/2.0f, thic, len}, {thic/2.0f, len/2.0f}, 0.0f, color);
    DrawRectanglePro({cx, cy + gap + len/2.0f, thic, len}, {thic/2.0f, len/2.0f}, 0.0f, color);
    DrawRectanglePro({cx - gap - len/2.0f, cy, len, thic}, {len/2.0f, thic/2.0f}, 0.0f, color);
    DrawRectanglePro({cx + gap + len/2.0f, cy, len, thic}, {len/2.0f, thic/2.0f}, 0.0f, color);
}

void CrosshairSettingsScreen::DrawCenterDot(float cx, float cy, float thic, Color color) const {
    DrawRectanglePro({cx, cy, thic, thic}, {thic/2.0f, thic/2.0f}, 0.0f, color);
}