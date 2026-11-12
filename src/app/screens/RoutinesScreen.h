#pragma once
#include "IScreen.h"
#include "TrainingCard.h"
#include <vector>
#include <memory>

class RoutinesScreen : public IScreen {
public:
    RoutinesScreen();
    void Update(ScreenManager& manager) override;
    void Draw(Font uiFont, ScreenManager& manager) override;
private:
    std::vector<std::unique_ptr<TrainingCard>> cards;
};