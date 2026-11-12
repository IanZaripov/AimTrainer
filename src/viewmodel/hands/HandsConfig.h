#pragma once
#include "raylib.h"

namespace HandsConfig {
    namespace Palm {
        constexpr Color color = { 220, 180, 150, 255 };
        constexpr Vector3 Pos  = { 0.01f, -0.08f, 0.0f };
        constexpr Vector3 Size = { 0.06f, 0.08f, 0.07f };
    }

    namespace Thumb {
        constexpr Color color = { 220, 180, 150, 255 };
        constexpr Vector3 Pos  = { -0.02f, -0.04f, 0.02f };
        constexpr Vector3 Size = { 0.02f, 0.04f, 0.04f };
    }

    namespace Sleeve {
        constexpr Color color = { 40, 60, 110, 255 };
        constexpr Vector3 Pos  = { 0.02f, -0.15f, -0.06f };
        constexpr Vector3 Size = { 0.08f, 0.12f, 0.12f };
    }
}