#include "TimedMode.h"
#include "GameConfig.h"
#include "raymath.h"

void TimedMode::OnStart(std::vector<Target3D>& targets, const Settings& settings) {
    Target3D t = SpawnBall(settings, GetRandomValue(-700, 700) / 100.0f, GetRandomValue(150, 250) / 100.0f, -settings.arena.distance);
    t.lifeTimer = (settings.arena.timedDifficulty == 0) ? 1.5f : (settings.arena.timedDifficulty == 1) ? 1.0f : 0.6f;
    targets.push_back(t);
}

void TimedMode::OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) {
    for (auto& t : targets) {
        t.lifeTimer -= dt;
        if (t.lifeTimer <= 0.0f) {
            t.active = false;
            Target3D newT = SpawnBall(settings, GetRandomValue(-700, 700) / 100.0f, GetRandomValue(150, 250) / 100.0f, -settings.arena.distance);
            newT.lifeTimer = t.lifeTimer;
            targets.push_back(newT);
        }
    }
}

void TimedMode::OnHit(std::vector<Target3D>& targets, const Settings& settings) {
    targets.clear();
    OnStart(targets, settings);
}

float TimedMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (spawned > 0) ? 100.0f * hits / spawned : 0.0f;
}