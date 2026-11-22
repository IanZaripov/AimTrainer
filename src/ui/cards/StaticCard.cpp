#include "TrainingCard.h"
#include "UITheme.h"
#include "Localization.h"

StaticCard::StaticCard(Rectangle r)
    : TrainingCard(r, GameMode::STATIC, Loc::T("Static"), Loc::T("Spawn after"), Loc::T("destruction")) {}

void StaticCard::DrawIcon(Vector2 center, const Settings& settings) const {
    DrawCircle(center.x, center.y, UITheme::Card::Layout::Icon::Radius, settings.arena.ballColor);
}