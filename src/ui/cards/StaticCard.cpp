#include "TrainingCard.h"
#include "UITheme.h"

StaticCard::StaticCard(Rectangle r)
    : TrainingCard(r, GameMode::STATIC, "Статичные", "Появляются после", "уничтожения") {}

void StaticCard::DrawIcon(Vector2 center, const Settings& settings) const {
    DrawCircle(center.x, center.y, UITheme::Card::IconRadius, settings.arena.ballColor);
}