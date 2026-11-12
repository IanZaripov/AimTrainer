#include "GameplayScreen.h"
#include "ScreenManager.h"

void GameplayScreen::Update(ScreenManager& manager) {
    auto& session = manager.GetSession();
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
}