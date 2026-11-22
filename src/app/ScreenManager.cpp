#include "ScreenManager.h"
#include "UITheme.h"
#include "raygui.h"
#include "Audio.h"

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
    DrawRectangle(0, 0, GetRenderWidth(), (int)UITheme::TopBar::Height, Color{ 20, 25, 30, 255 });
    DrawLine(0, (int)UITheme::TopBar::Height, GetRenderWidth(), (int)UITheme::TopBar::Height, UITheme::ACCENT);

    if (GuiButton({ UITheme::TopBar::Nav1X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Trainings"))) { 
        Audio::PlayClick(); GoTo(ScreenID::ROUTINES); 
    }
    if (GuiButton({ UITheme::TopBar::Nav2X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Arena"))) {
        Audio::PlayClick(); GoTo(ScreenID::SETTINGS_ARENA);
    }
    if (GuiButton({ UITheme::TopBar::Nav3X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Mouse"))) { 
        Audio::PlayClick(); GoTo(ScreenID::SETTINGS_MOUSE); 
    }
    if (GuiButton({ UITheme::TopBar::Nav4X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Crosshair"))) {
        Audio::PlayClick(); GoTo(ScreenID::SETTINGS_CROSSHAIR);
    }
    if (GuiButton({ UITheme::TopBar::Nav5X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Audio"))) {
        Audio::PlayClick(); GoTo(ScreenID::SETTINGS_AUDIO); 
    }
    if (GuiButton({ UITheme::TopBar::Nav6X, UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("Language"))) { 
        Audio::PlayClick(); GoTo(ScreenID::SETTINGS_LANGUAGE);
    }
    if (GuiButton({ UITheme::GetRightButtonX(), UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, Loc::T("EXIT"))){
        shouldExit = true;
    }
    const char* title = "AIM TRAINER";
    float titleWidth = MeasureTextEx(uiFont, title, 24, 1).x;
    DrawTextEx(uiFont, title, { (GetRenderWidth() - titleWidth) / 2.0f, 18 }, 24, 1, WHITE);

    if (GuiButton({ UITheme::GetRightButtonX(), UITheme::TopBar::ButtonY, UITheme::TopBar::ButtonW, UITheme::TopBar::ButtonH }, "ВЫХОД")) shouldExit = true;
}