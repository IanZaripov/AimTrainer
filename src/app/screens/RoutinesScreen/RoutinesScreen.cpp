#include "RoutinesScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "Settings.h"
#include "Audio.h"
#include "Localization.h"

namespace {
    struct CategoryTabInfo {
        GameCategory category;
        const char* labelKey;
    };

    const CategoryTabInfo kCategoryTabs[] = {
        { GameCategory::NORMAL,      "NORMAL"      },
        { GameCategory::COMPETITIVE, "COMPETITIVE" }
    };
    constexpr int kCategoryTabCount = sizeof(kCategoryTabs) / sizeof(kCategoryTabs[0]);

    Rectangle GetCategoryTabRect(int index) {
        using namespace UITheme::CategoryTab;
        return {
            StartX + index * (Width + Spacing),
            Y,
            Width,
            Height
        };
    }
}

RoutinesScreen::RoutinesScreen() {
    using namespace UITheme::Card::Grid;
    float x = X;
    cards.push_back(std::make_unique<StaticCard>(Rectangle{x, Y, Width, Height}));           x += Width + Spacing;
    cards.push_back(std::make_unique<MovingCard>(Rectangle{x, Y, Width, Height}));           x += Width + Spacing;
    cards.push_back(std::make_unique<BouncingCard>(Rectangle{x, Y, Width, Height}));         x += Width + Spacing;
    cards.push_back(std::make_unique<TimedCard>(Rectangle{x, Y, Width, Height}));            x += Width + Spacing;
    cards.push_back(std::make_unique<MultiStaticCard>(Rectangle{x, Y, Width, Height}));
}


void RoutinesScreen::Update(ScreenManager& manager) {
    HandleCategoryTabInput(manager);
    GameCategory cat = manager.GetRoutineCategory();
    LayoutCards(cat);
    for (auto& card : cards) {
        if (IsModeAvailableIn(card->GetMode(), cat)) {
            card->Update(manager.GetSettings());
        }
    }
    HandleCardClicks(manager, cat);
}

void RoutinesScreen::HandleCategoryTabInput(ScreenManager& manager) {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        return;
    }

    for (int i = 0; i < kCategoryTabCount; i++) {
        if (!CheckCollisionPointRec(GetMousePosition(), GetCategoryTabRect(i))) {
            continue;
        }
        // Already active — no-op
        if (manager.GetRoutineCategory() == kCategoryTabs[i].category) {
            return;
        }
        Audio::PlayClick();
        manager.SetRoutineCategory(kCategoryTabs[i].category);
        return;
    }
}

void RoutinesScreen::LayoutCards(GameCategory cat) {
    using namespace UITheme::Card::Grid;
    float x = X;
    for (auto& card : cards) {
        if (IsModeAvailableIn(card->GetMode(), cat)) {
            card->SetRect({ x, Y, Width, Height });
            x += Width + Spacing;
        }
    }
}

void RoutinesScreen::HandleCardClicks(ScreenManager& manager, GameCategory cat) {
    for (auto& card : cards) {
        if (!IsModeAvailableIn(card->GetMode(), cat)) {
            continue;
        }
        if (card->WasClicked()) {
            Audio::PlayClick();
            manager.GetSession().StartTraining(card->GetMode(), cat);
            manager.GoTo(ScreenID::PLAYING);
            card->ResetClicked();
            return;
        }
    }
}

void RoutinesScreen::Draw(Font uiFont, ScreenManager& manager) {
    GameCategory cat = manager.GetRoutineCategory();
    DrawCategoryTabs(uiFont, manager);
    DrawTitle(uiFont);
    DrawCards(uiFont, manager.GetSettings(), cat);
}

void RoutinesScreen::DrawCategoryTabs(Font uiFont, ScreenManager& manager) {
    GameCategory active = manager.GetRoutineCategory();
    for (int i = 0; i < kCategoryTabCount; i++) {
        DrawCategoryTab(uiFont, i, active);
    }
}

void RoutinesScreen::DrawCategoryTab(Font uiFont, int index, GameCategory active) {
    Rectangle rect = GetCategoryTabRect(index);
    bool isActive = (kCategoryTabs[index].category == active);
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), rect);
    if (isHovered && !isActive) {
        DrawRectangleRec(rect, UITheme::CategoryTab::HoverBg);
    }
    DrawTabLabel(uiFont, rect, Loc::T(kCategoryTabs[index].labelKey), isActive);
    if (isActive) {
        DrawActiveTabUnderline(rect);
    }
}

void RoutinesScreen::DrawTabLabel(Font uiFont, Rectangle rect, const char* label, bool isActive) {
    using namespace UITheme::CategoryTab;

    Vector2 size = MeasureTextEx(uiFont, label, FontSize, 1);
    Vector2 position = {
        rect.x + (rect.width - size.x) / 2.0f,
        rect.y + (rect.height - size.y) / 2.0f
    };

    Color textColor = isActive ? WHITE : UITheme::TEXT_DIM;
    DrawTextEx(uiFont, label, position, FontSize, 1, textColor);
}

void RoutinesScreen::DrawActiveTabUnderline(Rectangle rect) {
    using namespace UITheme::CategoryTab;
    DrawRectangle(
        (int)rect.x,
        (int)(rect.y + rect.height + UnderlineOffset),
        (int)rect.width,
        (int)UnderlineThickness,
        UITheme::ACCENT
    );
}

void RoutinesScreen::DrawTitle(Font uiFont) const {
    DrawTextEx(uiFont, Loc::T("SELECT ROUTINE:"),
        { UITheme::Screens::Routines::TitleX, UITheme::Screens::Routines::TitleY },
        20, 1, UITheme::TEXT_DIM);
}

void RoutinesScreen::DrawCards(Font uiFont, const Settings& settings, GameCategory cat) const {
    for (const auto& card : cards) {
        if (IsModeAvailableIn(card->GetMode(), cat)) {
            card->Draw(uiFont, settings);
        }
    }
}