#pragma once
#include "raylib.h"
#include "Localization.h"
#include "json.hpp"

struct MouseConfig {
    float valorantSens = 0.520f; 
    float sensMultiplier = 3.15f;
};

struct CrosshairConfig {
    Color color = { 255, 255, 255, 255 }; 
    float length = 4.0f;                
    float thickness = 2.0f;             
    float gap = 0.0f;                   
    bool  outline = false;               
    bool  dot = false;                   
};

struct TargetConfig {
    Color ballColor = { 0, 220, 255, 255 };
    float distance = 15.0f;
    float targetRadius = 0.20f; 
    int   timedDifficulty = 1;
};

struct AudioConfig {
    float uiVolume = 0.5f;
    float popVolume   = 0.5f;
    float arenaVolume = 0.5f;
};

class Settings {
private:
    using json = nlohmann::json;
    // Load methods
    void LoadGeneral(const json& j);
    void LoadMouse(const json& j);
    void LoadCrosshair(const json& j);
    void LoadArena(const json& j);
    void LoadAudio(const json& j);
    // Save methods
    void SaveGeneral(json& j) const;
    void SaveMouse(json& j) const;
    void SaveCrosshair(json& j) const;
    void SaveArena(json& j) const;
    void SaveAudio(json& j) const;
    //Validation
    void Sanitize();
public:
    MouseConfig     mouse;
    CrosshairConfig crosshair;
    TargetConfig    arena;
    AudioConfig     audio;
    Language language = Language::ENGLISH;
    
    float fovDegrees = 103.0f;
    float headRadius = 0.11f; 

    void Load(const char* filename = "settings.json");
    void Save(const char* filename = "settings.json") const;
};