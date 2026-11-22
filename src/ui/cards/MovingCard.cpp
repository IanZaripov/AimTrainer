#include "TrainingCard.h"
#include "UITheme.h"
#include "Localization.h"

MovingCard::MovingCard(Rectangle r)
    : TrainingCard(r, GameMode::MOVING, Loc::T("Moving"), Loc::T("Multiple targets"), Loc::T("flying around")) {}

void MovingCard::DrawIcon(Vector2 center, const Settings& settings) const {
    DrawCircle(center.x, center.y, UITheme::Card::Layout::Icon::Radius, settings.arena.ballColor);
    DrawHorizontalArrows(center);
}