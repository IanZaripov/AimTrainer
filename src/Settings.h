#pragma once
#include "raylib.h"

struct MouseConfig {
    float valorantSens = 0.255f; 
    float sensMultiplier = 1.0f;
};

struct CrosshairConfig {
    Color color = { 0, 255, 0, 255 };
    float length = 6.0f;
    float thickness = 2.0f;
    float gap = 4.0f;
    bool  outline = true;
    bool  dot = true;
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