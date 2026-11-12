#include "RoutinesScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"

RoutinesScreen::RoutinesScreen() {
    using namespace UITheme::Card;
    float x = LayoutX;
    cards.push_back(std::make_unique<StaticCard>(Rectangle{x, LayoutY, LayoutWidth, LayoutHeight}));           x += LayoutWidth + LayoutSpacing;
    cards.push_back(std::make_unique<MovingCard>(Rectangle{x, LayoutY, LayoutWidth, LayoutHeight}));           x += LayoutWidth + LayoutSpacing;
    cards.push_back(std::make_unique<BouncingCard>(Rectangle{x, LayoutY, LayoutWidth, LayoutHeight}));         x += LayoutWidth + LayoutSpacing;
    cards.push_back(std::make_unique<TimedCard>(Rectangle{x, LayoutY, LayoutWidth, LayoutHeight}));            x += LayoutWidth + LayoutSpacing;
    cards.push_back(std::make_unique<MultiStaticCard>(Rectangle{x, LayoutY, LayoutWidth, LayoutHeight}));
}

void RoutinesScreen::Update(ScreenManager& manager) {
    auto& settings = manager.GetSettings();
    for (auto& card : cards) card->Update(settings);
    
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
    DrawTextEx(uiFont, "ВЫБЕРИТЕ РУТИНУ:", { 40, 100 }, 20, 1, UITheme::TEXT_DIM);
    for (auto& card : cards) {
        card->Draw(uiFont, manager.GetSettings());
    }
}