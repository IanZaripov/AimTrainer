#pragma once
#include "raylib.h"
#include "Settings.h"

class HUD {
public:
    // Передаем только конфиг прицела
    void Draw(Font font, const CrosshairConfig& cfg, int score, int shots, int hits, float timer, bool hitMarker) const;
};