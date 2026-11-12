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
    using namespace UITheme::Screens::Settings;
    auto& settings = manager.GetSettings();
    
    DrawTextEx(uiFont, "НАСТРОЙКИ ПРИЦЕЛА", { TitleX, TitleY }, TitleFontSize, 1, UITheme::ACCENT);

    UITheme::DrawTitledGroup(uiFont, { GroupX, Crosshair::FormGroupY, GroupWidth, Crosshair::FormGroupH }, "ФОРМА");
    isDirty |= UIWidgets::DrawSliderBox(uiFont, Crosshair::FormLabelX, Crosshair::FormLabelStartY, "Длина линий", &settings.crosshair.length, 0.0f, 20.0f, lenBuffer, &lenEdit, true);
    isDirty |= UIWidgets::DrawSliderBox(uiFont, Crosshair::FormLabelX, Crosshair::FormLabelStartY + Crosshair::FormRowSpacing, "Толщина", &settings.crosshair.thickness, 1.0f, 10.0f, thicBuffer, &thicEdit, true);
    isDirty |= UIWidgets::DrawSliderBox(uiFont, Crosshair::FormLabelX, Crosshair::FormLabelStartY + Crosshair::FormRowSpacing * 2, "Отступ (Gap)", &settings.crosshair.gap, 0.0f, 20.0f, gapBuffer, &gapEdit, true);

    UITheme::DrawTitledGroup(uiFont, { GroupX, Crosshair::ExtraGroupY, GroupWidth, Crosshair::ExtraGroupH }, "ДОПОЛНИТЕЛЬНО");
    
    bool oldDot = settings.crosshair.dot;
    GuiCheckBox({ Crosshair::ExtraCheckboxX, Crosshair::ExtraCheckbox1Y, 20, 20 }, "Центральная точка", &settings.crosshair.dot);
    bool oldOutline = settings.crosshair.outline;
    GuiCheckBox({ Crosshair::ExtraCheckboxX, Crosshair::ExtraCheckbox2Y, 20, 20 }, "Обводка (Outline)", &settings.crosshair.outline);
    if (oldDot != settings.crosshair.dot || oldOutline != settings.crosshair.outline) isDirty = true;

    UITheme::DrawTitledGroup(uiFont, { GroupX, Crosshair::ColorGroupY, GroupWidth, Crosshair::ColorGroupH }, "ЦВЕТ ПРИЦЕЛА");
    Color colors[] = { WHITE, BLACK, YELLOW, PINK, SKYBLUE, ORANGE, RED };
    isDirty |= UIWidgets::DrawColorPickerRow(Crosshair::ColorPickerX, Crosshair::ColorPickerY, &settings.crosshair.color, colors, 7);

    // ... (тут оставь весь код отрисовки превью прицела, он не меняется) ...
    Rectangle previewBox = { Crosshair::PreviewX, Crosshair::PreviewY, Crosshair::PreviewW, Crosshair::PreviewH };
    DrawRectangleRounded(previewBox, Crosshair::PreviewRoundness, 4, Color{ 30, 35, 40, 255 });
    DrawRectangleLinesEx(previewBox, Crosshair::PreviewBorderThickness, UITheme::BORDER);
    DrawLineEx({previewBox.x, previewBox.y + Crosshair::PreviewFloorY}, {previewBox.x + previewBox.width, previewBox.y + Crosshair::PreviewFloorY}, 2.0f, UITheme::BORDER);

    float cx = previewBox.x + previewBox.width / 2.0f;
    float cy = previewBox.y + previewBox.height / 2.0f + Crosshair::PreviewCenterYOffset;
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
}