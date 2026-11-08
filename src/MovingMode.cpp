#include "MovingMode.h"
#include "raymath.h"

void MovingMode::OnStart(std::vector<Target3D>& targets, const Settings& settings) {
    Target3D t = SpawnBall(settings, GetRandomValue(-600, 600) / 100.0f, GetRandomValue(150, 250) / 100.0f, -settings.arena.distance);
    t.speed = GetRandomValue(300, 1200) / 100.0f;
    t.direction = (GetRandomValue(0, 1) == 0) ? 1 : -1;
    targets.push_back(t);
}

void MovingMode::OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) {
    for (auto& t : targets) {
        t.position.x += t.speed * t.direction * dt;
        if (t.position.x >= 7.0f) { t.direction = -1; t.position.x = 7.0f; }
        else if (t.position.x <= -7.0f) { t.direction = 1; t.position.x = -7.0f; }
    }
}

void MovingMode::OnHit(std::vector<Target3D>& targets, const Settings& settings) {
    targets.clear();
    OnStart(targets, settings);
}

float MovingMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (trackTotal > 0.0f) ? 100.0f * trackTime / trackTotal : 0.0f;
}