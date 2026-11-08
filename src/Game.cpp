#include "Game.h"
#include "StaticMode.h"
#include "MovingMode.h"
#include "BouncingMode.h"
#include "TimedMode.h"
#include "MultiStaticMode.h"
#include <cmath>
#include <algorithm>

Game::Game(Settings& s) : settings(s), arena(roomConfig) {
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
    session = SessionData{}; 
    camAngles = CameraAngles{};
}

void Game::StartTraining(GameMode mode) {
    Init();
    currentModeType = mode;
    session.isActive = true;
    DisableCursor();

    switch (mode) {
        case GameMode::STATIC:       activeMode = std::make_unique<StaticMode>(); break;
        case GameMode::MOVING:       activeMode = std::make_unique<MovingMode>(); break;
        case GameMode::BOUNCING:     activeMode = std::make_unique<BouncingMode>(); break;
        case GameMode::TIMED:        activeMode = std::make_unique<TimedMode>(); break;
        case GameMode::MULTI_STATIC: activeMode = std::make_unique<MultiStaticMode>(); break;
    }

    activeMode->OnStart(targets, settings);
    session.spawnedBalls += (int)targets.size();
}

void Game::StopTraining() {
    session.isActive = false;
    EnableCursor();
}

bool Game::IsPauseRequested() const {
    return IsKeyPressed(KEY_ESCAPE);
}

bool Game::IsShootRequested() const {
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

// --- ГЛАВНЫЙ ЦИКЛ ---
void Game::Update() {
    if (!session.isActive) return;

    // 1. Проверяем паузу
    if (IsPauseRequested()) {
        StopTraining();
        return;
    }

    // 2. Обновляем время и статы
    float dt = GetFrameTime();
    session.sessionTime += dt;
    hud.UpdateStats();

    // 3. Проверяем условия завершения
    if (activeMode->IsFinished(session.sessionTime)) {
        session.sessionTime = GameConfig::SessionTimeLimit;
        StopTraining();
        return;
    }

    // 4. Обновляем мир
    UpdateCameraAngles();
    UpdateEffects(dt);
    UpdateTracking(dt);
    int newSpawns = activeMode->OnUpdate(dt, targets, settings);
    session.spawnedBalls += newSpawns;
    CleanupTargets();

    // 5. И только теперь обрабатываем выстрел
    if (IsShootRequested()) {
        HandleShoot();
    }
}

void Game::UpdateCameraAngles() {
    Vector2 delta = GetMouseDelta();
    float finalSens = settings.mouse.valorantSens * settings.mouse.sensMultiplier * GameConfig::SensMultiplier;
    
    camAngles.yaw   += delta.x * finalSens;
    camAngles.pitch -= delta.y * finalSens;
    camAngles.pitch = std::clamp(camAngles.pitch, -GameConfig::PitchLimit, GameConfig::PitchLimit);

    Vector3 dir;
    dir.x = cosf(camAngles.pitch * DEG2RAD) * sinf(camAngles.yaw * DEG2RAD);
    dir.y = sinf(camAngles.pitch * DEG2RAD);
    dir.z = -cosf(camAngles.pitch * DEG2RAD) * cosf(camAngles.yaw * DEG2RAD);
    camera.target = Vector3Add(camera.position, dir);
}

void Game::UpdateEffects(float dt) {
    for (auto& e : effects) e.life -= dt;
    effects.erase(std::remove_if(effects.begin(), effects.end(), [](const PopEffect& e) { return e.life <= 0.0f; }), effects.end());
}

void Game::UpdateTracking(float dt) {
    if (!activeMode->UsesTracking()) return;

    session.trackTimeTotal += dt;
    Vector2 screenCenter = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
    Ray ray = GetScreenToWorldRay(screenCenter, camera);
    
    for (auto& t : targets) {
        if (!t.active) continue;
        if (GetRayCollisionSphere(ray, t.position, settings.arena.targetRadius).hit) {
            session.trackTimeOnTarget += dt;
        }
    }
}

void Game::CleanupTargets() {
    targets.erase(std::remove_if(targets.begin(), targets.end(), [](const Target3D& t) { return !t.active; }), targets.end());
}

void Game::HandleShoot() {
    session.shotsFired++;
    Vector2 screenCenter = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
    Ray ray = GetScreenToWorldRay(screenCenter, camera);

    for (auto& t : targets) {
        if (!t.active) continue;
        if (GetRayCollisionSphere(ray, t.position, settings.arena.targetRadius).hit) {
            t.active = false;
            session.poppedCount++;
            session.hits++;
            effects.push_back({ t.position });
            
            int newSpawns = activeMode->OnHit(targets, settings);
            session.spawnedBalls += newSpawns;
            break; 
        }
    }
}

// --- ОТРИСОВКА ---
void Game::Draw(Font uiFont) const {
    BeginMode3D(camera);
    arena.Draw();
    DrawTargets();
    DrawEffects();
    weapon.Draw(camera);
    EndMode3D();

    float accuracy = activeMode->GetAccuracy(session.shotsFired, session.hits, session.spawnedBalls, session.trackTimeOnTarget, session.trackTimeTotal);
    hud.Draw(uiFont, settings.crosshair, session.poppedCount, accuracy, session.sessionTime);
}

void Game::DrawTargets() const {
    for (const auto& t : targets) {
        if (!t.active) continue;
        DrawSphere(t.position, settings.arena.targetRadius, settings.arena.ballColor);
    }
}

void Game::DrawEffects() const {
    for (const auto& e : effects) {
        DrawSingleEffect(e);
    }
}

void Game::DrawSingleEffect(const PopEffect& effect) const {
    float radius = effect.GetRadius(settings.arena.targetRadius);
    Color col = effect.GetColor(settings.arena.ballColor);
    
    DrawSphereWires(effect.position, radius, GameConfig::EffectSphereRings, GameConfig::EffectSphereSlices, col);
}