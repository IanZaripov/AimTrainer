#include "Target.h"
#include "raymath.h"
#include <cmath>
#include <cstdlib>

float RandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

bool IsInsideFOV(Vector2 point, Vector2 center, float halfFovRad) {
    Vector2 dir = { point.x - center.x, point.y - center.y };
    float angle = std::atan2(dir.y, dir.x);
    return std::fabs(angle) <= halfFovRad;
}

Vector2 SpawnTargetPosition(const Settings& settings, int arenaWidth, int arenaHeight) {
    Vector2 center = { arenaWidth / 2.0f, arenaHeight / 2.0f };
    float halfFovRad = (settings.fovDegrees * DEG2RAD) / 2.0f;
    
    Vector2 pos;
    int attempts = 0;
    do {
        pos.x = RandomFloat(settings.headRadius, arenaWidth - settings.headRadius);
        pos.y = RandomFloat(settings.headRadius, arenaHeight - settings.headRadius);
        attempts++;
    } while (!IsInsideFOV(pos, center, halfFovRad) && attempts < 100);
    
    return pos;
}