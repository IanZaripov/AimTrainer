#pragma once
#include "raylib.h"
#include "Settings.h"
#include "GameConfig.h"
#include "TargetPool.h"
#include <vector>

class TrainingMode {
public:
    virtual ~TrainingMode() = default;

    virtual void OnStart(TargetPool& pool, const Settings& settings) = 0;
    virtual int OnUpdate(float dt, TargetPool& pool, const Settings& settings) = 0;
    virtual int OnHit(TargetPool& pool, const Settings& settings) = 0;
    
    virtual float GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const = 0;
    virtual bool IsFinished(float sessionTime) const { return false; }
    virtual bool UsesTracking() const { return false; }
};