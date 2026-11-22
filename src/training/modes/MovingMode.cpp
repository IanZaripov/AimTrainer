#include "MovingMode.h"
#include "raymath.h"
#include "GameConfig.h"

static float GetBandY(int bandIndex) {
    float bandHeight = (float)(GameConfig::Spawn::YMax - GameConfig::Spawn::YMin) / GameConfig::MovingMode::TargetCount;
    float y = (float)GameConfig::Spawn::YMin + bandHeight * (bandIndex + 0.5f);
    return y / GameConfig::Spawn::Scale;
}

void MovingMode::OnStart(TargetPool& pool, const Settings& settings) {
    for (int i = 0; i < GameConfig::MovingMode::TargetCount; i++) {
        Target3D& t = pool.Request();
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
    auto& targets = pool.GetAll();

    for (size_t i = 0; i < targets.size(); i++) {
        auto& t = targets[i];
        
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
            int bandIndex = i % GameConfig::MovingMode::TargetCount;
            
            t.position.x = (float)GetRandomValue(GameConfig::Spawn::XMin, GameConfig::Spawn::XMax) / GameConfig::Spawn::Scale;
            t.position.y = GetBandY(bandIndex);
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