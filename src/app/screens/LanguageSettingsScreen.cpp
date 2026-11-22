#include "LanguageSettingsScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "raygui.h"
#include "Localization.h"

void LanguageSettingsScreen::Update(ScreenManager& manager) {
    if (isDirty) {
        manager.GetSettings().Save();
        isDirty = false;
    }
}

void LanguageSettingsScreen::Draw(Font uiFont, ScreenManager& manager) {
    auto& settings = manager.GetSettings();
    
    DrawTitle(uiFont);
    DrawOptions(uiFont, settings);
}

void LanguageSettingsScreen::DrawTitle(Font uiFont) const {
    using namespace UITheme::Screens::Settings;
    DrawTextEx(uiFont, Loc::T("LANGUAGE SETTINGS"), { TitleX, TitleY }, TitleFontSize, 1, UITheme::ACCENT);
}

void LanguageSettingsScreen::DrawOptions(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, Mouse::SensGroupY, GroupWidth, Mouse::SensGroupH }, Loc::T("Select Language"));
    
    Rectangle btnEng = { Mouse::SensLabelX, Mouse::SensLabelY, 150, 40 };
    Rectangle btnRus = { Mouse::SensLabelX + 170, Mouse::SensLabelY, 150, 40 };

    bool isEng = (settings.language == Language::ENGLISH);
    bool isRus = (settings.language == Language::RUSSIAN);

    if (GuiButton(btnEng, "English")) {
        settings.language = Language::ENGLISH;
        Loc::SetLanguage(Language::ENGLISH);
        isDirty = true;
    }
    if (GuiButton(btnRus, "Russian")) {
        settings.language = Language::RUSSIAN;
        Loc::SetLanguage(Language::RUSSIAN);
        isDirty = true;
    }

    if (isEng) DrawRectangleLinesEx(btnEng, 2.0f, UITheme::ACCENT);
    if (isRus) DrawRectangleLinesEx(btnRus, 2.0f, UITheme::ACCENT);
}