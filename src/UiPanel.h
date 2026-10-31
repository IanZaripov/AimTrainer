#pragma once
#include "Game.h"
#include "Settings.h"
#include "raygui.h"

class UiPanel {
public:
    UiPanel(Game& game, Settings& settings);
    void Draw();

private:
    Game&     game;
    Settings& settings;
    
    int panelX() const { return GetScreenWidth() - settings.panelWidth; }
};