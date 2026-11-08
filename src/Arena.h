#pragma once
#include "raylib.h"

class Arena {
public:
    Arena();
    void Draw() const;

private:
    // Размеры комнаты
    const float width = 40.0f;
    const float depth = 100.0f; 
    const float height = 12.0f;

    // Цветовая палитра (вынесена из метода Draw)
    const Color floorColor   = Color{ 80, 95, 115, 255 };
    const Color wallColor    = Color{ 60, 75, 95, 255 };
    const Color ceilingColor = Color{ 90, 105, 125, 255 };
    const Color gridColor    = Color{ 100, 115, 135, 255 };
    const Color neonColor    = Color{ 255, 70, 85, 255 };

    // Приватные методы для отрисовки каждой детали
    void DrawFloor() const;
    void DrawWalls() const;
    void DrawCeiling() const;
    void DrawGrid() const;
    void DrawNeonLines() const;
};