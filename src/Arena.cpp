#include "Arena.h"

Arena::Arena() {}

void Arena::Draw() const {
    DrawFloor();
    DrawWalls();
    DrawCeiling();
    DrawWallLines();
}

void Arena::DrawFloor() const {
    // Пол размером с арену
    DrawPlane({0.0f, 0.0f, 0.0f}, {width, depth}, floorColor);
    // Сетка для ориентации в пространстве
    DrawGrid(50, 1.0f); 
}

void Arena::DrawWalls() const {
    // Задняя стена (Z = -depth/2)
    DrawCube({0.0f, height / 2.0f, -depth / 2.0f}, width, height, 1.0f, wallColor); 
    // Левая стена (X = -width/2)
    DrawCube({-width / 2.0f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor); 
    // Правая стена (X = width/2)
    DrawCube({width / 2.0f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor); 
}

void Arena::DrawCeiling() const {
    DrawCube({0.0f, height, 0.0f}, width, 1.0f, depth, ceilingColor);
}

void Arena::DrawWallLines() const {
    DrawCubeWires({0.0f, height / 2.0f, -depth / 2.0f}, width, height, 1.0f, lineColor);
    DrawCubeWires({-width / 2.0f, height / 2.0f, 0.0f}, 1.0f, height, depth, lineColor);
    DrawCubeWires({width / 2.0f, height / 2.0f, 0.0f}, 1.0f, height, depth, lineColor);
}