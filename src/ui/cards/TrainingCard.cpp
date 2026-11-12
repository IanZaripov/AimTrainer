#include "TrainingCard.h"
#include "UITheme.h"

TrainingCard::TrainingCard(Rectangle r, GameMode m, const char* t, const char* s1, const char* s2)
    : rect(r), mode(m), title(t), sub1(s1), sub2(s2) {}

void TrainingCard::Update(Settings& settings) {
    (void)settings;
    hovered = CheckCollisionPointRec(GetMousePosition(), rect);
    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        clicked = true;
    }
}

void TrainingCard::Draw(Font font, const Settings& settings) const {
    DrawBase();
    Vector2 center = { rect.x + rect.width / 2.0f, rect.y + UITheme::Card::Layout::Icon::CenterY };
    DrawIcon(center, settings);
    DrawTitleBlock(font);
}

void TrainingCard::DrawBase() const {
    Color bg = hovered ? Color{ 30, 35, 45, 255 } : UITheme::PANEL;
    Color border = hovered ? UITheme::ACCENT : UITheme::BORDER;
    float thickness = hovered ? 2.0f : 1.0f;
    DrawRectangleRec(rect, bg);
    DrawRectangleLinesEx(rect, thickness, border);
}

void TrainingCard::DrawTitleBlock(Font font) const {
    DrawTextEx(font, title, { rect.x + 20, rect.y + UITheme::Card::Text::TitleY }, 20, 1, WHITE);
    if (sub1) DrawTextEx(font, sub1, { rect.x + 15, rect.y + UITheme::Card::Text::Subtitle1Y }, 12, 1, UITheme::TEXT_DIM);
    if (sub2) DrawTextEx(font, sub2, { rect.x + 15, rect.y + UITheme::Card::Text::Subtitle2Y }, 12, 1, UITheme::TEXT_DIM);
}

void TrainingCard::DrawHorizontalArrows(Vector2 center) const {
    float aX = UITheme::Card::Layout::Arrows::OffsetX;
    float aY = UITheme::Card::Layout::Arrows::OffsetY;
    float aS = UITheme::Card::Layout::Arrows::Size;
    DrawTriangle({center.x + aX, center.y}, {center.x + aX + aY, center.y - aS}, {center.x + aX + aY, center.y + aS}, WHITE);
    DrawTriangle({center.x - aX, center.y}, {center.x - aX - aY, center.y - aS}, {center.x - aX - aY, center.y + aS}, WHITE);
}

void TrainingCard::DrawVerticalArrows(Vector2 center) const {
    float aX = UITheme::Card::Layout::Arrows::OffsetX;
    float aY = UITheme::Card::Layout::Arrows::OffsetY;
    float aS = UITheme::Card::Layout::Arrows::Size;
    DrawTriangle({center.x, center.y - aX}, {center.x - aS, center.y - aX - aY}, {center.x + aS, center.y - aX - aY}, WHITE);
    DrawTriangle({center.x, center.y + aX}, {center.x - aS, center.y + aX + aY}, {center.x + aS, center.y + aX + aY}, WHITE);
}