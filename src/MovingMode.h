#pragma once
#include "ITrainingMode.h"

class MovingMode : public TrainingMode {
public:
    void OnStart(std::vector<Target3D>& targets, const Settings& settings) override;
    void OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) override;
    void OnHit(std::vector<Target3D>& targets, const Settings& settings) override;
    float GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const override;
    bool UsesTracking() const override { return true; }
};