#pragma once
#include "IScreen.h"

class ArenaSettingsScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override {}
    void Draw(Font uiFont, ScreenManager& manager) override;
private:
    char distBuffer[16] = "15";
    bool distEdit = false;
    char sizeBuffer[16] = "0.11";
    bool sizeEdit = false;
};