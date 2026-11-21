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

    // Стандартное обновление игры
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

void GameplayScreen::DrawPauseMenu(Font uiFont, ScreenManager& manager) {
    auto& session = manager.GetSession();

    // 1. Затемняем экран
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), Fade(BLACK, 0.7f));

    // 2. Панель
    float pw = 400.0f;
    float ph = 360.0f;
    float px = GetRenderWidth() / 2.0f - pw / 2.0f;
    float py = GetRenderHeight() / 2.0f - ph / 2.0f;

    DrawRectangleRounded({ px, py, pw, ph }, 0.05f, 4, UITheme::PANEL);
    DrawRectangleLinesEx({ px, py, pw, ph }, 2.0f, UITheme::ACCENT);

    // 3. Заголовок
    const char* title = "ПАУЗА";
    float tw = MeasureTextEx(uiFont, title, 32, 1).x;
    DrawTextEx(uiFont, title, { px + (pw - tw) / 2.0f, py + 20.0f }, 32, 1, UITheme::ACCENT);
    DrawLineEx({ px + 20, py + 65 }, { px + pw - 20, py + 65 }, 1.0f, UITheme::BORDER);

    // 4. Статистика
    float textY = py + 85.0f;
    float labelX = px + 40.0f;
    float valueX = px + pw - 40.0f;

    auto DrawStatRow = [&](const char* label, const char* value) {
        DrawTextEx(uiFont, label, { labelX, textY }, 20, 1, UITheme::TEXT);
        float valW = MeasureTextEx(uiFont, value, 20, 1).x;
        DrawTextEx(uiFont, value, { valueX - valW, textY }, 20, 1, WHITE);
        textY += 35.0f;
    };

    DrawStatRow("Время:", TextFormat("%.1f сек", session.GetSessionTime()));
    DrawStatRow("Счет:", TextFormat("%d", session.GetPoppedCount()));
    DrawStatRow("Точность:", TextFormat("%.1f%%", session.GetCurrentAccuracy()));

    // 5. Кнопки
    float btnW = 300.0f;
    float btnX = px + pw / 2.0f - btnW / 2.0f;
    float btnY = py + 200.0f;

    if (GuiButton({ btnX, btnY, btnW, 40.0f }, "ПРОДОЛЖИТЬ")) {
        Audio::PlayClick();
        isPaused = false;
        DisableCursor();
    }
    if (GuiButton({ btnX, btnY + 50.0f, btnW, 40.0f }, "ЗАНОВО")) {
        Audio::PlayClick();
        isPaused = false;
        session.StartTraining(session.GetCurrentMode());
        DisableCursor();
    }
    if (GuiButton({ btnX, btnY + 100.0f, btnW, 40.0f }, "В МЕНЮ")) {
        Audio::PlayClick();
        isPaused = false;
        session.EndSession(GameExitReason::UserQuit);
        // Следующий кадр Update увидит, что сессия неактивна, и переключит на меню
    }
}