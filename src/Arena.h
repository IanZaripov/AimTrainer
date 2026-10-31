#pragma once
#include "raylib.h"

class Arena {
public:
    Arena();
    void Draw() const;

private:
    const float width = 30.0f;
    const float depth = 40.0f;
    const float height = 8.0f;

    const Color floorColor   = { 80, 85, 90, 255 };
    const Color wallColor    = { 60, 65, 75, 255 };
    const Color ceilingColor = { 40, 45, 55, 255 };
    const Color gridColor    = { 100, 105, 115, 255 };

    void DrawFloor() const;
    void DrawWalls() const;
    void DrawCeiling() const;
};