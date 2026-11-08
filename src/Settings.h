#pragma once
#include "raylib.h"

struct MouseConfig {
    float valorantSens = 0.255f; 
    float sensMultiplier = 3.15f;
};

struct CrosshairConfig {
    Color color = { 0, 255, 255, 255 }; 
    float length = 4.0f;                
    float thickness = 1.0f;             
    float gap = 0.0f;                   
    bool  outline = true;               
    bool  dot = true;                   
};

struct TargetConfig {
    Color ballColor = { 0, 220, 255, 255 };
    float distance = 15.0f;
    float targetRadius = 0.11f; 
    int   timedDifficulty = 1;
};

struct Settings {
    MouseConfig     mouse;
    CrosshairConfig crosshair;
    TargetConfig    arena;
    
    float fovDegrees = 103.0f;
    float headRadius = 0.11f; 

    void Load(const char* filename = "settings.cfg");
    void Save(const char* filename = "settings.cfg") const;
};