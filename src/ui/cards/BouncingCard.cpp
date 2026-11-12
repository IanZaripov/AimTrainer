#include "TrainingCard.h"
#include "UITheme.h"

BouncingCard::BouncingCard(Rectangle r)
    : TrainingCard(r, GameMode::BOUNCING, "Прыгающая", "Отскакивает от", "пола и стен") {}

void BouncingCard::DrawIcon(Vector2 center, const Settings& settings) const {
    DrawCircle(center.x, center.y, UITheme::Card::Layout::Icon::Radius, settings.arena.ballColor);
    DrawHorizontalArrows(center);
    DrawVerticalArrows(center);
}