#include "Localization.h"
#include "json.hpp"
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace Loc {
    using Dictionary = std::unordered_map<std::string, std::string>;
    
    static Language currentLang = Language::ENGLISH;
    static std::unordered_map<Language, Dictionary> translations;

    // Simple parser for JSON files
    static void LoadLanguageFile(const std::string& filename, Language lang) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to load language file: " << filename << std::endl;
            return;
        }

        try {
            json j;
            file >> j;
            
            for (auto& [key, value] : j.items()) {
                if (value.is_string()) {
                    translations[lang][key] = value.get<std::string>();
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "JSON parse error in " << filename << ": " << e.what() << std::endl;
        }
    }

    void Init() {
        LoadLanguageFile("assets/lang/en.json", Language::ENGLISH);
        LoadLanguageFile("assets/lang/ru.json", Language::RUSSIAN);
    }

    void SetLanguage(Language lang) {
        currentLang = lang;
    }

    Language GetLanguage() {
        return currentLang;
    }

    const char* T(const char* key) {
        if (currentLang == Language::ENGLISH) return key;
        
        auto itLang = translations.find(currentLang);
        if (itLang != translations.end()) {
            auto itKey = itLang->second.find(key);
            if (itKey != itLang->second.end()) {
                return itKey->second.c_str();
            }
        }
        return key;
    }
}