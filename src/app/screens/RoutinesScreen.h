#pragma once
#include "IScreen.h"
#include "TrainingCard.h"
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

    void DrawTitle(Font uiFont) const;
    void DrawCards(Font uiFont, const Settings& settings) const;
};