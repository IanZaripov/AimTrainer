#include "HUD.h"

void HUD::Draw(Font font, const CrosshairConfig& cfg, int score, int shots, int hits, float timer, bool hitMarker) const {
    float cx = GetScreenWidth() / 2.0f;
    float cy = GetScreenHeight() / 2.0f;

    // --- ПРИЦЕЛ ---
    Color col = cfg.color;
    float len = cfg.length;
    float thic = cfg.thickness;
    float gap = cfg.gap;
    
    if (cfg.outline) {
        Color out = BLACK;
        float outThic = thic + 2.0f;
        DrawRectangle(cx - outThic/2, cy - gap - len - 1, outThic, len + 2, out);
        DrawRectangle(cx - outThic/2, cy + gap - 1, outThic, len + 2, out);
        DrawRectangle(cx - gap - len - 1, cy - outThic/2, len + 2, outThic, out);
        DrawRectangle(cx + gap - 1, cy - outThic/2, len + 2, outThic, out);
    }

    DrawRectangle(cx - thic/2, cy - gap - len, thic, len, col);
    DrawRectangle(cx - thic/2, cy + gap, thic, len, col);
    DrawRectangle(cx - gap - len, cy - thic/2, len, thic, col);
    DrawRectangle(cx + gap, cy - thic/2, len, thic, col);

    if (cfg.dot) {
        DrawRectangle(cx - thic/2, cy - thic/2, thic, thic, col);
    }

    // --- ХИТМАРКЕР ---
    if (hitMarker && cfg.hitmarker) {
        float s = 10.0f;
        DrawLineEx({cx - s, cy - s}, {cx + s, cy + s}, 2.0f, WHITE);
        DrawLineEx({cx + s, cy - s}, {cx - s, cy + s}, 2.0f, WHITE);
    }

    // --- ВЕРХНИЙ ТАБЛО ---
    float panelWidth = 500.0f;
    float panelHeight = 60.0f;
    float panelX = cx - panelWidth / 2.0f;
    float panelY = 20.0f;

    DrawRectangleRounded({ panelX, panelY, panelWidth, panelHeight }, 0.2f, 4, Fade(Color{ 20, 25, 30, 255 }, 0.85f));
    DrawRectangleRoundedLinesEx({ panelX, panelY, panelWidth, panelHeight }, 0.2f, 4, 2.0f, Color{ 0, 200, 255, 255 });

    int mins = (int)timer / 60;
    int secs = (int)timer % 60;
    float accuracy = (shots > 0) ? 100.0f * hits / shots : 0.0f;

    const char* strTime = TextFormat("%02d:%02d", mins, secs);
    const char* strScore = TextFormat("%d", score);
    const char* strAcc = TextFormat("%.0f%%", accuracy);

    float timeW = MeasureTextEx(font, strTime, 28, 1).x;
    float scoreW = MeasureTextEx(font, strScore, 28, 1).x;
    float accW = MeasureTextEx(font, strAcc, 28, 1).x;

    float timeX = panelX + (panelWidth * 0.25f) - timeW / 2.0f;
    float scoreX = panelX + (panelWidth * 0.50f) - scoreW / 2.0f;
    float accX = panelX + (panelWidth * 0.75f) - accW / 2.0f;

    float textY = panelY + 8.0f;
    
    DrawTextEx(font, strTime, { timeX, textY }, 28, 1, WHITE);
    DrawTextEx(font, strScore, { scoreX, textY }, 28, 1, Color{ 0, 200, 255, 255 });
    DrawTextEx(font, strAcc, { accX, textY }, 28, 1, WHITE);

    const char* lblTime = "ВРЕМЯ";
    const char* lblScore = "СЧЕТ";
    const char* lblAcc = "ТОЧНОСТЬ";

    float ltW = MeasureTextEx(font, lblTime, 10, 1).x;
    float lsW = MeasureTextEx(font, lblScore, 10, 1).x;
    float laW = MeasureTextEx(font, lblAcc, 10, 1).x;

    DrawTextEx(font, lblTime, { panelX + (panelWidth * 0.25f) - ltW / 2.0f, textY + 28 }, 10, 1, GRAY);
    DrawTextEx(font, lblScore, { panelX + (panelWidth * 0.50f) - lsW / 2.0f, textY + 28 }, 10, 1, GRAY);
    DrawTextEx(font, lblAcc, { panelX + (panelWidth * 0.75f) - laW / 2.0f, textY + 28 }, 10, 1, GRAY);
}