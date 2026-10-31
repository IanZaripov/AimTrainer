#include "Settings.h"
#include <fstream>

void Settings::Load(const char* filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> valorantSens >> fovDegrees >> headRadius;
        if (headRadius > 1.0f) {
            headRadius = 0.25f;
        }
    }
}

void Settings::Save(const char* filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << valorantSens << "\n" << fovDegrees << "\n" << headRadius << "\n";
    }
}