#include "TimedMode.h"
#include "raymath.h"

float TimedMode::GetLifetime(const Settings& settings) const {
    if (settings.arena.timedDifficulty == 0) return GameConfig::TimedMode::LifeEasy;
    if (settings.arena.timedDifficulty == 1) return GameConfig::TimedMode::LifeMedium;
    return GameConfig::TimedMode::LifeHard;
}

void TimedMode::OnStart(TargetPool& pool, const Settings& settings) {
    Target3D& t = pool.Request();
    t.position.x = (float)GetRandomValue(GameConfig::Spawn::XMin, GameConfig::Spawn::XMax) / GameConfig::Spawn::Scale;
    t.position.y = (float)GetRandomValue(GameConfig::Spawn::YMin, GameConfig::Spawn::YMax) / GameConfig::Spawn::Scale;
    t.position.z = -settings.arena.distance;
    t.lifeTimer = GetLifetime(settings);
    t.active = true;
}

int TimedMode::OnUpdate(float dt, TargetPool& pool, const Settings& settings) {
    int spawned = 0;
    for (auto& t : pool.GetAll()) {
        if (!t.active) continue;
        
        t.lifeTimer -= dt;
        if (t.lifeTimer <= 0.0f) {
            t.ForceKill();
            Target3D& newT = pool.Request();
            newT.position.x = (float)GetRandomValue(GameConfig::Spawn::XMin, GameConfig::Spawn::XMax) / GameConfig::Spawn::Scale;
            newT.position.y = (float)GetRandomValue(GameConfig::Spawn::YMin, GameConfig::Spawn::YMax) / GameConfig::Spawn::Scale;
            newT.position.z = -settings.arena.distance;
            newT.lifeTimer = GetLifetime(settings);
            newT.active = true;
            spawned++;
        }
    }
    return spawned;
}

int TimedMode::OnHit(TargetPool& pool, const Settings& settings) {
    Target3D& t = pool.Request();
    t.position.x = (float)GetRandomValue(GameConfig::Spawn::XMin, GameConfig::Spawn::XMax) / GameConfig::Spawn::Scale;
    t.position.y = (float)GetRandomValue(GameConfig::Spawn::YMin, GameConfig::Spawn::YMax) / GameConfig::Spawn::Scale;
    t.position.z = -settings.arena.distance;
    t.lifeTimer = GetLifetime(settings);
    t.active = true;
    return 1;
}

float TimedMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (spawned > 0) ? 100.0f * hits / spawned : 0.0f;
}