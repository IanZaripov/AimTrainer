#include "TargetPool.h"

Target3D& TargetPool::Request() {
    return targets[RequestIndex()];
}

int TargetPool::RequestIndex() {
    for (size_t i = 0; i < targets.size(); i++) {
        if (!targets[i].active && !targets[i].IsExploding()) {
            targets[i] = Target3D{};
            return (int)i;
        }
    }
    targets.emplace_back();
    return (int)(targets.size() - 1);
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