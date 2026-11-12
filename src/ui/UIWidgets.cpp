#include "UIWidgets.h"
#include "UITheme.h"
#include "raygui.h"
#include <cstdio>
#include <cstdlib>

namespace UIWidgets {

bool DrawSliderBox(Font font, float x, float y, const char* label, float* value, float min, float max, char* buffer, bool* editMode, bool isInt, int precision) {
    using namespace UITheme::Widgets::SliderBox;
    
    float oldValue = *value; // <-- Store original value

    DrawTextEx(font, label, { x, y }, LabelFontSize, 1, UITheme::TEXT);
    GuiSlider({ x, y + SliderYOffset, SliderWidth, SliderHeight }, "", "", value, min, max);

    if (!*editMode) {
        if (isInt) snprintf(buffer, 16, "%d", (int)*value);
        else if (precision == 3) snprintf(buffer, 16, "%.3f", *value);
        else snprintf(buffer, 16, "%.2f", *value);
    }

    Rectangle tbRect = { x + TextBoxXOffset, y + TextBoxYOffset, TextBoxWidth, TextBoxHeight };
    if (GuiTextBox(tbRect, buffer, 16, *editMode)) {
        *editMode = !*editMode;
        if (!*editMode) {
            float val = atof(buffer);
            if (val >= min && val <= max) *value = val;
        }
    }

    return (*value != oldValue);
}

bool DrawColorPickerRow(float x, float y, Color* targetColor, const Color* palette, int paletteSize) {
    using namespace UITheme::Widgets::ColorPicker;
    bool changed = false;

    for (int i = 0; i < paletteSize; i++) {
        Rectangle btn = { x + i * ButtonSpacing, y, ButtonSize, ButtonSize };
        DrawRectangleRec(btn, palette[i]);
        bool isSelected = (targetColor->r == palette[i].r && targetColor->g == palette[i].g && targetColor->b == palette[i].b);
        DrawRectangleLinesEx(btn, isSelected ? BorderThicknessSelected : BorderThicknessNormal, isSelected ? UITheme::ACCENT : UITheme::BORDER);

        if (CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *targetColor = palette[i];
            changed = true;
        }
    }
    return changed;
}

}