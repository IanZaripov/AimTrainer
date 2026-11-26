#include "ScreenManager.h"
#include "UITheme.h"
#include "raygui.h"
#include "Audio.h"
#include "UIWidgets.h"

#include "RoutinesScreen.h"
#include "MouseSettingsScreen.h"
#include "CrosshairSettingsScreen.h"
#include "ArenaSettingsScreen.h"
#include "AudioSettingsScreen.h"
#include "GameplayScreen.h"
#include "ResultsScreen.h"
#include "LanguageSettingsScreen.h"
#include "Localization.h"

ScreenManager::ScreenManager() : session(settings) {
    settings.Load();
    Loc::Init();
    Loc::SetLanguage(settings.language);
    Audio::UpdateVolumes(
        settings.audio.uiVolume, 
        settings.audio.arenaVolume, 
        settings.audio.popVolume
    );
    session.Init();
    currentScreenID = ScreenID::ROUTINES;
    currentScreen = std::make_unique<RoutinesScreen>();
}

void ScreenManager::GoTo(ScreenID id) {
    pendingScreenID = id;
    hasPendingScreen = true;
}

void ScreenManager::ApplyPendingScreenChange() {
    if (!hasPendingScreen) return;
    
    hasPendingScreen = false;
    currentScreenID = pendingScreenID;

    switch (currentScreenID) {
        case ScreenID::ROUTINES:           currentScreen = std::make_unique<RoutinesScreen>(); break;
        case ScreenID::SETTINGS_MOUSE:     currentScreen = std::make_unique<MouseSettingsScreen>(); break;
        case ScreenID::SETTINGS_CROSSHAIR: currentScreen = std::make_unique<CrosshairSettingsScreen>(); break;
        case ScreenID::SETTINGS_ARENA:     currentScreen = std::make_unique<ArenaSettingsScreen>(); break;
        case ScreenID::SETTINGS_AUDIO:     currentScreen = std::make_unique<AudioSettingsScreen>(); break;
        case ScreenID::SETTINGS_LANGUAGE:  currentScreen = std::make_unique<LanguageSettingsScreen>(); break;
        case ScreenID::PLAYING:            currentScreen = std::make_unique<GameplayScreen>(); break;
        case ScreenID::RESULTS:            currentScreen = std::make_unique<ResultsScreen>(); break;
    }
}

void ScreenManager::UpdateLogic() {
    ApplyPendingScreenChange();
    if (currentScreen) {
        currentScreen->Update(*this);
    }
    ApplyPendingScreenChange();
}

void ScreenManager::DrawUI(Font uiFont) {
    ApplyPendingScreenChange();
    ClearBackground(UITheme::BG);

    if (currentScreenID == ScreenID::PLAYING || currentScreenID == ScreenID::RESULTS) {
        currentScreen->Draw(uiFont, *this);
    } else {
        DrawTopBar(uiFont);
        currentScreen->Draw(uiFont, *this);
    }
}

void ScreenManager::DrawTopBar(Font uiFont) {
    DrawRectangle(0, 0, GetRenderWidth(), (int)UITheme::TopBar::Height, Color{ 16, 19, 24, 255 });
    DrawLine(0, (int)UITheme::TopBar::Height, GetRenderWidth(), (int)UITheme::TopBar::Height, UITheme::ACCENT);
    
    DrawRectangle(0, 0, 4, (int)UITheme::TopBar::Height, UITheme::ACCENT);

    if (UIWidgets::Button({ UITheme::TopBar::Nav1X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Trainings"), uiFont)) { Audio::PlayClick(); GoTo(ScreenID::ROUTINES); }
    if (UIWidgets::Button({ UITheme::TopBar::Nav2X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Arena"), uiFont))      { Audio::PlayClick(); GoTo(ScreenID::SETTINGS_ARENA); }
    if (UIWidgets::Button({ UITheme::TopBar::Nav3X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Mouse"), uiFont))       { Audio::PlayClick(); GoTo(ScreenID::SETTINGS_MOUSE); }
    if (UIWidgets::Button({ UITheme::TopBar::Nav4X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Crosshair"), uiFont))     { Audio::PlayClick(); GoTo(ScreenID::SETTINGS_CROSSHAIR); }
    if (UIWidgets::Button({ UITheme::TopBar::Nav5X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Audio"), uiFont))       { Audio::PlayClick(); GoTo(ScreenID::SETTINGS_AUDIO); }
    if (UIWidgets::Button({ UITheme::TopBar::Nav6X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Language"), uiFont))    { Audio::PlayClick(); GoTo(ScreenID::SETTINGS_LANGUAGE); }

    const char* title = "AIM TRAINER";
    float titleWidth = MeasureTextEx(uiFont, title, 24, 1).x;
    DrawTextEx(uiFont, title, { (GetRenderWidth() - titleWidth) / 2.0f, 18 }, 24, 1, WHITE);

    if (UIWidgets::Button({ UITheme::GetRightButtonX(), UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("EXIT"), uiFont)) shouldExit = true;
}