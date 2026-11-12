#pragma once
#include "raylib.h"
#include "Settings.h"
#include "GameConfig.h"
#include "Target3D.h" // <-- Include the new class
#include <vector>

// Helper to spawn a target with random coordinates
inline Target3D SpawnRandomBall(const Settings& settings) {
    Target3D t;
    t.position.x = (float)GetRandomValue(GameConfig::SpawnXMin, GameConfig::SpawnXMax) / GameConfig::SpawnScale;
    t.position.y = (float)GetRandomValue(GameConfig::SpawnYMin, GameConfig::SpawnYMax) / GameConfig::SpawnScale;
    t.position.z = -settings.arena.distance;
    t.active = true;
    return t;
}

class TrainingMode {
public:
    virtual ~TrainingMode() = default;

    virtual void OnStart(std::vector<Target3D>& targets, const Settings& settings) = 0;
    
    // Returns the number of newly spawned targets for statistics
    virtual int OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) = 0;
    virtual int OnHit(std::vector<Target3D>& targets, const Settings& settings) = 0;
    
    virtual float GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const = 0;
    virtual bool IsFinished(float sessionTime) const { return false; }
    virtual bool UsesTracking() const { return false; }
};