#pragma once
#include "IScreen.h"
#include "TrainingCard.h"
#include "GameMode.h"
#include <vector>
#include <memory>

class Settings;

class RoutinesScreen : public IScreen {
public:
    RoutinesScreen();
    void Update(ScreenManager& manager) override;
    void Draw(Font uiFont, ScreenManager& manager) override;

private:
    std::vector<std::unique_ptr<TrainingCard>> cards;

    // Card layout and clicks
    void LayoutCards(GameCategory cat);
    void HandleCardClicks(ScreenManager& manager, GameCategory cat);
    void DrawTitle(Font uiFont) const;
    void DrawCards(Font uiFont, const Settings& settings, GameCategory cat) const;

    // Category tabs
    void HandleCategoryTabInput(ScreenManager& manager);
    void DrawCategoryTabs(Font uiFont, ScreenManager& manager);
    void DrawCategoryTab(Font uiFont, int index, GameCategory active);
    void DrawTabLabel(Font uiFont, Rectangle rect, const char* label, bool isActive);
    void DrawActiveTabUnderline(Rectangle rect);
};