#include "TargetPool.h"

Target3D& TargetPool::Request() {
    // Look for a dead target to reuse
    for (auto& t : targets) {
        if (!t.active && !t.IsExploding()) {
            t = Target3D{}; // Reset to default state
            return t;
        }
    }
    // If no dead targets, add a new one
    targets.emplace_back();
    return targets.back();
}

void TargetPool::Update(float dt) {
    for (auto& t : targets) {
        t.Update(dt);
    }
}

void TargetPool::Draw(const Settings& settings) const {
    for (const auto& t : targets) {
        t.Draw(settings);
    }
}

void TargetPool::DeactivateAll() {
    for (auto& t : targets) {
        t.ForceKill();
    }
}