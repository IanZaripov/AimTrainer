#pragma once
#include "raylib.h"

class Arena {
public:
    Arena();
    void Draw() const;

private:
    // Размеры комнаты (камера будет ровно в центре)
    const float width = 20.0f;
    const float depth = 40.0f; 
    const float height = 8.0f;
};