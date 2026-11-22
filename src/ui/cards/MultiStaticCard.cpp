#include "TrainingCard.h"
#include "UITheme.h"
#include "Localization.h"

MultiStaticCard::MultiStaticCard(Rectangle r)
    : TrainingCard(r, GameMode::MULTI_STATIC, Loc::T("Multi-target"), Loc::T("8 targets at once"), Loc::T("(Spray training)")) {}

void MultiStaticCard::DrawIcon(Vector2 center, const Settings& settings) const {
    Color c = settings.arena.ballColor;
    DrawCircle(center.x - 30, center.y - 20, 15, c);
    DrawCircle(center.x + 30, center.y - 20, 15, c);
    DrawCircle(center.x,      center.y + 20, 15, c);
    DrawCircle(center.x - 20, center.y + 60, 15, c);
    DrawCircle(center.x + 20, center.y + 60, 15, c);
}