#include "MovingMode.h"
#include "raymath.h"
#include "GameConfig.h"

static float GetBandY(int bandIndex) {
    float bandHeight = (float)(GameConfig::Spawn::YMax - GameConfig::Spawn::YMin) / GameConfig::MovingMode::TargetCount;
    float y = (float)GameConfig::Spawn::YMin + bandHeight * (bandIndex + 0.5f);
    return y / GameConfig::Spawn::Scale;
}

void MovingMode::OnStart(TargetPool& pool, const Settings& settings) {
    ownedIndices.clear();
    for (int i = 0; i < GameConfig::MovingMode::TargetCount; i++) {
        int idx = pool.RequestIndex();
        ownedIndices.push_back(idx);

        Target3D& t = pool.GetAll()[idx];
        t.position.x = (float)GetRandomValue(GameConfig::Spawn::XMin, GameConfig::Spawn::XMax) / GameConfig::Spawn::Scale;
        t.position.y = GetBandY(i);
        t.position.z = -settings.arena.distance;
        t.speed = (float)GetRandomValue(300, 1200) / 100.0f;
        t.direction = (GetRandomValue(0, 1) == 0) ? 1 : -1;
        t.active = true;
    }
}

int MovingMode::OnUpdate(float dt, TargetPool& pool, const Settings& settings) {
    int newSpawns = 0;
    auto& allTargets = pool.GetAll();

    for (size_t slot = 0; slot < ownedIndices.size(); slot++) {
        int idx = ownedIndices[slot];
        if (idx >= (int)allTargets.size()) continue;
        
        auto& t = allTargets[idx];
        
        if (t.active) {
            t.position.x += t.speed * t.direction * dt;
            
            if (t.position.x >= GameConfig::MovingMode::BoundX) { 
                t.direction = -1; 
                t.position.x = GameConfig::MovingMode::BoundX; 
            }
            else if (t.position.x <= -GameConfig::MovingMode::BoundX) { 
                t.direction = 1; 
                t.position.x = -GameConfig::MovingMode::BoundX; 
            }
        } 
        else if (!t.IsExploding()) {
            t.position.x = (float)GetRandomValue(GameConfig::Spawn::XMin, GameConfig::Spawn::XMax) / GameConfig::Spawn::Scale;
            t.position.y = GetBandY((int)slot);
            t.position.z = -settings.arena.distance;
            t.speed = (float)GetRandomValue(300, 1200) / 100.0f;
            t.direction = (GetRandomValue(0, 1) == 0) ? 1 : -1;
            t.active = true;
            newSpawns++;
        }
    }
    return newSpawns;
}


int MovingMode::OnHit(TargetPool& pool, const Settings& settings) {
    return 0; 
}

float MovingMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (shots > 0) ? 100.0f * hits / shots : 0.0f;
}