#pragma once
#include "raylib.h"

namespace HandsConfig {
    // Цвета
    constexpr Color SkinColor   = { 220, 180, 150, 255 };
    constexpr Color SleeveColor = { 40, 60, 110, 255 };

    // Ладонь
    constexpr Vector3 HandPos  = { 0.01f, -0.08f, -0.01f };
    constexpr Vector3 HandSize = { 0.05f, 0.08f, 0.07f };

    // Большой палец
    constexpr Vector3 ThumbPos  = { -0.01f, -0.04f, 0.02f };
    constexpr Vector3 ThumbSize = { 0.02f, 0.04f, 0.03f };

    // Рукав
    constexpr Vector3 SleevePos  = { 0.02f, -0.15f, -0.06f };
    constexpr Vector3 SleeveSize = { 0.07f, 0.12f, 0.12f };
}