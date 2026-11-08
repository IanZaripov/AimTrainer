#pragma once
#include "raylib.h"
#include "Settings.h"
#include <vector>

struct Target3D {
    Vector3 position;
    bool    active = true;
    float   speed = 0.0f;      
    int     direction = 1;     
    Vector2 velocity = { 0.0f, 0.0f };
    float   lifeTimer = 0.0f;  
};

inline Target3D SpawnBall(const Settings& settings, float x, float y, float z) {
    Target3D t;
    t.position = { x, y, z };
    t.active = true;
    return t;
}

class TrainingMode {
public:
    virtual ~TrainingMode() = default;

    virtual void OnStart(std::vector<Target3D>& targets, const Settings& settings) = 0;
    virtual void OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) = 0;
    virtual void OnHit(std::vector<Target3D>& targets, const Settings& settings) = 0;
    virtual float GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const = 0;
    virtual bool IsFinished(float sessionTime) const { return false; }
    virtual bool UsesTracking() const { return false; }
};