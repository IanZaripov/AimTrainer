#include "StaticMode.h"

void StaticMode::OnStart(TargetPool& pool, const Settings& settings) {
    Target3D& t = pool.Request();
    t.position.x = (float)GetRandomValue(GameConfig::SpawnXMin, GameConfig::SpawnXMax) / GameConfig::SpawnScale;
    t.position.y = (float)GetRandomValue(GameConfig::SpawnYMin, GameConfig::SpawnYMax) / GameConfig::SpawnScale;
    t.position.z = -settings.arena.distance;
    t.active = true;
}

int StaticMode::OnUpdate(float dt, TargetPool& pool, const Settings& settings) {
    return 0;
}

int StaticMode::OnHit(TargetPool& pool, const Settings& settings) {
    Target3D& t = pool.Request();
    t.position.x = (float)GetRandomValue(GameConfig::SpawnXMin, GameConfig::SpawnXMax) / GameConfig::SpawnScale;
    t.position.y = (float)GetRandomValue(GameConfig::SpawnYMin, GameConfig::SpawnYMax) / GameConfig::SpawnScale;
    t.position.z = -settings.arena.distance;
    t.active = true;
    return 1;
}

float StaticMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (shots > 0) ? 100.0f * hits / shots : 0.0f;
}