#include "MultiStaticMode.h"
#include "GameConfig.h"

void MultiStaticMode::OnStart(TargetPool& pool, const Settings& settings) {
    for (int i = 0; i < GameConfig::MultiStaticBallCount; i++) {
        Target3D& t = pool.Request();
        t.position.x = (float)GetRandomValue(GameConfig::SpawnXMin, GameConfig::SpawnXMax) / GameConfig::SpawnScale;
        t.position.y = (float)GetRandomValue(GameConfig::SpawnYMin, GameConfig::SpawnYMax) / GameConfig::SpawnScale;
        t.position.z = -settings.arena.distance;
        t.active = true;
    }
}

int MultiStaticMode::OnUpdate(float dt, TargetPool& pool, const Settings& settings) {
    return 0;
}

int MultiStaticMode::OnHit(TargetPool& pool, const Settings& settings) {
    Target3D& t = pool.Request();
    t.position.x = (float)GetRandomValue(GameConfig::SpawnXMin, GameConfig::SpawnXMax) / GameConfig::SpawnScale;
    t.position.y = (float)GetRandomValue(GameConfig::SpawnYMin, GameConfig::SpawnYMax) / GameConfig::SpawnScale;
    t.position.z = -settings.arena.distance;
    t.active = true;
    return 1;
}

float MultiStaticMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (shots > 0) ? 100.0f * hits / shots : 0.0f;
}