#include "MouseSettingsScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "UIWidgets.h"

void MouseSettingsScreen::Update(ScreenManager& manager) {
    if (isDirty) {
        manager.GetSettings().Save();
        isDirty = false;
    }
}

void MouseSettingsScreen::Draw(Font uiFont, ScreenManager& manager) {
    auto& settings = manager.GetSettings();

    DrawTitle(uiFont);
    
    isDirty |= DrawSensitivityGroup(uiFont, settings);
    isDirty |= DrawMultiplierGroup(uiFont, settings);
}

void MouseSettingsScreen::DrawTitle(Font uiFont) const {
    using namespace UITheme::Screens::Settings;
    DrawTextEx(uiFont, "НАСТРОЙКИ МЫШИ", { TitleX, TitleY }, TitleFontSize, 1, UITheme::ACCENT);
}

bool MouseSettingsScreen::DrawSensitivityGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, Mouse::SensGroupY, GroupWidth, Mouse::SensGroupH }, "СЕНСА (VALORANT)");
    return UIWidgets::DrawSliderBox(
        uiFont, Mouse::SensLabelX, Mouse::SensLabelY, 
        "Чувствительность", 
        &settings.mouse.valorantSens, 0.1f, 8.0f, 
        sensBuffer, &sensEditMode, false, 3
    );
}

bool MouseSettingsScreen::DrawMultiplierGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, Mouse::MultGroupY, GroupWidth, Mouse::MultGroupH }, "МНОЖИТЕЛЬ (ПОДГОНКА)");
    return UIWidgets::DrawSliderBox(
        uiFont, Mouse::MultLabelX, Mouse::MultLabelY, 
        "Множитель", 
        &settings.mouse.sensMultiplier, 0.5f, 5.0f, 
        multBuffer, &multEditMode
    );
}