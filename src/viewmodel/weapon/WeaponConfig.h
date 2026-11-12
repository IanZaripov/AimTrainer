#pragma once
#include "raylib.h"

namespace WeaponConfig {
    namespace Offsets {
        constexpr float Forward = 0.25f;
        constexpr float Right   = 0.12f;
        constexpr float Down    = 0.12f;
    }

    namespace Slide {
        constexpr Color color = { 60, 65, 75, 255 };
        constexpr Vector3 Pos  = { 0.0f, 0.02f, 0.05f };
        constexpr Vector3 Size = { 0.04f, 0.04f, 0.18f };
    }

    namespace Barrel {
        constexpr Color color = { 30, 30, 35, 255 };
        constexpr Vector3 Start = { 0.0f, 0.02f, 0.14f };
        constexpr Vector3 End   = { 0.0f, 0.02f, 0.18f };
        constexpr float Radius  = 0.015f;
        constexpr int Sides     = 8;
    }

    namespace Grip {
        constexpr Color color = { 35, 40, 45, 255 };
        constexpr Vector3 Pos  = { 0.0f, -0.05f, 0.0f };
        constexpr Vector3 Size = { 0.035f, 0.10f, 0.05f };
    }
}