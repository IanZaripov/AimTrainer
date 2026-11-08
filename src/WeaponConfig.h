#pragma once
#include "raylib.h"

namespace WeaponConfig {
    // Позиция оружия относительно камеры (смещение в метрах)
    constexpr float OffsetForward = 0.25f;
    constexpr float OffsetRight = 0.12f;
    constexpr float OffsetDown = 0.12f;

    // Цвета
    constexpr Color SlideColor  = { 60, 65, 75, 255 };
    constexpr Color BarrelColor = { 30, 30, 35, 255 };
    constexpr Color GripColor   = { 35, 40, 45, 255 };
    constexpr Color SkinColor   = { 220, 180, 150, 255 };
    constexpr Color SleeveColor = { 40, 60, 110, 255 };

    // Затвор (Slide)
    constexpr Vector3 SlidePos  = { 0.0f, 0.01f, 0.05f };
    constexpr Vector3 SlideSize = { 0.035f, 0.035f, 0.18f };

    // Ствол (Barrel)
    constexpr Vector3 BarrelStart = { 0.0f, 0.01f, 0.14f };
    constexpr Vector3 BarrelEnd   = { 0.0f, 0.01f, 0.20f };
    constexpr float BarrelRadius  = 0.012f;
    constexpr int BarrelSides     = 8;

    // Прицельные (Sights)
    constexpr Vector3 FrontSightPos  = { 0.0f, 0.035f, 0.13f };
    constexpr Vector3 FrontSightSize = { 0.008f, 0.01f, 0.01f };
    constexpr Vector3 RearSightPos   = { 0.0f, 0.035f, -0.02f };
    constexpr Vector3 RearSightSize  = { 0.015f, 0.01f, 0.01f };

    // Рукоять и скоба (Grip)
    constexpr Vector3 GripPos  = { 0.0f, -0.05f, -0.01f };
    constexpr Vector3 GripSize = { 0.03f, 0.10f, 0.05f };
    constexpr Vector3 TriggerGuardPos  = { 0.0f, -0.02f, 0.04f };
    constexpr Vector3 TriggerGuardSize = { 0.015f, 0.03f, 0.06f };

    // Рука (Hand)
    constexpr Vector3 HandPos  = { 0.01f, -0.08f, -0.01f };
    constexpr Vector3 HandSize = { 0.05f, 0.08f, 0.07f };
    constexpr Vector3 ThumbPos = { -0.01f, -0.04f, 0.02f };
    constexpr Vector3 ThumbSize= { 0.02f, 0.04f, 0.03f };

    // Рукав (Sleeve)
    constexpr Vector3 SleevePos  = { 0.02f, -0.15f, -0.06f };
    constexpr Vector3 SleeveSize = { 0.07f, 0.12f, 0.12f };
}