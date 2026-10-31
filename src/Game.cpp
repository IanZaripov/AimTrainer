#include "Game.h"
#include "raymath.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime> // Добавлено для функции time()

Game::Game(Settings& s) : settings(s) {
    srand(static_cast<unsigned>(time(nullptr)));
}

void Game::Init() {
    targets.clear();
    poppedCount = shotsFired = hits = 0;
    trainingActive = false;
    showHitMarker = false;
    crosshair = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
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

    // --- МАТЕМАТИКА СЕНСЫ VALORANT ---
    // Valorant: 0.022 * sens = градусы за 1 count мыши.
    // Переводим градусы в пиксели экрана в зависимости от FOV.
    float degreesPerCount = 0.022f * settings.valorantSens;
    float pixelsPerDegree = (float)GetScreenWidth() / settings.fovDegrees;
    float pixelsPerCount = degreesPerCount * pixelsPerDegree;

    Vector2 delta = GetMouseDelta();
    crosshair.x += delta.x * pixelsPerCount;
    crosshair.y += delta.y * pixelsPerCount;

    // Ограничиваем прицел экраном
    crosshair.x = std::clamp(crosshair.x, 0.0f, (float)GetScreenWidth());
    crosshair.y = std::clamp(crosshair.y, 0.0f, (float)GetScreenHeight());

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
        if (Vector2Distance(crosshair, t.position) <= settings.headRadius) {
            t.active = false;
            poppedCount++;
            hits++;
            SpawnNewTarget();
            showHitMarker = true;
            hitMarkerTimer = 0.12f;
            break; 
        }
    }
    targets.erase(std::remove_if(targets.begin(), targets.end(), [](const Target& t) { return !t.active; }), targets.end());
}

void Game::SpawnNewTarget() {
    Vector2 center = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    float halfFovRad = (settings.fovDegrees * DEG2RAD) / 2.0f;
    
    Vector2 pos;
    int attempts = 0;
    do {
        pos.x = (float)GetRandomValue(settings.headRadius, GetScreenWidth() - settings.headRadius);
        pos.y = (float)GetRandomValue(settings.headRadius, GetScreenHeight() - settings.headRadius);
        attempts++;
    } while (std::fabs(std::atan2(pos.y - center.y, pos.x - center.x)) > halfFovRad && attempts < 100);
    
    targets.push_back({pos, true});
}

void Game::Draw(Font uiFont) const {
    DrawArena();
    DrawTargets();
    DrawCrosshair();
    DrawHitMarker();

    // Отрисовка статистики с поддержкой русского языка
    DrawRectangle(20, 20, 250, 100, Fade(BLACK, 0.7f));
    DrawTextEx(uiFont, TextFormat("Попаданий: %d", poppedCount), {30, 30}, 20, 1, GREEN);
    float accuracy = (shotsFired > 0) ? 100.0f * hits / shotsFired : 0.0f;
    DrawTextEx(uiFont, TextFormat("Точность: %.1f%%", accuracy), {30, 60}, 20, 1, WHITE);
    DrawTextEx(uiFont, TextFormat("Выстрелов: %d", shotsFired), {30, 90}, 20, 1, LIGHTGRAY);
    
    DrawTextEx(uiFont, "ESC - выйти в меню", {20, (float)GetScreenHeight() - 30}, 16, 1, GRAY);
}

void Game::DrawArena() const {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{ 30, 30, 35, 255 });
    for (int x = 0; x < GetScreenWidth(); x += 80) DrawLine(x, 0, x, GetScreenHeight(), Color{ 50, 50, 55, 255 });
    for (int y = 0; y < GetScreenHeight(); y += 80) DrawLine(0, y, GetScreenWidth(), y, Color{ 50, 50, 55, 255 });

    Vector2 center = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    float halfFovRad = (settings.fovDegrees * DEG2RAD) / 2.0f;
    float radius = 400.0f;
    DrawLineV(center, { center.x + cosf(-halfFovRad) * radius, center.y + sinf(-halfFovRad) * radius }, Color{ 80, 80, 90, 120 });
    DrawLineV(center, { center.x + cosf(halfFovRad) * radius, center.y + sinf(halfFovRad) * radius }, Color{ 80, 80, 90, 120 });
}

void Game::DrawTargets() const {
    for (const auto& t : targets) {
        if (!t.active) continue;
        DrawCircleV(t.position, settings.headRadius, Color{ 220, 60, 60, 255 });
        DrawCircleLinesV(t.position, settings.headRadius, Color{ 255, 150, 150, 200 });
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