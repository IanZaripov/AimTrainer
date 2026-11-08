#include "MultiStaticMode.h"
#include "GameConfig.h"

void MultiStaticMode::OnStart(std::vector<Target3D>& targets, const Settings& settings) {
    for (int i = 0; i < GameConfig::MultiStaticBallCount; i++) {
        targets.push_back(SpawnRandomBall(settings));
    }
}

int MultiStaticMode::OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) {
    return 0;
}

int MultiStaticMode::OnHit(std::vector<Target3D>& targets, const Settings& settings) {
    targets.push_back(SpawnRandomBall(settings));
    return 1;
}

float MultiStaticMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (shots > 0) ? 100.0f * hits / shots : 0.0f;
}