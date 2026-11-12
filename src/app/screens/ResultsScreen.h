#pragma once
#include "IScreen.h"

class TrainingSession;

class ResultsScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override {}
    void Draw(Font uiFont, ScreenManager& manager) override;

private:
    Rectangle GetPanelRect() const;
    void DrawOverlay() const;
    void DrawPanel(Rectangle panelRect) const;
    void DrawTitle(Font uiFont, Rectangle panelRect) const;
    
    void DrawStats(Font uiFont, Rectangle panelRect, const TrainingSession& session) const;
    
    void DrawTimeResult(Font font, float labelX, float valueX, float y) const;
    void DrawSpawnedResult(Font font, float labelX, float valueX, float y, const TrainingSession& session) const;
    void DrawPoppedResult(Font font, float labelX, float valueX, float y, const TrainingSession& session) const;
    void DrawAccuracyResult(Font font, float labelX, float valueX, float y, const TrainingSession& session) const;
    
    void DrawButtons(Font uiFont, Rectangle panelRect, ScreenManager& manager, const TrainingSession& session);
};