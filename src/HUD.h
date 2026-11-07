#pragma once
#include "raylib.h"
#include "Settings.h"

float GetCPULoad();

class HUD {
public:
    void Draw(Font font, const CrosshairConfig& cfg, int score, float accuracy, float timer) const;

private:
    void DrawCrosshair(const CrosshairConfig& cfg) const;
    void DrawTopPanel(Font font, int score, float accuracy, float timer) const;
    void DrawSystemStats(Font font) const;
};