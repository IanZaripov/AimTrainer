#pragma once
#include "IScreen.h"

class Settings;

class LanguageSettingsScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override;
    void Draw(Font uiFont, ScreenManager& manager) override;

private:
    bool isDirty = false;
    void DrawTitle(Font uiFont) const;
    void DrawOptions(Font uiFont, Settings& settings);
};