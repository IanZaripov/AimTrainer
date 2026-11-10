#pragma once
#include "ITrainingMode.h"
#include "GameConfig.h"

class TimedMode : public TrainingMode {
private:
    float GetLifetime(const Settings& settings) const;
public:
    void OnStart(std::vector<Target3D>& targets, const Settings& settings) override;
    int OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) override;
    int OnHit(std::vector<Target3D>& targets, const Settings& settings) override;
    float GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const override;
    bool IsFinished(float sessionTime) const override { return sessionTime >= GameConfig::SessionTimeLimit; }
};