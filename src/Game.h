#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Settings.h"
#include "Arena.h"
#include <vector>

struct Target3D {
    Vector3 position;
    bool    active = true;
};

class Game {
public:
    Game(Settings& settings);
    void Init();
    void Update();
    void Draw(Font uiFont) const;

    bool IsTrainingActive() const { return trainingActive; }
    void StartTraining();
    void StopTraining();

private:
    void SpawnNewTarget();
    void HandleShoot();
    void DrawTargets() const;
    void DrawUI(Font uiFont) const;
    void UpdateCameraAngles();

    Settings& settings;
    Arena     arena;
    std::vector<Target3D> targets;
    
    Camera3D camera;
    float yaw = 0.0f;   
    float pitch = 0.0f; 

    int   poppedCount   = 0;
    int   shotsFired    = 0;
    int   hits          = 0;
    bool  trainingActive = false;
    bool  showHitMarker  = false;
    float hitMarkerTimer = 0.0f;
};