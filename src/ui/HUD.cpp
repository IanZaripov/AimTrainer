#include "HUD.h"
#include "UITheme.h"
#include "Localization.h"
#include <cstdio>

void HUD::UpdateStats() {
    sysStats.Update(GetFrameTime());
}

void HUD::Draw(Font font, const CrosshairConfig& cfg, int score, float accuracy, float timer) const {
    DrawCrosshair(cfg);
    DrawTopPanel(font, score, accuracy, timer);
    DrawSystemStats(font);
}

void HUD::DrawCrosshair(const CrosshairConfig& cfg) const {
    float cx = GetRenderWidth() / 2.0f;
    float cy = GetRenderHeight() / 2.0f;

    Color col = cfg.color;
    float len = cfg.length;
    float thic = cfg.thickness;
    float gap = cfg.gap;
    
    if (cfg.outline) {
        Color out = BLACK;
        float oT = thic + 2.0f;
        float oL = len + 2.0f;
        DrawRectanglePro({cx, cy - gap - len/2.0f, oT, oL}, {oT/2.0f, oL/2.0f}, 0.0f, out);
        DrawRectanglePro({cx, cy + gap + len/2.0f, oT, oL}, {oT/2.0f, oL/2.0f}, 0.0f, out);
        DrawRectanglePro({cx - gap - len/2.0f, cy, oL, oT}, {oL/2.0f, oT/2.0f}, 0.0f, out);
        DrawRectanglePro({cx + gap + len/2.0f, cy, oL, oT}, {oL/2.0f, oT/2.0f}, 0.0f, out);
    }

    DrawRectanglePro({cx, cy - gap - len/2.0f, thic, len}, {thic/2.0f, len/2.0f}, 0.0f, col);
    DrawRectanglePro({cx, cy + gap + len/2.0f, thic, len}, {thic/2.0f, len/2.0f}, 0.0f, col);
    DrawRectanglePro({cx - gap - len/2.0f, cy, len, thic}, {len/2.0f, thic/2.0f}, 0.0f, col);
    DrawRectanglePro({cx + gap + len/2.0f, cy, len, thic}, {len/2.0f, thic/2.0f}, 0.0f, col);

    if (cfg.dot) {
        DrawRectanglePro({cx, cy, thic, thic}, {thic/2.0f, thic/2.0f}, 0.0f, col);
    }
}

void HUD::DrawTopPanel(Font font, int score, float accuracy, float timer) const {
    float panelWidth = 500.0f;
    float panelHeight = 60.0f;
    float panelX = GetRenderWidth() / 2.0f - panelWidth / 2.0f;
    float panelY = 20.0f;

    DrawRectangleRounded({ panelX, panelY, panelWidth, panelHeight }, 0.2f, 4, Fade(Color{ 20, 25, 30, 255 }, 0.85f));
    DrawRectangleRoundedLinesEx({ panelX, panelY, panelWidth, panelHeight }, 0.2f, 4, 2.0f, Color{ 255, 70, 85, 255 });

    int mins = (int)timer / 60;
    int secs = (int)timer % 60;
    float textY = panelY + 8.0f;

    DrawStatColumn(font, TextFormat("%02d:%02d", mins, secs), Loc::T("TIME"), panelX + (panelWidth * 0.25f), textY);
    DrawStatColumn(font, TextFormat("%d", score), Loc::T("SCORE"), panelX + (panelWidth * 0.50f), textY);
    DrawStatColumn(font, TextFormat("%.1f%%", accuracy), Loc::T("ACCURACY"), panelX + (panelWidth * 0.75f), textY);
}

void HUD::DrawStatColumn(Font font, const char* value, const char* label, float centerX, float y) const {
    float valW = MeasureTextEx(font, value, 28, 1).x;
    float lblW = MeasureTextEx(font, label, 10, 1).x;

    DrawTextEx(font, value, { centerX - valW / 2.0f, y }, 28, 1, WHITE);
    DrawTextEx(font, label, { centerX - lblW / 2.0f, y + 28 }, 10, 1, GRAY);
}

void HUD::DrawSystemStats(Font font) const {
    float currentX = 10.0f;
    float startY = 20.0f;

    DrawStatBox(font, "FPS", TextFormat("%d", GetFPS()), currentX, startY);
    currentX += 110.0f + 10.0f;
    
    DrawStatBox(font, "CPU", TextFormat("%.1f%%", sysStats.GetCPU()), currentX, startY);
    currentX += 110.0f + 10.0f;
    
    DrawStatBox(font, "GPU", TextFormat("%.1f%%", sysStats.GetGPU()), currentX, startY);
}

void HUD::DrawStatBox(Font font, const char* label, const char* value, float x, float y) const {
    Rectangle boxRect = { x, y, 110.0f, 30.0f };
    DrawRectangleRounded(boxRect, 0.2f, 4, Fade(Color{ 20, 25, 30, 255 }, 0.8f));
    DrawRectangleRoundedLinesEx(boxRect, 0.2f, 4, 1.5f, Color{ 255, 70, 85, 255 });

    char textBuffer[64];
    snprintf(textBuffer, sizeof(textBuffer), "%s: %s", label, value);
    
    Vector2 textSize = MeasureTextEx(font, textBuffer, 16, 1);
    float textX = boxRect.x + (boxRect.width - textSize.x) / 2.0f;
    float textY = boxRect.y + (boxRect.height - textSize.y) / 2.0f;
    DrawTextEx(font, textBuffer, { textX, textY }, 16, 1, WHITE);
}