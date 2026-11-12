#include "UIWidgets.h"
#include "UITheme.h"
#include "raygui.h"
#include <cstdio>
#include <cstdlib>

namespace UIWidgets {

void DrawSliderBox(Font font, float x, float y, const char* label, float* value, float min, float max, char* buffer, bool* editMode, bool isInt, int precision) {
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

void DrawColorPickerRow(float x, float y, Color* targetColor, const Color* palette, int paletteSize) {
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

} // namespace UIWidgets