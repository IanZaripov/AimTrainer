#include "Game.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>

Game::Game(Settings& s) : settings(s) {
    camera.position = { 0.0f, 1.6f, 15.0f }; 
    camera.target = { 0.0f, 1.6f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    
    float aspect = (float)GetScreenWidth() / (float)GetScreenHeight();
    float hFovRad = settings.fovDegrees * DEG2RAD;
    camera.fovy = 2.0f * atanf(tanf(hFovRad / 2.0f) / aspect) * RAD2DEG;
    camera.projection = CAMERA_PERSPECTIVE;
}

void Game::Init() {
    targets.clear();
    poppedCount = shotsFired = hits = 0;
    sessionTime = 0.0f;
    trainingActive = false;
    showHitMarker = false;
    yaw = 0.0f;
    pitch = 0.0f;
}

void Game::StartTraining() {
    Init();
    trainingActive = true;
    DisableCursor();
    SpawnNewTarget();
}

void Game::StopTraining() {
    trainingActive = false;
    EnableCursor();
}

void Game::Update() {
    if (!trainingActive) return;

    if (IsKeyPressed(KEY_ESCAPE)) {
        StopTraining();
        return;
    }

    sessionTime += GetFrameTime();
    UpdateCameraAngles();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        HandleShoot();
    }

    if (showHitMarker) {
        hitMarkerTimer -= GetFrameTime();
        if (hitMarkerTimer <= 0.0f) showHitMarker = false;
    }
}

void Game::UpdateCameraAngles() {
    Vector2 delta = GetMouseDelta();
    // Используем данные из MouseConfig
    float finalSens = settings.mouse.valorantSens * settings.mouse.sensMultiplier * 0.022f;
    
    yaw   += delta.x * finalSens;
    pitch -= delta.y * finalSens;
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    Vector3 dir;
    dir.x = cosf(pitch * DEG2RAD) * sinf(yaw * DEG2RAD);
    dir.y = sinf(pitch * DEG2RAD);
    dir.z = -cosf(pitch * DEG2RAD) * cosf(yaw * DEG2RAD);
    camera.target = Vector3Add(camera.position, dir);
}

void Game::HandleShoot() {
    shotsFired++;
    Vector2 screenCenter = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
    Ray ray = GetScreenToWorldRay(screenCenter, camera);

    for (auto& t : targets) {
        if (!t.active) continue;
        if (GetRayCollisionSphere(ray, t.position, settings.headRadius).hit) {
            t.active = false;
            poppedCount++;
            hits++;
            SpawnNewTarget();
            showHitMarker = true;
            hitMarkerTimer = 0.12f;
            break; 
        }
    }
    targets.erase(std::remove_if(targets.begin(), targets.end(), [](const Target3D& t) { return !t.active; }), targets.end());
}

void Game::SpawnNewTarget() {
    Target3D t;
    t.position.x = (float)GetRandomValue(-600, 600) / 100.0f;
    t.position.y = (float)GetRandomValue(100, 400) / 100.0f;
    t.position.z = (float)GetRandomValue(-2000, -500) / 100.0f;
    t.active = true;
    targets.push_back(t);
}

void Game::Draw(Font uiFont) const {
    BeginMode3D(camera);
    arena.Draw();
    DrawTargets();
    weapon.Draw(camera);
    EndMode3D();

    // Передаем только конфиг прицела
    hud.Draw(uiFont, settings.crosshair, poppedCount, shotsFired, hits, sessionTime, showHitMarker);
}

void Game::DrawTargets() const {
    for (const auto& t : targets) {
        if (!t.active) continue;
        DrawSphere(t.position, settings.headRadius, Color{ 0, 220, 255, 255 });
        DrawSphereWires(t.position, settings.headRadius, 8, 8, WHITE);
    }
}