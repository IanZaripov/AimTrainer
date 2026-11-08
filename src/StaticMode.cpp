#include "StaticMode.h"
#include "raymath.h"

void StaticMode::OnStart(std::vector<Target3D>& targets, const Settings& settings) {
    targets.push_back(SpawnBall(settings, GetRandomValue(-700, 700) / 100.0f, GetRandomValue(150, 250) / 100.0f, -settings.arena.distance));
}

void StaticMode::OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) {}

void StaticMode::OnHit(std::vector<Target3D>& targets, const Settings& settings) {
    targets.push_back(SpawnBall(settings, GetRandomValue(-700, 700) / 100.0f, GetRandomValue(150, 250) / 100.0f, -settings.arena.distance));
}

float StaticMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (shots > 0) ? 100.0f * hits / shots : 0.0f;
}