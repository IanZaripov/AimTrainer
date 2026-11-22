#include "AudioSettingsScreen.h"
#include "ScreenManager.h"
#include "UITheme.h"
#include "UIWidgets.h"
#include "Audio.h"
#include "Localization.h"

void AudioSettingsScreen::Update(ScreenManager& manager) {
    if (isDirty) {
        auto& settings = manager.GetSettings();
        settings.Save();
        Audio::UpdateVolumes(
            settings.audio.uiVolume, 
            settings.audio.arenaVolume, 
            settings.audio.popVolume
        );
        isDirty = false;
    }
}

void AudioSettingsScreen::Draw(Font uiFont, ScreenManager& manager) {
    auto& settings = manager.GetSettings();
    
    DrawTitle(uiFont);
    
    isDirty |= DrawUIGroup(uiFont, settings);
    isDirty |= DrawPopGroup(uiFont, settings);
    isDirty |= DrawArenaGroup(uiFont, settings);
}

void AudioSettingsScreen::DrawTitle(Font uiFont) const {
    using namespace UITheme::Screens::Settings;
    DrawTextEx(uiFont, Loc::T("AUDIO SETTINGS"), { TitleX, TitleY }, TitleFontSize, 1, UITheme::ACCENT);
}

bool AudioSettingsScreen::DrawUIGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, AudioSettings::UIGroupY, GroupWidth, AudioSettings::UIGroupH }, Loc::T("UI SOUNDS"));
    return UIWidgets::DrawSliderBox(
        uiFont, AudioSettings::UILabelX, AudioSettings::UILabelY, 
        Loc::T("UI Volume"), 
        &settings.audio.uiVolume, 0.0f, 1.0f, 
        uiBuffer, &uiEdit, false, 2
    );
}

bool AudioSettingsScreen::DrawPopGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, AudioSettings::PopGroupY, GroupWidth, AudioSettings::PopGroupH }, Loc::T("TARGET SOUNDS"));
    return UIWidgets::DrawSliderBox(
        uiFont, AudioSettings::PopLabelX, AudioSettings::PopLabelY, 
        Loc::T("Hit Volume"), 
        &settings.audio.popVolume, 0.0f, 1.0f, 
        popBuffer, &popEdit, false, 2
    );
}

bool AudioSettingsScreen::DrawArenaGroup(Font uiFont, Settings& settings) {
    using namespace UITheme::Screens::Settings;
    
    UITheme::DrawTitledGroup(uiFont, { GroupX, AudioSettings::ArenaGroupY, GroupWidth, AudioSettings::ArenaGroupH }, Loc::T("ARENA SOUNDS (MUSIC)"));
    return UIWidgets::DrawSliderBox(
        uiFont, AudioSettings::ArenaLabelX, AudioSettings::ArenaLabelY, 
        Loc::T("Arena Volume"), 
        &settings.audio.arenaVolume, 0.0f, 1.0f, 
        arenaBuffer, &arenaEdit, false, 2
    );
}