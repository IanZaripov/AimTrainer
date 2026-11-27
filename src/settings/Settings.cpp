#include "Settings.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

// --- Color Helpers ---

static json ColorToJson(Color color) {
    return json{ {"r", color.r}, {"g", color.g}, {"b", color.b} };
}

static Color ColorFromJson(const json& j, Color fallback) {
    return {
        (unsigned char)j.value("r", (int)fallback.r),
        (unsigned char)j.value("g", (int)fallback.g),
        (unsigned char)j.value("b", (int)fallback.b),
        255
    };
}

// --- Public API ---

void Settings::Load(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    try {
        json j;
        file >> j;

        LoadGeneral(j);
        LoadMouse(j);
        LoadCrosshair(j);
        LoadArena(j);
        LoadAudio(j);

        Sanitize();
    } catch (const std::exception& e) {
        std::cerr << "Settings load error: " << e.what() << std::endl;
    }
}

void Settings::Save(const char* filename) const {
    json j;

    SaveGeneral(j);
    SaveMouse(j);
    SaveCrosshair(j);
    SaveArena(j);
    SaveAudio(j);

    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4); // 4-space indent for readability
    }
}

// --- Loaders ---

void Settings::LoadGeneral(const json& j) {
    fovDegrees = j.value("fovDegrees", fovDegrees);
    headRadius = j.value("headRadius", headRadius);

    int langInt = j.value("language", (int)language);
    language = static_cast<Language>(langInt);
}

void Settings::LoadMouse(const json& j) {
    if (!j.contains("mouse")) {
        return;
    }
    const auto& m = j["mouse"];
    mouse.valorantSens   = m.value("sens", mouse.valorantSens);
    mouse.sensMultiplier = m.value("multiplier", mouse.sensMultiplier);
}

void Settings::LoadCrosshair(const json& j) {
    if (!j.contains("crosshair")) {
        return;
    }
    const auto& c = j["crosshair"];
    crosshair.length    = c.value("length", crosshair.length);
    crosshair.thickness = c.value("thickness", crosshair.thickness);
    crosshair.gap       = c.value("gap", crosshair.gap);
    crosshair.outline   = c.value("outline", crosshair.outline);
    crosshair.dot       = c.value("dot", crosshair.dot);

    if (c.contains("color")) {
        crosshair.color = ColorFromJson(c["color"], crosshair.color);
    }
}

void Settings::LoadArena(const json& j) {
    if (!j.contains("arena")){
        return;
    }
    const auto& a = j["arena"];
    arena.distance        = a.value("distance", arena.distance);
    arena.targetRadius    = a.value("targetRadius", arena.targetRadius);
    arena.timedDifficulty = a.value("timedDifficulty", arena.timedDifficulty);

    if (a.contains("ballColor")) {
        arena.ballColor = ColorFromJson(a["ballColor"], arena.ballColor);
    }
}

void Settings::LoadAudio(const json& j) {
    if (!j.contains("audio")){
        return;
    }
    const auto& a = j["audio"];
    audio.uiVolume    = a.value("uiVolume", audio.uiVolume);
    audio.popVolume   = a.value("popVolume", audio.popVolume);
    audio.arenaVolume = a.value("arenaVolume", audio.arenaVolume);
}

// --- Savers ---

void Settings::SaveGeneral(json& j) const {
    j["fovDegrees"] = fovDegrees;
    j["headRadius"] = headRadius;
    j["language"]   = (int)language;
}

void Settings::SaveMouse(json& j) const {
    j["mouse"] = {
        {"sens",       mouse.valorantSens},
        {"multiplier", mouse.sensMultiplier}
    };
}

void Settings::SaveCrosshair(json& j) const {
    j["crosshair"] = {
        {"length",    crosshair.length},
        {"thickness", crosshair.thickness},
        {"gap",       crosshair.gap},
        {"outline",   crosshair.outline},
        {"dot",       crosshair.dot},
        {"color",     ColorToJson(crosshair.color)}
    };
}

void Settings::SaveArena(json& j) const {
    j["arena"] = {
        {"distance",        arena.distance},
        {"targetRadius",    arena.targetRadius},
        {"timedDifficulty", arena.timedDifficulty},
        {"ballColor",       ColorToJson(arena.ballColor)}
    };
}

void Settings::SaveAudio(json& j) const {
    j["audio"] = {
        {"uiVolume",    audio.uiVolume},
        {"popVolume",   audio.popVolume},
        {"arenaVolume", audio.arenaVolume}
    };
}

// --- Validation ---

void Settings::Sanitize() {
    if (mouse.sensMultiplier <= 0.0f || mouse.sensMultiplier > 10.0f) mouse.sensMultiplier = 3.15f;
    if (arena.targetRadius < 0.02f || arena.targetRadius > 2.0f) arena.targetRadius = 0.11f;
    if (arena.timedDifficulty < 0 || arena.timedDifficulty > 2) arena.timedDifficulty = 1;
}