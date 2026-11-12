#pragma once
#include "ITrainingMode.h"

class BouncingMode : public TrainingMode {
public:
    void OnStart(TargetPool& pool, const Settings& settings) override;
    int OnUpdate(float dt, TargetPool& pool, const Settings& settings) override;
    int OnHit(TargetPool& pool, const Settings& settings) override;
    float GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const override;
    bool UsesTracking() const override { return true; }
};