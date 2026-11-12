#pragma once
#include "raylib.h"

namespace UIWidgets {
    void DrawSliderBox(Font font, float x, float y, const char* label, float* value, float min, float max, char* buffer, bool* editMode, bool isInt = false, int precision = 2);
    void DrawColorPickerRow(float x, float y, Color* targetColor, const Color* palette, int paletteSize);
}