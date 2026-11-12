#include "RoutinesScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "Settings.h"

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
    auto& settings = manager.GetSettings();
    for (auto& card : cards) {
        card->Update(settings);
    }
    
    for (auto& card : cards) {
        if (card->WasClicked()) {
            manager.GetSession().StartTraining(card->GetMode());
            manager.GoTo(ScreenID::PLAYING);
            card->ResetClicked();
            break;
        }
    }
}

void RoutinesScreen::Draw(Font uiFont, ScreenManager& manager) {
    DrawTitle(uiFont);
    DrawCards(uiFont, manager.GetSettings());
}

void RoutinesScreen::DrawTitle(Font uiFont) const {
    DrawTextEx(uiFont, "ВЫБЕРИТЕ РУТИНУ:", { UITheme::Screens::Routines::TitleX, UITheme::Screens::Routines::TitleY }, 20, 1, UITheme::TEXT_DIM);
}

void RoutinesScreen::DrawCards(Font uiFont, const Settings& settings) const {
    for (const auto& card : cards) {
        card->Draw(uiFont, settings);
    }
}