#include "StaticMode.h"

void StaticMode::OnStart(std::vector<Target3D>& targets, const Settings& settings) {
    targets.push_back(SpawnRandomBall(settings));
}

int StaticMode::OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) {
    return 0;
}

int StaticMode::OnHit(std::vector<Target3D>& targets, const Settings& settings) {
    targets.push_back(SpawnRandomBall(settings));
    return 1;
}

float StaticMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (shots > 0) ? 100.0f * hits / shots : 0.0f;
}