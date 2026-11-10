#include "TrainingCard.h"
#include "UITheme.h"

TimedCard::TimedCard(Rectangle r)
    : TrainingCard(r, GameMode::TIMED, "На время", nullptr, nullptr) {}

void TimedCard::Update(Settings& settings) {
    clickedDifficulty = false;
    float diffY = rect.y + UITheme::Card::DiffBtnY;

    // Кнопки сложности обрабатываем первыми
    for (int i = 0; i < 3; i++) {
        Rectangle btn = { rect.x + 15 + i * UITheme::Card::DiffBtnSpacing, diffY, 
                          UITheme::Card::DiffBtnW, UITheme::Card::DiffBtnH };
        if (CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            settings.arena.timedDifficulty = i;
            settings.Save();
            clickedDifficulty = true;
        }
    }

    // Клик по самой карточке — только если не кликнули по кнопке
    hovered = CheckCollisionPointRec(GetMousePosition(), rect);
    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !clickedDifficulty) {
        clicked = true;
    }
}

void TimedCard::Draw(Font font, const Settings& settings) const {
    DrawBase();
    Vector2 center = { rect.x + rect.width / 2.0f, rect.y + UITheme::Card::IconCenterY };
    DrawIcon(center, settings);
    DrawTextEx(font, title, { rect.x + 15, rect.y + UITheme::Card::TimedTitleY }, 20, 1, WHITE);
    DrawDifficultyButtons(font, settings);
}

void TimedCard::DrawIcon(Vector2 center, const Settings& settings) const {
    DrawCircle(center.x, center.y, UITheme::Card::IconRadius, settings.arena.ballColor);
    DrawCircleLines(center.x, center.y, UITheme::Card::IconRadius, WHITE);
    DrawLineEx({center.x, center.y}, {center.x, center.y - UITheme::Card::TimerHandLength}, 3.0f, WHITE);
}

void TimedCard::DrawDifficultyButtons(Font font, const Settings& settings) const {
    const char* diffNames[] = { "Легко", "Сред", "Сложно" };
    float diffY = rect.y + UITheme::Card::DiffBtnY;

    for (int i = 0; i < 3; i++) {
        Rectangle btn = { rect.x + 15 + i * UITheme::Card::DiffBtnSpacing, diffY, 
                          UITheme::Card::DiffBtnW, UITheme::Card::DiffBtnH };
        bool btnHover = CheckCollisionPointRec(GetMousePosition(), btn);
        DrawRectangleRec(btn, settings.arena.timedDifficulty == i ? UITheme::ACCENT : UITheme::BG);
        DrawRectangleLinesEx(btn, 1.0f, btnHover ? WHITE : UITheme::BORDER);
        float tw = MeasureTextEx(font, diffNames[i], 12, 1).x;
        DrawTextEx(font, diffNames[i], { btn.x + (btn.width - tw) / 2, btn.y + 5 }, 12, 1, WHITE);
    }
}