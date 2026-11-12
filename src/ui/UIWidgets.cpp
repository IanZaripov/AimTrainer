#include "UIWidgets.h"
#include "UITheme.h"
#include "raygui.h"
#include <cstdio>
#include <cstdlib>

namespace UIWidgets {

bool DrawSliderBox(Font font, float x, float y, const char* label, float* value, float min, float max, char* buffer, bool* editMode, bool isInt, int precision) {
    float oldValue = *value; // Store original value to detect changes

    DrawSliderLabel(font, x, y, label);
    DrawSliderControl(x, y, value, min, max);
    HandleTextBoxInput(x, y, value, min, max, buffer, editMode, isInt, precision);

    return (*value != oldValue);
}

// Draws the text above the slider
void DrawSliderLabel(Font font, float x, float y, const char* label) {
    using namespace UITheme::Widgets::SliderBox;
    DrawTextEx(font, label, { x, y }, LabelFontSize, 1, UITheme::TEXT);
}

// Draws the raygui slider
void DrawSliderControl(float x, float y, float* value, float min, float max) {
    using namespace UITheme::Widgets::SliderBox;
    GuiSlider({ x, y + SliderYOffset, SliderWidth, SliderHeight }, "", "", value, min, max);
}

// Handles the text box logic: formatting string, drawing it, and parsing input
void HandleTextBoxInput(float x, float y, float* value, float min, float max, char* buffer, bool* editMode, bool isInt, int precision) {
    using namespace UITheme::Widgets::SliderBox;

    // Update buffer string if not currently editing
    if (!*editMode) {
        if (isInt) snprintf(buffer, 16, "%d", (int)*value);
        else if (precision == 3) snprintf(buffer, 16, "%.3f", *value);
        else snprintf(buffer, 16, "%.2f", *value);
    }

    // Draw and handle TextBox
    Rectangle tbRect = { x + TextBoxXOffset, y + TextBoxYOffset, TextBoxWidth, TextBoxHeight };
    if (GuiTextBox(tbRect, buffer, 16, *editMode)) {
        *editMode = !*editMode;
        
        // If user finished editing (clicked outside or pressed Enter)
        if (!*editMode) {
            float val = atof(buffer);
            if (val >= min && val <= max) *value = val;
        }
    }
}

bool DrawColorPickerRow(float x, float y, Color* targetColor, const Color* palette, int paletteSize) {
    bool changed = false;

    for (int i = 0; i < paletteSize; i++) {
        Rectangle btn = GetColorButtonRect(x, y, i);
        
        DrawColorButton(btn, palette[i], *targetColor);

        if (IsColorButtonClicked(btn)) {
            *targetColor = palette[i];
            changed = true;
        }
    }
    return changed;
}

Rectangle GetColorButtonRect(float x, float y, int index) {
    using namespace UITheme::Widgets::ColorPicker;
    return { x + index * ButtonSpacing, y, ButtonSize, ButtonSize };
}

bool IsColorSelected(Color currentColor, Color paletteColor) {
    return (currentColor.r == paletteColor.r && 
            currentColor.g == paletteColor.g && 
            currentColor.b == paletteColor.b);
}

void DrawColorButton(Rectangle btn, Color paletteColor, Color currentColor) {
    using namespace UITheme::Widgets::ColorPicker;
    
    DrawRectangleRec(btn, paletteColor);
    bool selected = IsColorSelected(currentColor, paletteColor);
    DrawRectangleLinesEx(
        btn, 
        selected ? BorderThicknessSelected : BorderThicknessNormal, 
        selected ? UITheme::ACCENT : UITheme::BORDER
    );
}

bool IsColorButtonClicked(Rectangle btn) {
    return CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

}