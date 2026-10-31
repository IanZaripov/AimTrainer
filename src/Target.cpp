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

Vector2 SpawnTargetPosition(int arenaWidth, int arenaHeight) {
    Vector2 center = { arenaWidth / 2.0f, arenaHeight / 2.0f };
    Vector2 pos;
    int attempts = 0;
    do {
        pos.x = RandomFloat(HEAD_RADIUS, arenaWidth - HEAD_RADIUS);
        pos.y = RandomFloat(HEAD_RADIUS, arenaHeight - HEAD_RADIUS);
        attempts++;
    } while (!IsInsideFOV(pos, center, HALF_FOV_RAD) && attempts < 100);
    return pos;
}