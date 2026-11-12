#pragma once
#include "IScreen.h"

class MouseSettingsScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override {}
    void Draw(Font uiFont, ScreenManager& manager) override;
private:
    char sensBuffer[16] = "0.255";
    bool sensEditMode = false;
    char multBuffer[16] = "3.15";
    bool multEditMode = false;
};