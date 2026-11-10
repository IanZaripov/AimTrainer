#include "TrainingCard.h"
#include "UITheme.h"

MultiStaticCard::MultiStaticCard(Rectangle r)
    : TrainingCard(r, GameMode::MULTI_STATIC, "Мульти-цель", "8 шаров одновременно", "(Тренировка спрея)") {}

void MultiStaticCard::DrawIcon(Vector2 center, const Settings& settings) const {
    Color c = settings.arena.ballColor;
    DrawCircle(center.x - 30, center.y - 20, 15, c);
    DrawCircle(center.x + 30, center.y - 20, 15, c);
    DrawCircle(center.x,      center.y + 20, 15, c);
    DrawCircle(center.x - 20, center.y + 60, 15, c);
    DrawCircle(center.x + 20, center.y + 60, 15, c);
}