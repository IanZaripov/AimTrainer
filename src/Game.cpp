#include "Game.h"
#include "raymath.h" // Добавлено для Vector2Distance
#include <cmath>
#include <algorithm>

Game::Game(int sw, int sh, int pw)
    : screenWidth(sw), screenHeight(sh), panelWidth(pw) {}

void Game::Init() {
    targets.clear();
    poppedCount = shotsFired = hits = 0;
    trainingActive = false;
    showHitMarker = false;
}

void Game::StartTraining() {
    Init();
    trainingActive = true;
    SpawnNewTarget();
}

void Game::StopTraining() {
    trainingActive = false;
}

void Game::Update() {
    crosshair = GetMousePosition();
    if (!trainingActive) return;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        HandleShoot();
    }

    if (showHitMarker) {
        hitMarkerTimer -= GetFrameTime();
        if (hitMarkerTimer <= 0.0f) showHitMarker = false;
    }
}

void Game::HandleShoot() {
    shotsFired++;
    for (auto& t : targets) {
        if (!t.active) continue;
        if (Vector2Distance(crosshair, t.position) <= HEAD_RADIUS) {
            t.active = false;
            poppedCount++;
            hits++;
            
            SpawnNewTarget();

            showHitMarker   = true;
            hitMarkerTimer = 0.12f;
            break; 
        }
    }

    targets.erase(
        std::remove_if(targets.begin(), targets.end(),
                       [](const Target& t) { return !t.active; }),
        targets.end());
}

void Game::SpawnNewTarget() {
    Target t;
    t.position = SpawnTargetPosition(arenaWidth(), screenHeight);
    t.active   = true;
    targets.push_back(t);
}

void Game::Draw() const {
    DrawArena();
    DrawTargets();
    DrawCrosshair();
    DrawHitMarker();
}

void Game::DrawArena() const {
    DrawRectangle(0, 0, arenaWidth(), screenHeight, Color{ 30, 30, 35, 255 });

    for (int x = 0; x < arenaWidth(); x += 80)
        DrawLine(x, 0, x, screenHeight, Color{ 50, 50, 55, 255 });
    for (int y = 0; y < screenHeight; y += 80)
        DrawLine(0, y, arenaWidth(), y, Color{ 50, 50, 55, 255 });

    Vector2 center = { arenaWidth() / 2.0f, screenHeight / 2.0f };
    float radius = 400.0f;
    DrawLineV(center,
              { center.x + cosf(-HALF_FOV_RAD) * radius,
                center.y + sinf(-HALF_FOV_RAD) * radius },
              Color{ 80, 80, 90, 120 });
    DrawLineV(center,
              { center.x + cosf(HALF_FOV_RAD) * radius,
                center.y + sinf(HALF_FOV_RAD) * radius },
              Color{ 80, 80, 90, 120 });
}

void Game::DrawTargets() const {
    for (const auto& t : targets) {
        if (!t.active) continue;
        DrawCircleV(t.position, HEAD_RADIUS, Color{ 220, 60, 60, 255 });
        DrawCircleLinesV(t.position, HEAD_RADIUS, Color{ 255, 150, 150, 200 });
    }
}

void Game::DrawCrosshair() const {
    float cx = crosshair.x, cy = crosshair.y;
    const float gap = 6.0f, len = 10.0f;
    DrawCircleV(crosshair, 1.5f, GREEN);
    DrawLine(cx - gap - len, cy, cx - gap, cy, GREEN);
    DrawLine(cx + gap, cy, cx + gap + len, cy, GREEN);
    DrawLine(cx, cy - gap - len, cx, cy - gap, GREEN);
    DrawLine(cx, cy + gap, cx, cy + gap + len, GREEN);
}

void Game::DrawHitMarker() const {
    if (!showHitMarker) return;
    float cx = crosshair.x, cy = crosshair.y, s = 8.0f;
    DrawLine(cx - s, cy - s, cx + s, cy + s, WHITE);
    DrawLine(cx + s, cy - s, cx - s, cy + s, WHITE);
}