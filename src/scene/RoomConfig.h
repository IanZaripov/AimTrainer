#pragma once
#include "raylib.h"

namespace RoomConfig {
    namespace Dimensions {
        constexpr float Width  = 40.0f;
        constexpr float Depth  = 100.0f;
        constexpr float Height = 12.0f;
        
        constexpr float WallThickness  = 1.0f;
        constexpr float FloorThickness = 1.0f;
    }

    namespace Grid {
        constexpr int Step = 4;
        constexpr float NeonHeightOffset = 0.05f;
    }

    namespace Colors {
        constexpr Color Floor   = { 80, 95, 115, 255 };
        constexpr Color Wall    = { 60, 75, 95, 255 };
        constexpr Color Ceiling = { 90, 105, 125, 255 };
        constexpr Color Grid    = { 100, 115, 135, 255 };
        constexpr Color Neon    = { 255, 70, 85, 255 };
    }
}