#include "Arena.h"

Arena::Arena() {}

void Arena::Draw() const {
    Color floorColor = Color{ 45, 50, 60, 255 };
    Color wallColor  = Color{ 55, 60, 70, 255 };
    Color gridColor  = Color{ 75, 80, 90, 255 };
    Color neonColor  = Color{ 255, 70, 85, 255 };

    // 1. Пол (сплошной куб, БЕЗ сетки)
    DrawCube({0.0f, -0.5f, 0.0f}, width, 1.0f, depth, floorColor);

    // 2. Стены
    DrawCube({0.0f, height / 2.0f, -depth / 2.0f}, width, height, 1.0f, wallColor); // Задняя
    DrawCube({0.0f, height / 2.0f, depth / 2.0f}, width, height, 1.0f, wallColor);  // Передняя
    DrawCube({-width / 2.0f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor); // Левая
    DrawCube({width / 2.0f, height / 2.0f, 0.0f}, 1.0f, height, depth, wallColor);  // Правая

    // 3. Потолок
    DrawCube({0.0f, height, 0.0f}, width, 1.0f, depth, Color{ 30, 35, 45, 255 });

    // 4. Сетка ТОЛЬКО на стенах (чтобы видеть объем комнаты, но пол не отвлекал)
    for (int x = (int)-width/2; x <= width/2; x += 2) {
        DrawLine3D({(float)x, 0, -depth/2}, {(float)x, height, -depth/2}, gridColor);
        DrawLine3D({(float)x, 0, depth/2}, {(float)x, height, depth/2}, gridColor);
    }
    for (int y = 0; y <= height; y += 2) {
        DrawLine3D({-width/2, (float)y, -depth/2}, {width/2, (float)y, -depth/2}, gridColor);
        DrawLine3D({-width/2, (float)y, depth/2}, {width/2, (float)y, depth/2}, gridColor);
        DrawLine3D({-width/2, (float)y, -depth/2}, {-width/2, (float)y, depth/2}, gridColor);
        DrawLine3D({width/2, (float)y, -depth/2}, {width/2, (float)y, depth/2}, gridColor);
    }
    for (int z = (int)-depth/2; z <= depth/2; z += 2) {
        DrawLine3D({-width/2, 0, (float)z}, {-width/2, height, (float)z}, gridColor);
        DrawLine3D({width/2, 0, (float)z}, {width/2, height, (float)z}, gridColor);
    }

    // 5. Неоновые линии по периметру пола
    DrawLine3D({-width/2, 0.05f, -depth/2}, {width/2, 0.05f, -depth/2}, neonColor);
    DrawLine3D({-width/2, 0.05f, depth/2}, {width/2, 0.05f, depth/2}, neonColor);
    DrawLine3D({-width/2, 0.05f, -depth/2}, {-width/2, 0.05f, depth/2}, neonColor);
    DrawLine3D({width/2, 0.05f, -depth/2}, {width/2, 0.05f, depth/2}, neonColor);
}