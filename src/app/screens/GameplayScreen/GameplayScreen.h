#pragma once
#include "IScreen.h"

class GameplayScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override;
    void Draw(Font uiFont, ScreenManager& manager) override;

private:
    bool isPaused = false;

    void DrawPauseMenu(Font uiFont, ScreenManager& manager);
};