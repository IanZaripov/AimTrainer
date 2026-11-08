#pragma once
#include "raylib.h"

class Weapon {
public:
    void Draw(const Camera3D& camera) const;

private:
    // Настройка матрицы для отрисовки viewmodel'а (оружия в руках)
    void SetupWeaponTransform(const Camera3D& camera) const;

    // Отрисовка деталей
    void DrawSlide() const;
    void DrawBarrel() const;
    void DrawSights() const;
    void DrawGrip() const;
    void DrawHand() const;
    void DrawSleeve() const;
};