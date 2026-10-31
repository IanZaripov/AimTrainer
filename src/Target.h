#pragma once
#include "raylib.h"
#include "Settings.h"

struct Target {
    Vector2 position;
    bool    active = true;
};

Vector2 SpawnTargetPosition(const Settings& settings, int arenaWidth, int arenaHeight);