#pragma once
#include "Game.h"
#include "raygui.h"

class UiPanel {
public:
    explicit UiPanel(Game& game, int screenWidth, int panelWidth);
    void Draw();

private:
    Game& game;
    int   screenWidth;
    int   panelWidth;
    int   panelX() const { return screenWidth - panelWidth; }
};