#include <gtest/gtest.h>
#include "Localization.h"

TEST(Localization, EnglishReturnsKeyAsIs) {
    Loc::SetLanguage(Language::ENGLISH);
    EXPECT_STREQ(Loc::T("EXIT"), "EXIT");
}

TEST(Localization, MissingKeyFallsBackToKey) {
    Loc::SetLanguage(Language::RUSSIAN);
    EXPECT_STREQ(Loc::T("NonExistentKey12345"), "NonExistentKey12345");
}

TEST(Localization, SwitchLanguageChangesResult) {
    // Need Loc::Init() first
    Loc::Init();
    
    Loc::SetLanguage(Language::ENGLISH);
    std::string en = Loc::T("EXIT");
    
    Loc::SetLanguage(Language::RUSSIAN);
    std::string ru = Loc::T("EXIT");
    
    EXPECT_NE(en, ru) << "Translations should differ";
}