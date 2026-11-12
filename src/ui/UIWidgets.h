#pragma once
#include "raylib.h"

namespace UIWidgets {
    // Main widgets
    bool DrawSliderBox(Font font, float x, float y, const char* label, float* value, float min, float max, char* buffer, bool* editMode, bool isInt = false, int precision = 2);
    bool DrawColorPickerRow(float x, float y, Color* targetColor, const Color* palette, int paletteSize);

    // Internal helpers for SliderBox
    void DrawSliderLabel(Font font, float x, float y, const char* label);
    void DrawSliderControl(float x, float y, float* value, float min, float max);
    void HandleTextBoxInput(float x, float y, float* value, float min, float max, char* buffer, bool* editMode, bool isInt, int precision);

    // Internal helpers for ColorPickerRow
    Rectangle GetColorButtonRect(float x, float y, int index);
    bool IsColorSelected(Color currentColor, Color paletteColor);
    void DrawColorButton(Rectangle btn, Color paletteColor, Color currentColor);
    bool IsColorButtonClicked(Rectangle btn);
}