#include "TrainingCard.h"
#include "UITheme.h"

MovingCard::MovingCard(Rectangle r)
    : TrainingCard(r, GameMode::MOVING, "Движущиеся", "Несколько шаров", "летают туда-сюда") {}

void MovingCard::DrawIcon(Vector2 center, const Settings& settings) const {
    Color c = settings.arena.ballColor;
    DrawCircle(center.x, center.y, UITheme::Card::Layout::Icon::Radius, c);
    
    DrawHorizontalArrows(center);
}