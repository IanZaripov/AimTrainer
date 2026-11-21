#pragma once
#include "IScreen.h"

class TrainingSession;

class GameplayScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override;
    void Draw(Font uiFont, ScreenManager& manager) override;

private:
    bool isPaused = false;

    void DrawPauseMenu(Font uiFont, ScreenManager& manager);
    void DrawPauseOverlay() const;
    void DrawPausePanel(Rectangle panelRect) const;
    void DrawPauseHeader(Font uiFont, Rectangle panelRect) const;
    void DrawPauseStats(Font uiFont, Rectangle panelRect, const TrainingSession& session) const;
    void DrawPauseButtons(Font uiFont, Rectangle panelRect, ScreenManager& manager);
    
    Rectangle GetPausePanelRect() const;
};