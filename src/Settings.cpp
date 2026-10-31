#include "Settings.h"
#include <fstream>

void Settings::Load(const char* filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> valorantSens >> fovDegrees >> headRadius;
    }
}

void Settings::Save(const char* filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << valorantSens << "\n" << fovDegrees << "\n" << headRadius << "\n";
    }
}