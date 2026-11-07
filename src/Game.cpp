#include "Game.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>

Game::Game(Settings& s) : settings(s) {
    camera.position = { 0.0f, 1.6f, 0.0f }; 
    camera.target = { 0.0f, 1.6f, -1.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    
    float aspect = (float)GetScreenWidth() / (float)GetScreenHeight();
    float hFovRad = settings.fovDegrees * DEG2RAD;
    camera.fovy = 2.0f * atanf(tanf(hFovRad / 2.0f) / aspect) * RAD2DEG;
    camera.projection = CAMERA_PERSPECTIVE;
}

void Game::Init() {
    targets.clear();
    effects.clear();
    poppedCount = shotsFired = hits = misses = spawnedBalls = 0;
    sessionTime = 0.0f;
    trackTimeOnTarget = 0.0f;
    trackTimeTotal = 0.0f;
    trainingActive = false;
    yaw = 0.0f;
    pitch = 0.0f;
}

void Game::StartTraining(GameMode mode) {
    currentMode = mode;
    Init();
    trainingActive = true;
    DisableCursor();

    if (currentMode == GameMode::MULTI_STATIC) {
        for (int i = 0; i < 8; i++) {
            SpawnNewTarget();
        }
    } else {
        SpawnNewTarget();
    }
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

    if (currentMode == GameMode::TIMED && sessionTime >= 60.0f) {
        sessionTime = 60.0f;
        StopTraining();
        return;
    }

    UpdateCameraAngles();

    for (auto& e : effects) e.life -= GetFrameTime();
    effects.erase(std::remove_if(effects.begin(), effects.end(), [](const PopEffect& e) { return e.life <= 0.0f; }), effects.end());

    if (currentMode == GameMode::MOVING || currentMode == GameMode::BOUNCING) {
        trackTimeTotal += GetFrameTime();
        Vector2 screenCenter = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
        Ray ray = GetScreenToWorldRay(screenCenter, camera);
        for (auto& t : targets) {
            if (!t.active) continue;
            if (GetRayCollisionSphere(ray, t.position, settings.arena.targetRadius).hit) {
                trackTimeOnTarget += GetFrameTime();
            }
        }
    }

    float floorY = settings.arena.targetRadius + 0.1f;
    float ceilingY = 8.0f - settings.arena.targetRadius - 0.1f;
    if (ceilingY <= floorY) ceilingY = floorY + 1.0f;

    for (auto& t : targets) {
        if (!t.active) continue;

        switch (currentMode) {
            case GameMode::STATIC:
            case GameMode::MULTI_STATIC:
                break;

            case GameMode::MOVING:
                t.position.x += t.speed * t.direction * GetFrameTime();
                if (t.position.x >= 7.0f) {
                    t.direction = -1;
                    t.position.x = 7.0f;
                } else if (t.position.x <= -7.0f) {
                    t.direction = 1;
                    t.position.x = -7.0f;
                }
                break;

            case GameMode::BOUNCING:
                t.position.x += t.velocity.x * GetFrameTime();
                t.position.y += t.velocity.y * GetFrameTime();

                if (t.position.x >= 7.0f) { t.position.x = 7.0f; t.velocity.x *= -1.0f; }
                else if (t.position.x <= -7.0f) { t.position.x = -7.0f; t.velocity.x *= -1.0f; }

                if (t.position.y >= ceilingY) { t.position.y = ceilingY; t.velocity.y *= -1.0f; }
                else if (t.position.y <= floorY) { t.position.y = floorY; t.velocity.y *= -1.0f; }
                break;

            case GameMode::TIMED:
                t.lifeTimer -= GetFrameTime();
                if (t.lifeTimer <= 0.0f) {
                    t.active = false;
                    misses++;
                    SpawnNewTarget();
                }
                break;
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        HandleShoot();
    }
}

void Game::UpdateCameraAngles() {
    Vector2 delta = GetMouseDelta();
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
    bool hitSomething = false;
    Vector2 screenCenter = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
    Ray ray = GetScreenToWorldRay(screenCenter, camera);

    for (auto& t : targets) {
        if (!t.active) continue;
        if (GetRayCollisionSphere(ray, t.position, settings.arena.targetRadius).hit) {
            t.active = false;
            poppedCount++;
            hits++;
            hitSomething = true;

            effects.push_back({ t.position });
            
            if (currentMode != GameMode::STATIC && currentMode != GameMode::MULTI_STATIC) {
                targets.clear();
            }
            SpawnNewTarget();
            break; 
        }
    }

    if (!hitSomething && currentMode == GameMode::TIMED) {
        misses++;
    }

    targets.erase(std::remove_if(targets.begin(), targets.end(), [](const Target3D& t) { return !t.active; }), targets.end());
}

void Game::SpawnNewTarget() {
    Target3D t;
    t.position.z = -settings.arena.distance; 

    float minY = settings.arena.targetRadius + 0.1f;
    float maxY = 6.0f - settings.arena.targetRadius;
    if (maxY <= minY) maxY = minY + 1.0f;

    switch (currentMode) {
        case GameMode::STATIC:
        case GameMode::TIMED:
            t.position.y = (float)GetRandomValue((int)(minY*100), (int)(maxY*100)) / 100.0f;
            t.position.x = (float)GetRandomValue(-700, 700) / 100.0f;
            t.position.z += (float)GetRandomValue(-100, 100) / 100.0f;
            
            if (currentMode == GameMode::TIMED) {
                if (settings.arena.timedDifficulty == 0) t.lifeTimer = 1.5f;
                else if (settings.arena.timedDifficulty == 1) t.lifeTimer = 1.0f;
                else t.lifeTimer = 0.6f;
            }
            break;

        case GameMode::MULTI_STATIC:
            t.position.y = (float)GetRandomValue((int)(minY*100), (int)(maxY*100)) / 100.0f;
            t.position.x = (float)GetRandomValue(-600, 600) / 100.0f; 
            t.position.z += (float)GetRandomValue(-200, 200) / 100.0f;
            break;

        case GameMode::MOVING:
            t.position.y = (float)GetRandomValue((int)(minY*100), (int)(maxY*100)) / 100.0f;
            t.position.x = (float)GetRandomValue(-600, 600) / 100.0f;
            t.speed = (float)GetRandomValue(300, 1200) / 100.0f; 
            t.direction = (GetRandomValue(0, 1) == 0) ? 1 : -1;
            break;

        case GameMode::BOUNCING:
            t.position.x = (float)GetRandomValue(-600, 600) / 100.0f;
            t.position.y = (float)GetRandomValue((int)(minY*100), (int)(maxY*100)) / 100.0f;

            float vx = (float)GetRandomValue(300, 800) / 100.0f; 
            float vy = (float)GetRandomValue(300, 800) / 100.0f;
            if (GetRandomValue(0, 1) == 0) vx *= -1.0f;
            if (GetRandomValue(0, 1) == 0) vy *= -1.0f;
            t.velocity = { vx, vy };
            break;
    }

    t.active = true;
    spawnedBalls++;
    targets.push_back(t);
}

void Game::Draw(Font uiFont) const {
    BeginMode3D(camera);
    arena.Draw();
    DrawTargets();
    DrawEffects();
    weapon.Draw(camera);
    EndMode3D();

    float accuracy = 0.0f;
    if (currentMode == GameMode::STATIC || currentMode == GameMode::MULTI_STATIC) {
        accuracy = (shotsFired > 0) ? 100.0f * hits / shotsFired : 0.0f;
    } else if (currentMode == GameMode::TIMED) {
        accuracy = (spawnedBalls > 0) ? 100.0f * poppedCount / spawnedBalls : 0.0f;
    } else {
        accuracy = (trackTimeTotal > 0.0f) ? 100.0f * trackTimeOnTarget / trackTimeTotal : 0.0f;
    }

    // Убрали showHitMarker из вызова
    hud.Draw(uiFont, settings.crosshair, poppedCount, accuracy, sessionTime);
}

void Game::DrawTargets() const {
    for (const auto& t : targets) {
        if (!t.active) continue;
        DrawSphere(t.position, settings.arena.targetRadius, settings.arena.ballColor);
    }
}

void Game::DrawEffects() const {
    for (const auto& e : effects) {
        float progress = 1.0f - (e.life / 0.2f); 
        float radius = settings.arena.targetRadius * (1.0f + progress * 2.0f); 
        Color col = settings.arena.ballColor;
        col.a = (unsigned char)(255 * (1.0f - progress));
        DrawSphereWires(e.position, radius, 8, 8, col);
    }
}