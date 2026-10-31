#pragma once
#include "raylib.h"
#include "Settings.h"

class HUD {
public:
    void Draw(Font font, const CrosshairConfig& cfg, int score, float accuracy, float timer, bool hitMarker) const;
};