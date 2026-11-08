#include "Arena.h"

Arena::Arena() {}

// Теперь Draw() читается как оглавление
void Arena::Draw() const {
    DrawFloor();
    DrawWalls();
    DrawCeiling();
    DrawGrid();
    DrawNeonLines();
}

void Arena::DrawFloor() const {
    DrawCube({0.0f, -0.5f, 0.0f}, width, 1.0f, depth, floorColor);
}

void Arena::DrawWalls() const {
    DrawCube({0.0f, height / 2.0f, -depth / 2.0f}, width, height, 1.0f, wallColor); // Задняя
    DrawCube({0.0f, height / 2.0f, depth / 2.0f}, width, height, 1.0f, wallColor);  // Передняя
    DrawCube({-width / 2.0f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor); // Левая
    DrawCube({width / 2.0f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor);  // Правая
}

void Arena::DrawCeiling() const {
    DrawCube({0.0f, height, 0.0f}, width, 1.0f, depth, ceilingColor);
}

void Arena::DrawGrid() const {
    // Сетка (шаг 4 метра)
    for (int x = (int)-width/2; x <= width/2; x += 4) {
        DrawLine3D({(float)x, 0, -depth/2}, {(float)x, height, -depth/2}, gridColor);
        DrawLine3D({(float)x, 0, depth/2}, {(float)x, height, depth/2}, gridColor);
    }
    for (int y = 0; y <= height; y += 4) {
        DrawLine3D({-width/2, (float)y, -depth/2}, {width/2, (float)y, -depth/2}, gridColor);
        DrawLine3D({-width/2, (float)y, depth/2}, {width/2, (float)y, depth/2}, gridColor);
        DrawLine3D({-width/2, (float)y, -depth/2}, {-width/2, (float)y, depth/2}, gridColor);
        DrawLine3D({width/2, (float)y, -depth/2}, {width/2, (float)y, depth/2}, gridColor);
    }
    for (int z = (int)-depth/2; z <= depth/2; z += 4) {
        DrawLine3D({-width/2, 0, (float)z}, {-width/2, height, (float)z}, gridColor);
        DrawLine3D({width/2, 0, (float)z}, {width/2, height, (float)z}, gridColor);
    }
}

void Arena::DrawNeonLines() const {
    // Красные линии по периметру пола
    DrawLine3D({-width/2, 0.05f, -depth/2}, {width/2, 0.05f, -depth/2}, neonColor);
    DrawLine3D({-width/2, 0.05f, depth/2}, {width/2, 0.05f, depth/2}, neonColor);
    DrawLine3D({-width/2, 0.05f, -depth/2}, {-width/2, 0.05f, depth/2}, neonColor);
    DrawLine3D({width/2, 0.05f, -depth/2}, {width/2, 0.05f, depth/2}, neonColor);
}