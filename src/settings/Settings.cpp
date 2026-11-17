#include "Settings.h"

void Settings::Load(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()){
        return;
    }

    LoadMouse(file);
    LoadCrosshair(file);
    LoadArena(file);
    LoadAudio(file);

    Sanitize();
}

void Settings::Save(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()){
        return;
    }

    SaveMouse(file);
    SaveCrosshair(file);
    SaveArena(file);
    SaveAudio(file);
}

// ==========================================
// LOAD METHODS
// ==========================================

void Settings::LoadMouse(std::ifstream& file) {
    file >> mouse.valorantSens >> fovDegrees >> headRadius >> mouse.sensMultiplier;
}

void Settings::LoadCrosshair(std::ifstream& file) {
    int out, dt, r, g, b;
    file >> crosshair.length >> crosshair.thickness >> crosshair.gap >> out >> dt;
    crosshair.outline = (out != 0);
    crosshair.dot = (dt != 0);

    file >> r >> g >> b;
    crosshair.color = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
}

void Settings::LoadArena(std::ifstream& file) {
    int r, g, b;
    if (file >> arena.distance >> arena.targetRadius >> arena.timedDifficulty >> r >> g >> b) {
        arena.ballColor = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
    }
}

void Settings::LoadAudio(std::ifstream& file) {
    file >> audio.uiVolume >> audio.popVolume >> audio.arenaVolume;
}

// ==========================================
// SAVE METHODS
// ==========================================

void Settings::SaveMouse(std::ofstream& file) const {
    file << mouse.valorantSens << "\n" 
         << fovDegrees << "\n" 
         << headRadius << "\n" 
         << mouse.sensMultiplier << "\n";
}

void Settings::SaveCrosshair(std::ofstream& file) const {
    file << crosshair.length << "\n" 
         << crosshair.thickness << "\n" 
         << crosshair.gap << "\n" 
         << crosshair.outline << "\n" 
         << crosshair.dot << "\n";
    file << (int)crosshair.color.r << " " 
         << (int)crosshair.color.g << " " 
         << (int)crosshair.color.b << "\n";
}

void Settings::SaveArena(std::ofstream& file) const {
    file << arena.distance << "\n" 
         << arena.targetRadius << "\n" 
         << arena.timedDifficulty << "\n";
    file << (int)arena.ballColor.r << " " 
         << (int)arena.ballColor.g << " " 
         << (int)arena.ballColor.b << "\n";
}

void Settings::SaveAudio(std::ofstream& file) const {
    file << audio.uiVolume << "\n" 
         << audio.popVolume << "\n" 
         << audio.arenaVolume << "\n";
}

// ==========================================
// VALIDATION
// ==========================================

void Settings::Sanitize() {
    if (mouse.sensMultiplier <= 0.0f || mouse.sensMultiplier > 10.0f) 
        mouse.sensMultiplier = 3.15f;
    
    if (arena.targetRadius < 0.02f || arena.targetRadius > 2.0f) 
        arena.targetRadius = 0.11f;
    
    if (arena.timedDifficulty < 0 || arena.timedDifficulty > 2) 
        arena.timedDifficulty = 1;
}