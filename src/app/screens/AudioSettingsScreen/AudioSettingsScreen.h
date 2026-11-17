#pragma once
#include "IScreen.h"

class Settings;

class AudioSettingsScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override;
    void Draw(Font uiFont, ScreenManager& manager) override;

private:
    bool isDirty = false;
    char uiBuffer[16] = "0.50";
    bool uiEdit = false;
    char popBuffer[16] = "0.50";
    bool popEdit = false;
    char arenaBuffer[16] = "0.50";
    bool arenaEdit = false;

    void DrawTitle(Font uiFont) const;
    bool DrawUIGroup(Font uiFont, Settings& settings);
    bool DrawPopGroup(Font uiFont, Settings& settings);
    bool DrawArenaGroup(Font uiFont, Settings& settings);
};