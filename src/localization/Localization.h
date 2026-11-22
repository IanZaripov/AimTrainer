#pragma once

enum class Language {
    ENGLISH,
    RUSSIAN
};

namespace Loc {
    void Init();
    void SetLanguage(Language lang);
    Language GetLanguage();
    
    // Returns translated string from dictionary, or the key itself if not found
    const char* T(const char* key);
}