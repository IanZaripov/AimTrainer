#pragma once
#include <vector>
#include "Target3D.h"
#include "Settings.h"

class TargetPool {
public:
    TargetPool() = default;

    // Requests a target from the pool. 
    // Reuses an inactive one if available, or creates a new one.
    Target3D& Request();

    // Updates all targets (including exploding ones)
    void Update(float dt);

    // Draws all active and exploding targets
    void Draw(const Settings& settings) const;

    // Returns the entire collection for raycasting and movement logic
    std::vector<Target3D>& GetAll() { return targets; }
    const std::vector<Target3D>& GetAll() const { return targets; }

    // Deactivates all targets immediately (useful when restarting modes)
    void DeactivateAll();

private:
    std::vector<Target3D> targets;
};