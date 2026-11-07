#include "Arena.h"

Arena::Arena() {}

void Arena::Draw() const {
    // Пыльно-голубая гамма в стиле Aim Lab (осветленная)
    Color floorColor   = Color{ 80, 95, 115, 255 };   // Светлее, без черноты
    Color wallColor    = Color{ 60, 75, 95, 255 };    // Базовый пыльно-голубой
    Color ceilingColor = Color{ 90, 105, 125, 255 };  // Светлый, не давит
    Color gridColor    = Color{ 100, 115, 135, 255 }; // Мягкая сетка
    Color neonColor    = Color{ 255, 70, 85, 255 };   // Красный акцент

    // 1. Пол
    DrawCube({0.0f, -0.5f, 0.0f}, width, 1.0f, depth, floorColor);

    // 2. Стены
    DrawCube({0.0f, height / 2.0f, -depth / 2.0f}, width, height, 1.0f, wallColor); // Задняя
    DrawCube({0.0f, height / 2.0f, depth / 2.0f}, width, height, 1.0f, wallColor);  // Передняя
    DrawCube({-width / 2.0f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor); // Левая
    DrawCube({width / 2.0f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor);  // Правая

    // 3. Потолок
    DrawCube({0.0f, height, 0.0f}, width, 1.0f, depth, ceilingColor);

    // 4. Сетка (шаг 4 метра)
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

    // 5. Красные линии по периметру пола
    DrawLine3D({-width/2, 0.05f, -depth/2}, {width/2, 0.05f, -depth/2}, neonColor);
    DrawLine3D({-width/2, 0.05f, depth/2}, {width/2, 0.05f, depth/2}, neonColor);
    DrawLine3D({-width/2, 0.05f, -depth/2}, {-width/2, 0.05f, depth/2}, neonColor);
    DrawLine3D({width/2, 0.05f, -depth/2}, {width/2, 0.05f, depth/2}, neonColor);
}