#include "MouseSettingsScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "UIWidgets.h"

void MouseSettingsScreen::Draw(Font uiFont, ScreenManager& manager) {
    auto& settings = manager.GetSettings();
    DrawTextEx(uiFont, "НАСТРОЙКИ МЫШИ", { 40, 90 }, 24, 1, UITheme::ACCENT);

    UITheme::DrawTitledGroup(uiFont, { 40, 140, 350, 100 }, "СЕНСА (VALORANT)");
    UIWidgets::DrawSliderBox(uiFont, 60, 180, "Чувствительность", &settings.mouse.valorantSens, 0.1f, 8.0f, sensBuffer, &sensEditMode, false, 3);

    UITheme::DrawTitledGroup(uiFont, { 40, 260, 350, 100 }, "МНОЖИТЕЛЬ (ПОДГОНКА)");
    UIWidgets::DrawSliderBox(uiFont, 60, 300, "Множитель", &settings.mouse.sensMultiplier, 0.5f, 5.0f, multBuffer, &multEditMode);

    static float lastSaveTime = 0.0f;
    if (GetTime() - lastSaveTime > 2.0f) { settings.Save(); lastSaveTime = GetTime(); }
}