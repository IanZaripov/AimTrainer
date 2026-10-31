#pragma once
#include "raylib.h"
#include "Target.h"
#include "Settings.h"
#include <vector>

class Game {
public:
    Game(Settings& settings);
    ~Game() = default;

    void Init();
    void Update();
    void Draw() const;

    bool IsTrainingActive() const { return trainingActive; }
    void StartTraining();
    void StopTraining();

private:
    void SpawnNewTarget();
    void HandleShoot();
    void DrawArena() const;
    void DrawTargets() const;
    void DrawCrosshair() const;
    void DrawHitMarker() const;

    Settings& settings;
    std::vector<Target> targets;

    Vector2 crosshair = { 0, 0 };
    int   poppedCount   = 0;
    int   shotsFired    = 0;
    int   hits          = 0;
    bool  trainingActive = false;
    bool  showHitMarker  = false;
    float hitMarkerTimer = 0.0f;
};