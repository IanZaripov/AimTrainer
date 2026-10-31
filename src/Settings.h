#pragma once
#include "raylib.h"

struct MouseConfig {
    float valorantSens = 0.255f; 
    float sensMultiplier = 1.0f;
};

struct CrosshairConfig {
    Color color = { 0, 255, 255, 255 }; // Циан (c;5)
    float length = 4.0f;                // 0l;4
    float thickness = 1.0f;             // 0t;1
    float gap = 0.0f;                   // 0o;0
    bool  outline = true;               // o;1
    bool  dot = true;                   // d;1
    bool  hitmarker = true;
};

struct Settings {
    MouseConfig     mouse;
    CrosshairConfig crosshair;
    
    float fovDegrees = 103.0f;
    float headRadius = 0.4f;

    void Load(const char* filename = "settings.cfg");
    void Save(const char* filename = "settings.cfg") const;
};