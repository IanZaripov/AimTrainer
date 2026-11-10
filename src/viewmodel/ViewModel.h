#pragma once
#include "raylib.h"
#include "Weapon.h"
#include "Hands.h"

class Viewmodel {
public:
    // Главный метод: настраивает матрицу и рисует Weapon + Hands
    void Draw(const Camera3D& camera) const;

private:
    Weapon weapon;
    Hands  hands;

    // Настройка матрицы (позиция относительно камеры)
    void SetupTransform(const Camera3D& camera) const;
};