#pragma once
#include "raylib.h"
#include <fstream>
#include "Localization.h"

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
    float targetRadius = 0.30f; 
    int   timedDifficulty = 1;
};

struct AudioConfig {
    float uiVolume = 0.5f;
    float popVolume   = 0.5f;
    float arenaVolume = 0.5f;
};

class Settings {
private:
    // Load methods
    void LoadMouse(std::ifstream& file);
    void LoadCrosshair(std::ifstream& file);
    void LoadArena(std::ifstream& file);
    void LoadAudio(std::ifstream& file);
    
    // Save methods
    void SaveMouse(std::ofstream& file) const;
    void SaveCrosshair(std::ofstream& file) const;
    void SaveArena(std::ofstream& file) const;
    void SaveAudio(std::ofstream& file) const;

    // Validation
    void Sanitize();
public:
    MouseConfig     mouse;
    CrosshairConfig crosshair;
    TargetConfig    arena;
    AudioConfig     audio;
    Language language = Language::ENGLISH;
    
    float fovDegrees = 103.0f;
    float headRadius = 0.11f; 

    void Load(const char* filename = "settings.cfg");
    void Save(const char* filename = "settings.cfg") const;
};