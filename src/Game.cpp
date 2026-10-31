#include "Game.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>

Game::Game(Settings& s) : settings(s) {
    // Камера стоит в начале арены (Z=15) и смотрит вглубь (Z=0)
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
    
    // ИСПРАВЛЕНИЕ ИНВЕРСИИ: yaw +=, pitch -=
    yaw   += delta.x * settings.valorantSens * 0.022f;
    pitch -= delta.y * settings.valorantSens * 0.022f;

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
        
        RayCollision collision = GetRayCollisionSphere(ray, t.position, settings.headRadius);
        if (collision.hit) {
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
    // Спавним цели в пределах стен (X: -10..10, Y: 1..4, Z: -15..-5)
    t.position.x = (float)GetRandomValue(-1000, 1000) / 100.0f;
    t.position.y = (float)GetRandomValue(100, 400) / 100.0f;
    t.position.z = (float)GetRandomValue(-1500, -500) / 100.0f;
    t.active = true;
    targets.push_back(t);
}

void Game::Draw(Font uiFont) const {
    BeginMode3D(camera);
    
    // Отрисовка сцены (делегировано в класс Arena)
    arena.Draw();
    
    // Отрисовка целей
    DrawTargets();
    
    EndMode3D();

    // Отрисовка UI (делегировано в отдельный метод)
    DrawUI(uiFont);
}

void Game::DrawTargets() const {
    for (const auto& t : targets) {
        if (!t.active) continue;
        DrawSphere(t.position, settings.headRadius, Color{ 220, 60, 60, 255 });
        DrawSphereWires(t.position, settings.headRadius, 8, 8, Color{ 255, 150, 150, 200 });
    }
}

void Game::DrawUI(Font uiFont) const {
    float cx = GetScreenWidth() / 2.0f;
    float cy = GetScreenHeight() / 2.0f;
    float gap = 6.0f, len = 10.0f;
    
    // Прицел
    DrawCircleV({cx, cy}, 1.5f, GREEN);
    DrawLine(cx - gap - len, cy, cx - gap, cy, GREEN);
    DrawLine(cx + gap, cy, cx + gap + len, cy, GREEN);
    DrawLine(cx, cy - gap - len, cx, cy - gap, GREEN);
    DrawLine(cx, cy + gap, cx, cy + gap + len, GREEN);

    // Хитмаркер
    if (showHitMarker) {
        float s = 8.0f;
        DrawLine(cx - s, cy - s, cx + s, cy + s, WHITE);
        DrawLine(cx + s, cy - s, cx - s, cy + s, WHITE);
    }

    // Статистика
    DrawRectangle(20, 20, 250, 100, Fade(BLACK, 0.7f));
    DrawTextEx(uiFont, TextFormat("Попаданий: %d", poppedCount), {30, 30}, 20, 1, GREEN);
    float accuracy = (shotsFired > 0) ? 100.0f * hits / shotsFired : 0.0f;
    DrawTextEx(uiFont, TextFormat("Точность: %.1f%%", accuracy), {30, 60}, 20, 1, WHITE);
    DrawTextEx(uiFont, TextFormat("Выстрелов: %d", shotsFired), {30, 90}, 20, 1, LIGHTGRAY);
    
    DrawTextEx(uiFont, "ESC - выйти в меню", {20, (float)GetScreenHeight() - 30}, 16, 1, GRAY);
}