#pragma once
#include "raylib.h"

class Hands {
public:
    // Рисует руки в локальном пространстве
    void Draw() const;

private:
    void DrawPalm() const;
    void DrawThumb() const;
    void DrawSleeve() const;
};