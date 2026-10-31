#include "Arena.h"

Arena::Arena() {}

void Arena::Draw() const {
    DrawFloor();
    DrawWalls();
    DrawCeiling();
}

void Arena::DrawFloor() const {
    // Сплошной куб, верхняя грань которого на уровне Y=0
    DrawCube({0.0f, -0.5f, 0.0f}, width, 1.0f, depth, Color{ 50, 55, 60, 255 });
    // Сетка (чуть выше пола, чтобы не было мерцания)
    DrawGrid(50, 1.0f); 
}

void Arena::DrawWalls() const {
    Color wallColor = Color{ 40, 45, 55, 255 };
    
    // Задняя
    DrawCube({0.0f, height / 2.0f, -depth / 2.0f - 0.5f}, width, height, 1.0f, wallColor);
    // Передняя (за спиной)
    DrawCube({0.0f, height / 2.0f, depth / 2.0f + 0.5f}, width, height, 1.0f, wallColor);
    // Левая
    DrawCube({-width / 2.0f - 0.5f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor);
    // Правая
    DrawCube({width / 2.0f + 0.5f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor);
    
    // Неоновые линии по краям (стиль Valorant)
    Color neon = Color{ 0, 180, 255, 255 };
    DrawLine3D({-width/2, 0.01f, -depth/2}, {width/2, 0.01f, -depth/2}, neon);
    DrawLine3D({-width/2, 0.01f, -depth/2}, {-width/2, 0.01f, depth/2}, neon);
    DrawLine3D({width/2, 0.01f, -depth/2}, {width/2, 0.01f, depth/2}, neon);
}

void Arena::DrawCeiling() const {
    DrawCube({0.0f, height + 0.5f, 0.0f}, width, 1.0f, depth, Color{ 30, 35, 40, 255 });
}