#pragma once
#include "raylib.h"

class Weapon {
public:
    // Рисует оружие в локальном пространстве (0,0,0 = центр оружия)
    // Трансформация (позиция относительно камеры) выставляется в Viewmodel
    void Draw() const;

private:
    void DrawSlide() const;
    void DrawBarrel() const;
    void DrawSights() const;
    void DrawGrip() const;
};