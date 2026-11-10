#pragma once
#include "raylib.h"
#include "Settings.h"
#include "SystemStats.h"

class HUD {
public:
    void UpdateStats();
    void Draw(Font font, const CrosshairConfig& cfg, int score, float accuracy, float timer) const;

private:
    SystemStats sysStats;

    void DrawCrosshair(const CrosshairConfig& cfg) const;
    void DrawTopPanel(Font font, int score, float accuracy, float timer) const;
    void DrawSystemStats(Font font) const;
    
    void DrawStatColumn(Font font, const char* value, const char* label, float centerX, float y) const;
    void DrawStatBox(Font font, const char* label, const char* value, float x, float y) const;
    void DrawStatFrame(Rectangle rect) const;
    void DrawCenteredText(Font font, const char* text, Rectangle rect, float fontSize, Color color) const;
};