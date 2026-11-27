#include "RoutinesScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "Settings.h"
#include "Audio.h"
#include "Localization.h"

RoutinesScreen::RoutinesScreen() {
    using namespace UITheme::Card::Grid;
    float x = X;
    cards.push_back(std::make_unique<StaticCard>(Rectangle{x, Y, Width, Height}));
    x += Width + Spacing;
    cards.push_back(std::make_unique<MovingCard>(Rectangle{x, Y, Width, Height}));
    x += Width + Spacing;
    cards.push_back(std::make_unique<BouncingCard>(Rectangle{x, Y, Width, Height}));
    x += Width + Spacing;
    cards.push_back(std::make_unique<TimedCard>(Rectangle{x, Y, Width, Height}));
    x += Width + Spacing;
    cards.push_back(std::make_unique<MultiStaticCard>(Rectangle{x, Y, Width, Height}));
}

void RoutinesScreen::Update(ScreenManager& manager) {
    GameCategory cat = manager.GetRoutineCategory();

    LayoutCards(cat);

    for (auto& card : cards) {
        if (IsModeAvailableIn(card->GetMode(), cat)) {
            card->Update(manager.GetSettings());
        }
    }

    HandleCardClicks(manager, cat);
}

void RoutinesScreen::Draw(Font uiFont, ScreenManager& manager) {
    GameCategory cat = manager.GetRoutineCategory();
    DrawCategoryTabs(uiFont, manager);
    DrawTitle(uiFont);
    DrawCards(uiFont, manager.GetSettings(), cat);
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
        if (!IsModeAvailableIn(card->GetMode(), cat)){
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

void RoutinesScreen::DrawCategoryTabs(Font uiFont, ScreenManager& manager) {
    using namespace UITheme::CategoryTab;
    GameCategory active = manager.GetRoutineCategory();

    struct Tab { GameCategory category; const char* labelKey; };
    const Tab tabs[] = {
        { GameCategory::NORMAL,      "NORMAL"      },
        { GameCategory::COMPETITIVE, "COMPETITIVE" }
    };

    for (int i = 0; i < 2; i++) {
        Rectangle rect = { StartX + i * (Width + Spacing), Y, Width, Height };
        bool isActive = (active == tabs[i].category);
        bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);

        if (hovered && !isActive) {
            DrawRectangleRec(rect, Color{ 35, 42, 50, 255 });
        }

        const char* label = Loc::T(tabs[i].labelKey);
        Vector2 size = MeasureTextEx(uiFont, label, FontSize, 1);
        float textX = rect.x + (rect.width - size.x) / 2.0f;
        float textY = rect.y + (rect.height - size.y) / 2.0f;
        Color textColor = isActive ? WHITE : UITheme::TEXT_DIM;
        DrawTextEx(uiFont, label, { textX, textY }, FontSize, 1, textColor);

        if (isActive) {
            DrawRectangle(
                (int)rect.x,
                (int)(rect.y + rect.height + UnderlineOffset),
                (int)rect.width,
                (int)UnderlineThickness,
                UITheme::ACCENT
            );
        }

        if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isActive) {
            Audio::PlayClick();
            manager.SetRoutineCategory(tabs[i].category);
        }
    }
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