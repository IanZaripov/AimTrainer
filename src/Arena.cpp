#include "Arena.h"

Arena::Arena() {}

void Arena::Draw() const {
    DrawFloor();
    DrawWalls();
    DrawCeiling();
}

void Arena::DrawFloor() const {
    // Сплошной пол
    DrawCube({0.0f, -0.5f, 0.0f}, width, 1.0f, depth, floorColor);
    // Сетка поверх пола (чуть приподнята, чтобы не было мерцания)
    DrawGrid(40, 1.0f);
}

void Arena::DrawWalls() const {
    // Задняя стена
    DrawCube({0.0f, height / 2.0f, -depth / 2.0f - 0.5f}, width, height, 1.0f, wallColor);
    // Левая и правая
    DrawCube({-width / 2.0f - 0.5f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor);
    DrawCube({width / 2.0f + 0.5f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor);
}

void Arena::DrawCeiling() const {
    DrawCube({0.0f, height + 0.5f, 0.0f}, width, 1.0f, depth, ceilingColor);
}