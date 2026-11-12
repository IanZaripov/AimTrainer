#include "TrainingSession.h"
#include "StaticMode.h"
#include "MovingMode.h"
#include "BouncingMode.h"
#include "TimedMode.h"
#include "MultiStaticMode.h"
#include <cmath>
#include <algorithm>

TrainingSession::TrainingSession(Settings& s) : settings(s), arena(roomConfig) {
    camera.position = { 0.0f, 1.6f, 0.0f };
    camera.target = { 0.0f, 1.6f, -1.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };

    float aspect = (float)GetRenderWidth() / (float)GetRenderHeight();
    float hFovRad = settings.fovDegrees * DEG2RAD;
    camera.fovy = 2.0f * atanf(tanf(hFovRad / 2.0f) / aspect) * RAD2DEG;
    camera.projection = CAMERA_PERSPECTIVE;
}

void TrainingSession::Init() {
    targets.clear();
    session = SessionData{};
    camAngles = CameraAngles{};
}

void TrainingSession::StartTraining(GameMode mode) {
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

void TrainingSession::EndSession(GameExitReason reason) {
    session.isActive = false;
    session.exitReason = reason;
    EnableCursor();
}

void TrainingSession::Update() {
    if (!session.isActive) return;

    if (IsKeyPressed(KEY_ESCAPE)) {
        EndSession(GameExitReason::UserQuit);
        return;
    }

    float dt = GetFrameTime();
    session.sessionTime += dt;
    hud.UpdateStats();

    if (activeMode->IsFinished(session.sessionTime)) {
        session.sessionTime = GameConfig::SessionTimeLimit;
        EndSession(GameExitReason::TimeExpired);
        return;
    }

    UpdateCameraAngles();
    UpdateTargets(dt);
    UpdateTracking(dt);

    int newSpawns = activeMode->OnUpdate(dt, targets, settings);
    session.spawnedBalls += newSpawns;

    CleanupTargets();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        HandleShoot();
    }
}

void TrainingSession::UpdateCameraAngles() {
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

void TrainingSession::UpdateTargets(float dt) {
    for (auto& target : targets) {
        target.Update(dt);
    }
}

void TrainingSession::UpdateTracking(float dt) {
    if (!activeMode->UsesTracking()) return;

    session.trackTimeTotal += dt;
    Vector2 screenCenter = { (float)GetRenderWidth() / 2.0f, (float)GetRenderHeight() / 2.0f };
    Ray ray = GetScreenToWorldRay(screenCenter, camera);

    for (auto& t : targets) {
        if (!t.active) continue;
        if (GetRayCollisionSphere(ray, t.position, settings.arena.targetRadius).hit) {
            session.trackTimeOnTarget += dt;
        }
    }
}

void TrainingSession::CleanupTargets() {
    // Remove targets that are dead AND finished exploding
    targets.erase(std::remove_if(targets.begin(), targets.end(), [](const Target3D& t) { 
        return !t.active && !t.IsExploding(); 
    }), targets.end());
}

void TrainingSession::HandleShoot() {
    session.shotsFired++;
    Vector2 screenCenter = { (float)GetRenderWidth() / 2.0f, (float)GetRenderHeight() / 2.0f };
    Ray ray = GetScreenToWorldRay(screenCenter, camera);

    for (auto& t : targets) {
        if (!t.active) continue;
        if (GetRayCollisionSphere(ray, t.position, settings.arena.targetRadius).hit) {
            t.Hit(); // Trigger explosion and deactivate
            session.poppedCount++;
            session.hits++;

            int newSpawns = activeMode->OnHit(targets, settings);
            session.spawnedBalls += newSpawns;
            break;
        }
    }
}

void TrainingSession::Draw(Font uiFont) const {
    BeginMode3D(camera);
    arena.Draw();
    DrawTargets();
    viewmodel.Draw(camera);
    EndMode3D();

    float accuracy = activeMode->GetAccuracy(session.shotsFired, session.hits, session.spawnedBalls, session.trackTimeOnTarget, session.trackTimeTotal);
    hud.Draw(uiFont, settings.crosshair, session.poppedCount, accuracy, session.sessionTime);
}

void TrainingSession::DrawTargets() const {
    for (const auto& t : targets) {
        t.Draw(settings);
    }
}