#include "GameplayScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "raygui.h"
#include "Audio.h"

void GameplayScreen::Update(ScreenManager& manager) {
    auto& session = manager.GetSession();

    if (isPaused) {
        return;
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        isPaused = true;
        EnableCursor();
        return;
    }

    session.Update();

    if (!session.IsTrainingActive()) {
        if (session.GetExitReason() == GameExitReason::TimeExpired) {
            manager.GoTo(ScreenID::RESULTS);
        } else {
            manager.GoTo(ScreenID::ROUTINES);
        }
    }
}
    
void GameplayScreen::Draw(Font uiFont, ScreenManager& manager) {
    manager.GetSession().Draw(uiFont);

    if (isPaused) {
        DrawPauseMenu(uiFont, manager);
    }
}

// --- Pause Menu Logic ---

void GameplayScreen::DrawPauseMenu(Font uiFont, ScreenManager& manager) {
    Rectangle panelRect = GetPausePanelRect();
    auto& session = manager.GetSession();

    DrawPauseOverlay();
    DrawPausePanel(panelRect);
    DrawPauseHeader(uiFont, panelRect);
    DrawPauseStats(uiFont, panelRect, session);
    DrawPauseButtons(uiFont, panelRect, manager);
}

Rectangle GameplayScreen::GetPausePanelRect() const {
    using namespace UITheme::PauseMenu;
    return { 
        GetRenderWidth() / 2.0f - PanelWidth / 2.0f, 
        GetRenderHeight() / 2.0f - PanelHeight / 2.0f, 
        PanelWidth, 
        PanelHeight 
    };
}

void GameplayScreen::DrawPauseOverlay() const {
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), Fade(BLACK, 0.7f));
}

void GameplayScreen::DrawPausePanel(Rectangle panelRect) const {
    using namespace UITheme::PauseMenu;
    DrawRectangleRounded(panelRect, PanelRoundness, PanelSegments, UITheme::PANEL);
    DrawRectangleLinesEx(panelRect, PanelBorderThickness, UITheme::ACCENT);
}

void GameplayScreen::DrawPauseHeader(Font uiFont, Rectangle panelRect) const {
    using namespace UITheme::PauseMenu;
    const char* title = "ПАУЗА";
    float tw = MeasureTextEx(uiFont, title, HeaderFontSize, 1).x;
    
    DrawTextEx(uiFont, title, { panelRect.x + (panelRect.width - tw) / 2.0f, panelRect.y + HeaderYOffset }, HeaderFontSize, 1, UITheme::ACCENT);
    DrawLineEx(
        { panelRect.x + SeparatorPaddingX, panelRect.y + SeparatorYOffset }, 
        { panelRect.x + panelRect.width - SeparatorPaddingX, panelRect.y + SeparatorYOffset }, 
        SeparatorThickness, 
        UITheme::BORDER
    );
}

void GameplayScreen::DrawPauseStats(Font uiFont, Rectangle panelRect, const TrainingSession& session) const {
    using namespace UITheme::PauseMenu;
    
    float textY = panelRect.y + StatsStartYOffset;
    float labelX = panelRect.x + StatsLabelXOffset;
    float valueX = panelRect.x + panelRect.width - StatsValueXOffset;

    auto DrawStatRow = [&](const char* label, const char* value) {
        DrawTextEx(uiFont, label, { labelX, textY }, StatsFontSize, 1, UITheme::TEXT);
        float valW = MeasureTextEx(uiFont, value, StatsFontSize, 1).x;
        DrawTextEx(uiFont, value, { valueX - valW, textY }, StatsFontSize, 1, WHITE);
        textY += StatsRowSpacing;
    };

    DrawStatRow("Время:", TextFormat("%.1f сек", session.GetSessionTime()));
    DrawStatRow("Счет:", TextFormat("%d", session.GetPoppedCount()));
    DrawStatRow("Точность:", TextFormat("%.1f%%", session.GetCurrentAccuracy()));
}

void GameplayScreen::DrawPauseButtons(Font uiFont, Rectangle panelRect, ScreenManager& manager) {
    using namespace UITheme::PauseMenu;
    auto& session = manager.GetSession();

    float btnX = panelRect.x + panelRect.width / 2.0f - BtnWidth / 2.0f;
    float btnY = panelRect.y + BtnStartYOffset;

    if (GuiButton({ btnX, btnY, BtnWidth, BtnHeight }, "ПРОДОЛЖИТЬ")) {
        Audio::PlayClick();
        isPaused = false;
        DisableCursor();
    }
    if (GuiButton({ btnX, btnY + BtnHeight + BtnSpacing, BtnWidth, BtnHeight }, "ЗАНОВО")) {
        Audio::PlayClick();
        isPaused = false;
        session.StartTraining(session.GetCurrentMode());
        DisableCursor();
    }
    if (GuiButton({ btnX, btnY + (BtnHeight + BtnSpacing) * 2.0f, BtnWidth, BtnHeight }, "В МЕНЮ")) {
        Audio::PlayClick();
        isPaused = false;
        session.EndSession(GameExitReason::UserQuit);
    }
}