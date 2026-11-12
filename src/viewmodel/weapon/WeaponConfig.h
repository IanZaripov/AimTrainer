#pragma once
#include "raylib.h"

namespace WeaponConfig {
    constexpr float OffsetForward = 0.25f;
    constexpr float OffsetRight   = 0.12f;
    constexpr float OffsetDown    = 0.12f;

    constexpr Color SlideColor  = { 60, 65, 75, 255 };
    constexpr Color BarrelColor = { 30, 30, 35, 255 };
    constexpr Color GripColor   = { 35, 40, 45, 255 };

    // Slide
    constexpr Vector3 SlidePos  = { 0.0f, 0.02f, 0.05f };
    constexpr Vector3 SlideSize = { 0.04f, 0.04f, 0.18f };

    // Barrel (extended forward)
    constexpr Vector3 BarrelStart = { 0.0f, 0.02f, 0.14f };
    constexpr Vector3 BarrelEnd   = { 0.0f, 0.02f, 0.18f };
    constexpr float BarrelRadius  = 0.015f;
    constexpr int BarrelSides     = 8;

    // Grip
    constexpr Vector3 GripPos  = { 0.0f, -0.05f, 0.0f };
    constexpr Vector3 GripSize = { 0.035f, 0.10f, 0.05f };
}