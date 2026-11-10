#include "TimedMode.h"
#include "raymath.h"

float TimedMode::GetLifetime(const Settings& settings) const {
    if (settings.arena.timedDifficulty == 0) return GameConfig::TimedLifeEasy;
    if (settings.arena.timedDifficulty == 1) return GameConfig::TimedLifeMedium;
    return GameConfig::TimedLifeHard;
}

void TimedMode::OnStart(std::vector<Target3D>& targets, const Settings& settings) {
    Target3D t = SpawnRandomBall(settings);
    t.lifeTimer = GetLifetime(settings);
    targets.push_back(t);
}

int TimedMode::OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) {
    int spawned = 0;
    for (auto& t : targets) {
        t.lifeTimer -= dt;
        if (t.lifeTimer <= 0.0f) {
            // Перерождаем шар НА МЕСТЕ (не меняем размер вектора!)
            t.position.x = (float)GetRandomValue(GameConfig::SpawnXMin, GameConfig::SpawnXMax) / GameConfig::SpawnScale;
            t.position.y = (float)GetRandomValue(GameConfig::SpawnYMin, GameConfig::SpawnYMax) / GameConfig::SpawnScale;
            t.lifeTimer = GetLifetime(settings);
            spawned++;
        }
    }
    return spawned; // Возвращаем 1, если был промах по времени
}

int TimedMode::OnHit(std::vector<Target3D>& targets, const Settings& settings) {
    targets.clear();
    OnStart(targets, settings);
    return 1;
}

float TimedMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (spawned > 0) ? 100.0f * hits / spawned : 0.0f;
}