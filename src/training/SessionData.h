#pragma once
#include "GameExitReason.h"

class SessionData {
public:
    void Reset();
    void Start();
    void End(GameExitReason reason);

    void AddTime(float dt);
    void SetSessionTime(float time);
    
    void RegisterShot();
    void RegisterHit();
    void AddSpawned(int count);
    
    void AddTrackingTime(float dt);
    void AddTrackingTimeOnTarget(float dt);

    int GetPoppedCount() const { return poppedCount; }
    int GetSpawnedBalls() const { return spawnedBalls; }
    int GetShotsFired() const { return shotsFired; }
    int GetHits() const { return hits; }
    float GetSessionTime() const { return sessionTime; }
    float GetTrackTimeOnTarget() const { return trackTimeOnTarget; }
    float GetTrackTimeTotal() const { return trackTimeTotal; }
    bool IsActive() const { return isActive; }
    GameExitReason GetExitReason() const { return exitReason; }

private:
    int   poppedCount   = 0;
    int   spawnedBalls  = 0;
    int   shotsFired    = 0;
    int   hits          = 0;
    float sessionTime   = 0.0f;
    float trackTimeOnTarget = 0.0f;
    float trackTimeTotal    = 0.0f;
    bool  isActive      = false;
    GameExitReason exitReason = GameExitReason::None;
};