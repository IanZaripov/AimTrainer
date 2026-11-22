#include "TrainingCard.h"
#include "UITheme.h"
#include "Localization.h"

BouncingCard::BouncingCard(Rectangle r)
    : TrainingCard(r, GameMode::BOUNCING, Loc::T("Bouncing"), Loc::T("Bounces off"), Loc::T("floor and walls")) {}

void BouncingCard::DrawIcon(Vector2 center, const Settings& settings) const {
    DrawCircle(center.x, center.y, UITheme::Card::Layout::Icon::Radius, settings.arena.ballColor);
    DrawHorizontalArrows(center);
    DrawVerticalArrows(center);
}