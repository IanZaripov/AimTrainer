#pragma once
#include "ITrainingMode.h"

class StaticMode : public TrainingMode {
public:
    void OnStart(std::vector<Target3D>& targets, const Settings& settings) override;
    int OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) override;
    int OnHit(std::vector<Target3D>& targets, const Settings& settings) override;
    float GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const override;
};