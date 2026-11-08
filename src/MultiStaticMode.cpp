#include "MultiStaticMode.h"
#include "raymath.h"

void MultiStaticMode::OnStart(std::vector<Target3D>& targets, const Settings& settings) {
    for (int i = 0; i < 8; i++) {
        targets.push_back(SpawnBall(settings, GetRandomValue(-600, 600) / 100.0f, GetRandomValue(150, 250) / 100.0f, -settings.arena.distance));
    }
}

void MultiStaticMode::OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) {}

void MultiStaticMode::OnHit(std::vector<Target3D>& targets, const Settings& settings) {
    targets.push_back(SpawnBall(settings, GetRandomValue(-600, 600) / 100.0f, GetRandomValue(150, 250) / 100.0f, -settings.arena.distance));
}

float MultiStaticMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (shots > 0) ? 100.0f * hits / shots : 0.0f;
}