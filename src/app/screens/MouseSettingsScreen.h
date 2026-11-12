#pragma once
#include "IScreen.h"

class Settings;

class MouseSettingsScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override;
    void Draw(Font uiFont, ScreenManager& manager) override;

private:
    bool isDirty = false;
    char sensBuffer[16] = "0.255";
    bool sensEditMode = false;
    char multBuffer[16] = "3.15";
    bool multEditMode = false;

    void DrawTitle(Font uiFont) const;
    bool DrawSensitivityGroup(Font uiFont, Settings& settings);
    bool DrawMultiplierGroup(Font uiFont, Settings& settings);
};