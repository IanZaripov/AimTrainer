#include "BouncingMode.h"
#include "raymath.h"

void BouncingMode::OnStart(std::vector<Target3D>& targets, const Settings& settings) {
    Target3D t = SpawnBall(settings, GetRandomValue(-600, 600) / 100.0f, GetRandomValue(150, 250) / 100.0f, -settings.arena.distance);
    float vx = GetRandomValue(300, 800) / 100.0f;
    float vy = GetRandomValue(300, 800) / 100.0f;
    t.velocity = { (GetRandomValue(0, 1) == 0 ? 1.0f : -1.0f) * vx, (GetRandomValue(0, 1) == 0 ? 1.0f : -1.0f) * vy };
    targets.push_back(t);
}

void BouncingMode::OnUpdate(float dt, std::vector<Target3D>& targets, const Settings& settings) {
    float floorY = settings.arena.targetRadius + 0.1f;
    float ceilingY = 6.0f - settings.arena.targetRadius;

    for (auto& t : targets) {
        t.position.x += t.velocity.x * dt;
        t.position.y += t.velocity.y * dt;

        if (t.position.x >= 7.0f) { t.position.x = 7.0f; t.velocity.x *= -1; }
        else if (t.position.x <= -7.0f) { t.position.x = -7.0f; t.velocity.x *= -1; }
        if (t.position.y >= ceilingY) { t.position.y = ceilingY; t.velocity.y *= -1; }
        else if (t.position.y <= floorY) { t.position.y = floorY; t.velocity.y *= -1; }
    }
}

void BouncingMode::OnHit(std::vector<Target3D>& targets, const Settings& settings) {
    targets.clear();
    OnStart(targets, settings);
}

float BouncingMode::GetAccuracy(int shots, int hits, int spawned, float trackTime, float trackTotal) const {
    return (trackTotal > 0.0f) ? 100.0f * trackTime / trackTotal : 0.0f;
}