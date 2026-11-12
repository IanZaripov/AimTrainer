#include "ResultsScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "raygui.h"

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
    float pw = 500.0f;
    float ph = 450.0f;
    return { 
        (GetRenderWidth() - pw) / 2.0f, 
        (GetRenderHeight() - ph) / 2.0f, 
        pw, 
        ph 
    };
}

void ResultsScreen::DrawOverlay() const {
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), Fade(BLACK, 0.8f));
}

void ResultsScreen::DrawPanel(Rectangle panelRect) const {
    DrawRectangleRounded(panelRect, 0.05f, 4, UITheme::PANEL);
    DrawRectangleLinesEx(panelRect, 2.0f, UITheme::ACCENT);
}

void ResultsScreen::DrawTitle(Font uiFont, Rectangle panelRect) const {
    const char* title = "РЕЗУЛЬТАТЫ";
    float tw = MeasureTextEx(uiFont, title, 32, 1).x;
    
    DrawTextEx(uiFont, title, { panelRect.x + (panelRect.width - tw) / 2.0f, panelRect.y + 30 }, 32, 1, UITheme::ACCENT);
    DrawLineEx({panelRect.x + 20, panelRect.y + 80}, {panelRect.x + panelRect.width - 20, panelRect.y + 80}, 1.0f, UITheme::BORDER);
}

void ResultsScreen::DrawStats(Font uiFont, Rectangle panelRect, const TrainingSession& session) const {
    float textY = panelRect.y + 110;
    float labelX = panelRect.x + 50;
    float valueX = panelRect.x + 300;

    DrawTimeResult(uiFont, labelX, valueX, textY);
    textY += 40;

    DrawSpawnedResult(uiFont, labelX, valueX, textY, session);
    textY += 40;

    DrawPoppedResult(uiFont, labelX, valueX, textY, session);
    textY += 40;

    DrawAccuracyResult(uiFont, labelX, valueX, textY, session);
}

void ResultsScreen::DrawTimeResult(Font font, float labelX, float valueX, float y) const {
    DrawTextEx(font, "Время:", { labelX, y }, 20, 1, UITheme::TEXT);
    DrawTextEx(font, "60 сек", { valueX, y }, 20, 1, WHITE);
}

void ResultsScreen::DrawSpawnedResult(Font font, float labelX, float valueX, float y, const TrainingSession& session) const {
    DrawTextEx(font, "Сгенерировано шаров:", { labelX, y }, 20, 1, UITheme::TEXT);
    DrawTextEx(font, TextFormat("%d", session.GetSpawnedBalls()), { valueX, y }, 20, 1, WHITE);
}

void ResultsScreen::DrawPoppedResult(Font font, float labelX, float valueX, float y, const TrainingSession& session) const {
    DrawTextEx(font, "Уничтожено:", { labelX, y }, 20, 1, UITheme::TEXT);
    DrawTextEx(font, TextFormat("%d", session.GetPoppedCount()), { valueX, y }, 20, 1, WHITE);
}

void ResultsScreen::DrawAccuracyResult(Font font, float labelX, float valueX, float y, const TrainingSession& session) const {
    float accuracy = (session.GetSpawnedBalls() > 0) ? 100.0f * session.GetPoppedCount() / session.GetSpawnedBalls() : 0.0f;
    
    DrawTextEx(font, "Точность:", { labelX, y }, 20, 1, UITheme::TEXT);
    DrawTextEx(font, TextFormat("%.1f%%", accuracy), { valueX, y }, 20, 1, WHITE);
}

void ResultsScreen::DrawButtons(Font uiFont, Rectangle panelRect, ScreenManager& manager, const TrainingSession& session) {
    if (GuiButton({ panelRect.x + 50, panelRect.y + 350, 180, 40 }, "ЗАНОВО")) {
        auto& mutableSession = manager.GetSession();
        mutableSession.StartTraining(GameMode::TIMED);
        manager.GoTo(ScreenID::PLAYING);
    }
    if (GuiButton({ panelRect.x + 270, panelRect.y + 350, 180, 40 }, "В МЕНЮ")) {
        manager.GoTo(ScreenID::ROUTINES);
    }
}