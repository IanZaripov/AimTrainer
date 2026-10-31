#include "Settings.h"
#include <fstream>

void Settings::Load(const char* filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> mouse.valorantSens >> fovDegrees >> headRadius >> mouse.sensMultiplier;
        
        int r, g, b;
        file >> crosshair.length >> crosshair.thickness >> crosshair.gap 
             >> crosshair.outline >> crosshair.dot >> crosshair.hitmarker;
        file >> r >> g >> b;
        crosshair.color = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };

        if (headRadius > 1.0f) headRadius = 0.4f;
        if (mouse.sensMultiplier <= 0.0f) mouse.sensMultiplier = 1.0f;
    }
}

void Settings::Save(const char* filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << mouse.valorantSens << "\n" << fovDegrees << "\n" << headRadius << "\n" << mouse.sensMultiplier << "\n";
        file << crosshair.length << "\n" << crosshair.thickness << "\n" << crosshair.gap << "\n" 
             << crosshair.outline << "\n" << crosshair.dot << "\n" << crosshair.hitmarker << "\n";
        file << (int)crosshair.color.r << " " << (int)crosshair.color.g << " " << (int)crosshair.color.b << "\n";
    }
}