#pragma once
#include "raylib.h"
#include "Target.h"
#include <vector>

class Game {
public:
    Game(int screenWidth, int screenHeight, int panelWidth);

    void Init();
    void Update();
    void Draw() const;

    // Геттеры для UI
    bool  IsTrainingActive() const { return trainingActive; }
    int   GetPoppedCount()   const { return poppedCount; }
    int   GetShotsFired()    const { return shotsFired; }
    int   GetHits()          const { return hits; }
    Vector2 GetCrosshair()   const { return crosshair; }

    void StartTraining();
    void StopTraining();

private:
    void SpawnNewTarget();
    void HandleShoot();
    void DrawArena() const;
    void DrawTargets() const;
    void DrawCrosshair() const;
    void DrawHitMarker() const;

    int screenWidth;
    int screenHeight;
    int panelWidth;
    int arenaWidth() const { return screenWidth - panelWidth; }

    Vector2 crosshair = { 0, 0 };
    std::vector<Target> targets;
    int  poppedCount   = 0;
    int  shotsFired    = 0;
    int  hits          = 0;
    bool trainingActive = false;
    bool showHitMarker  = false;
    float hitMarkerTimer = 0.0f;
};