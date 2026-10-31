#include "HUD.h"

void HUD::Draw(Font font, const CrosshairConfig& cfg, int score, float accuracy, float timer, bool hitMarker) const {
    float cx = GetScreenWidth() / 2.0f;
    float cy = GetScreenHeight() / 2.0f;

    // --- ПРИЦЕЛ ---
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

    const char* strTime = TextFormat("%02d:%02d", mins, secs);
    const char* strScore = TextFormat("%d", score);
    const char* strAcc = TextFormat("%.1f%%", accuracy); // Теперь с дробной частью, так как трекинг точнее

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