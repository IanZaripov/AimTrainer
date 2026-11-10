#pragma once
#include "raylib.h"

namespace WeaponConfig {
    // Позиция оружия относительно камеры
    constexpr float OffsetForward = 0.25f;
    constexpr float OffsetRight   = 0.12f;
    constexpr float OffsetDown    = 0.12f;

    // Цвета
    constexpr Color SlideColor  = { 60, 65, 75, 255 };
    constexpr Color BarrelColor = { 30, 30, 35, 255 };
    constexpr Color GripColor   = { 35, 40, 45, 255 };

    // Затвор
    constexpr Vector3 SlidePos  = { 0.0f, 0.01f, 0.05f };
    constexpr Vector3 SlideSize = { 0.035f, 0.035f, 0.18f };

    // Ствол
    constexpr Vector3 BarrelStart = { 0.0f, 0.01f, 0.14f };
    constexpr Vector3 BarrelEnd   = { 0.0f, 0.01f, 0.20f };
    constexpr float BarrelRadius  = 0.012f;
    constexpr int BarrelSides     = 8;

    // Прицельные
    constexpr Vector3 FrontSightPos  = { 0.0f, 0.035f, 0.13f };
    constexpr Vector3 FrontSightSize = { 0.008f, 0.01f, 0.01f };
    constexpr Vector3 RearSightPos   = { 0.0f, 0.035f, -0.02f };
    constexpr Vector3 RearSightSize  = { 0.015f, 0.01f, 0.01f };

    // Рукоять и скоба
    constexpr Vector3 GripPos  = { 0.0f, -0.05f, -0.01f };
    constexpr Vector3 GripSize = { 0.03f, 0.10f, 0.05f };
    constexpr Vector3 TriggerGuardPos  = { 0.0f, -0.02f, 0.04f };
    constexpr Vector3 TriggerGuardSize = { 0.015f, 0.03f, 0.06f };
}