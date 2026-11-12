#pragma once
#include "raylib.h"

namespace UIWidgets {
    // Returns true if the value was changed by the user
    bool DrawSliderBox(Font font, float x, float y, const char* label, float* value, float min, float max, char* buffer, bool* editMode, bool isInt = false, int precision = 2);
    
    // Returns true if the color was changed
    bool DrawColorPickerRow(float x, float y, Color* targetColor, const Color* palette, int paletteSize);
}