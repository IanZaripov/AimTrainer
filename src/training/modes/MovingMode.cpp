#include "MovingMode.h"
#include "raymath.h"

void MovingMode::OnStart(TargetPool& pool, const Settings& settings) {
    Target3D& t = pool.Request();
    t.position.x = (float)GetRandomValue(GameConfig::Spawn::XMin, GameConfig::Spawn::XMax) / GameConfig::Spawn::Scale;
    t.position.y = (float)GetRandomValue(GameConfig::Spawn::YMin, GameConfig::Spawn::YMax) / GameConfig::Spawn::Scale;
    t.position.z = -settings.arena.distance;
    t.speed = (float)GetRandomValue(300, 1200) / 100.0f;
    t.direction = (GetRandomValue(0, 1) == 0) ? 1 : -1;
    t.active = true;
}

int MovingMode::OnUpdate(float dt, TargetPool& pool, const Settings& settings) {
    for (auto& t : pool.GetAll()) {
        if (!t.active) continue;
        t.position.x += t.speed * t.direction * dt;
        if (t.position.x >= 7.0f) { t.direction = -1; t.position.x = 7.0f; }
        else if (t.position.x <= -7.0f) { t.direction = 1; t.position.x = -7.0f; }
    }
    return 0;
}

int MovingMode::OnHit(TargetPool& pool, const Settings& settings) {
    Target3D& t = pool.Request();
    t.position.x = (float)GetRandomValue(GameConfig::Spawn::XMin, GameConfig::Spawn::XMax) / GameConfig::Spawn::Scale;
    t.position.y = (float)GetRandomValue(GameConfig::Spawn::YMin, GameConfig::Spawn::YMax) / GameConfig::Spawn::Scale;
    t.position.z = -settings.arena.distance;
    t.speed = (float)GetRandomValue(300, 1200) / 100.0f;
    t.direction = (GetRandomValue(0, 1) == 0) ? 1 : -1;
    t.active = true;
    return 1;
}

float MovingMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (trackTotal > 0.0f) ? 100.0f * trackTime / trackTotal : 0.0f;
}