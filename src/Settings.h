#pragma once

struct Settings {
    float valorantSens = 0.255f;
    float fovDegrees   = 103.0f;
    float headRadius   = 22.0f;

    void Load(const char* filename = "settings.cfg");
    void Save(const char* filename = "settings.cfg") const;
};