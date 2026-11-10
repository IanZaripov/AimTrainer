#include "TrainingCard.h"
#include "UITheme.h"

MovingCard::MovingCard(Rectangle r)
    : TrainingCard(r, GameMode::MOVING, "Движущаяся", "Летает влево", "и вправо") {}

void MovingCard::DrawIcon(Vector2 center, const Settings& settings) const {
    DrawCircle(center.x, center.y, UITheme::Card::IconRadius, settings.arena.ballColor);
    DrawHorizontalArrows(center);
}