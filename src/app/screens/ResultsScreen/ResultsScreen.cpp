#include "ResultsScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "raygui.h"
#include "Localization.h"
#include "UIWidgets.h"

void ResultsScreen::Draw(Font uiFont, ScreenManager& manager) {
    auto& session = manager.GetSession();
    Rectangle panelRect = GetPanelRect();

    DrawOverlay();
    DrawPanel(panelRect);
    DrawTitle(uiFont, panelRect);
    DrawStats(uiFont, panelRect, session);
    DrawButtons(uiFont, panelRect, manager, session);
}

Rectangle ResultsScreen::GetPanelRect() const {
    using namespace UITheme::Screens::Results;
    return { 
        (GetRenderWidth() - PanelWidth) / 2.0f, 
        (GetRenderHeight() - PanelHeight) / 2.0f, 
        PanelWidth, 
        PanelHeight 
    };
}

void ResultsScreen::DrawOverlay() const {
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), Fade(BLACK, 0.8f));
}

void ResultsScreen::DrawPanel(Rectangle panelRect) const {
    using namespace UITheme::Screens::Results;
    DrawRectangleRounded(panelRect, PanelRoundness, PanelSegments, UITheme::PANEL);
    DrawRectangleLinesEx(panelRect, PanelBorderThickness, UITheme::ACCENT);
}

void ResultsScreen::DrawTitle(Font uiFont, Rectangle panelRect) const {
    using namespace UITheme::Screens::Results;
    const char* title = Loc::T("RESULTS");
    float tw = MeasureTextEx(uiFont, title, TitleFontSize, 1).x;
    
    DrawTextEx(uiFont, title, { panelRect.x + (panelRect.width - tw) / 2.0f, panelRect.y + TitleYOffset }, TitleFontSize, 1, UITheme::ACCENT);
    DrawLineEx(
        { panelRect.x + SeparatorPaddingX, panelRect.y + SeparatorYOffset }, 
        { panelRect.x + panelRect.width - SeparatorPaddingX, panelRect.y + SeparatorYOffset }, 
        SeparatorThickness, 
        UITheme::BORDER
    );
}

void ResultsScreen::DrawStats(Font uiFont, Rectangle panelRect, const TrainingSession& session) const {
    using namespace UITheme::Screens::Results;
    float textY = panelRect.y + StatsStartY;
    float labelX = panelRect.x + StatLabelX;
    float valueX = panelRect.x + StatValueX;

    DrawTimeResult(uiFont, labelX, valueX, textY);
    textY += StatRowSpacing;

    DrawSpawnedResult(uiFont, labelX, valueX, textY, session);
    textY += StatRowSpacing;

    DrawPoppedResult(uiFont, labelX, valueX, textY, session);
    textY += StatRowSpacing;

    DrawAccuracyResult(uiFont, labelX, valueX, textY, session);
}

void ResultsScreen::DrawTimeResult(Font font, float labelX, float valueX, float y) const {
    DrawTextEx(font, Loc::T("Time:"), { labelX, y }, UITheme::Screens::Results::StatFontSize, 1, UITheme::TEXT);
    DrawTextEx(font, Loc::T("60 sec"), { valueX, y }, UITheme::Screens::Results::StatFontSize, 1, WHITE);
}

void ResultsScreen::DrawSpawnedResult(Font font, float labelX, float valueX, float y, const TrainingSession& session) const {
    DrawTextEx(font, Loc::T("Targets spawned:"), { labelX, y }, UITheme::Screens::Results::StatFontSize, 1, UITheme::TEXT);
    DrawTextEx(font, TextFormat("%d", session.GetData().GetSpawnedBalls()), { valueX, y }, UITheme::Screens::Results::StatFontSize, 1, WHITE);
}

void ResultsScreen::DrawPoppedResult(Font font, float labelX, float valueX, float y, const TrainingSession& session) const {
    DrawTextEx(font, Loc::T("Targets destroyed:"), { labelX, y }, UITheme::Screens::Results::StatFontSize, 1, UITheme::TEXT);
    DrawTextEx(font, TextFormat("%d", session.GetData().GetPoppedCount()), { valueX, y }, UITheme::Screens::Results::StatFontSize, 1, WHITE);
}

void ResultsScreen::DrawAccuracyResult(Font font, float labelX, float valueX, float y, const TrainingSession& session) const {
    float accuracy = session.GetCurrentAccuracy();
    
    DrawTextEx(font, Loc::T("Accuracy:"), { labelX, y }, UITheme::Screens::Results::StatFontSize, 1, UITheme::TEXT);
    DrawTextEx(font, TextFormat("%.1f%%", accuracy), { valueX, y }, UITheme::Screens::Results::StatFontSize, 1, WHITE);
}

void ResultsScreen::DrawButtons(Font uiFont, Rectangle panelRect, ScreenManager& manager, const TrainingSession& session) {
    using namespace UITheme::Screens::Results;
    
    if (UIWidgets::Button({ panelRect.x + Btn1X, panelRect.y + BtnY, BtnWidth, BtnHeight }, Loc::T("RESTART"), uiFont)) {
        auto& mutableSession = manager.GetSession();
        mutableSession.StartTraining(GameMode::TIMED);
        manager.GoTo(ScreenID::PLAYING);
    }
    if (UIWidgets::Button({ panelRect.x + Btn2X, panelRect.y + BtnY, BtnWidth, BtnHeight }, Loc::T("MAIN MENU"), uiFont)) {
        manager.GoTo(ScreenID::ROUTINES);
    }
}