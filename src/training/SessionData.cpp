#include "SessionData.h"

void SessionData::Reset() {
    poppedCount = 0;
    spawnedBalls = 0;
    shotsFired = 0;
    hits = 0;
    sessionTime = 0.0f;
    trackTimeOnTarget = 0.0f;
    trackTimeTotal = 0.0f;
    isActive = false;
    exitReason = GameExitReason::None;
}

void SessionData::Start() {
    Reset();
    isActive = true;
}

void SessionData::End(GameExitReason reason) {
    isActive = false;
    exitReason = reason;
}

void SessionData::AddTime(float dt) {
    sessionTime += dt;
}

void SessionData::SetSessionTime(float time) {
    sessionTime = time;
}

void SessionData::RegisterShot() {
    shotsFired++;
}

void SessionData::RegisterHit() {
    hits++;
    poppedCount++;
}

void SessionData::AddSpawned(int count) {
    spawnedBalls += count;
}

void SessionData::AddTrackingTime(float dt) {
    trackTimeTotal += dt;
}

void SessionData::AddTrackingTimeOnTarget(float dt) {
    trackTimeOnTarget += dt;
}