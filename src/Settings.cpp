#include "Settings.h"
#include <fstream>

void Settings::Load(const char* filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> mouse.valorantSens >> fovDegrees >> headRadius >> mouse.sensMultiplier;
        
        int out, dt, hm, r, g, b;
        file >> crosshair.length >> crosshair.thickness >> crosshair.gap >> out >> dt >> hm;
        crosshair.outline = (out != 0);
        crosshair.dot = (dt != 0);
        crosshair.hitmarker = (hm != 0);

        file >> r >> g >> b;
        crosshair.color = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };

        // Загружаем арену (дистанция, радиус, сложность, цвет)
        if (file >> arena.distance >> arena.targetRadius >> arena.timedDifficulty >> r >> g >> b) {
            arena.ballColor = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
        }

        if (mouse.sensMultiplier <= 0.0f || mouse.sensMultiplier > 10.0f) mouse.sensMultiplier = 3.15f;
        if (arena.targetRadius < 0.02f || arena.targetRadius > 2.0f) arena.targetRadius = 0.11f;
        if (arena.timedDifficulty < 0 || arena.timedDifficulty > 2) arena.timedDifficulty = 1;
    }
}

void Settings::Save(const char* filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << mouse.valorantSens << "\n" << fovDegrees << "\n" << headRadius << "\n" << mouse.sensMultiplier << "\n";
        file << crosshair.length << "\n" << crosshair.thickness << "\n" << crosshair.gap << "\n" 
             << crosshair.outline << "\n" << crosshair.dot << "\n" << crosshair.hitmarker << "\n";
        file << (int)crosshair.color.r << " " << (int)crosshair.color.g << " " << (int)crosshair.color.b << "\n";
        
        file << arena.distance << "\n" << arena.targetRadius << "\n" << arena.timedDifficulty << "\n";
        file << (int)arena.ballColor.r << " " << (int)arena.ballColor.g << " " << (int)arena.ballColor.b << "\n";
    }
}