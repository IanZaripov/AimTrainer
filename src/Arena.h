#pragma once
#include "raylib.h"

class Arena {
public:
    Arena();
    void Draw() const;

private:
    // Размеры арены
    const float width = 30.0f;
    const float depth = 40.0f;
    const float height = 6.0f;

    // Цвета
    const Color floorColor   = { 40, 45, 50, 255 };
    const Color wallColor    = { 70, 130, 180, 255 }; // Steel Blue
    const Color ceilingColor = { 30, 30, 40, 255 };
    const Color lineColor    = LIGHTGRAY;

    void DrawFloor() const;
    void DrawWalls() const;
    void DrawCeiling() const;
    void DrawWallLines() const;
};