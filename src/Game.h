#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Settings.h"
#include "Arena.h"
#include "Weapon.h"
#include "HUD.h"
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
    void UpdateCameraAngles();

    Settings& settings;
    Arena     arena;
    Weapon    weapon;
    HUD       hud;
    
    std::vector<Target3D> targets;
    Camera3D camera;
    float yaw = 0.0f;   
    float pitch = 0.0f; 

    int   poppedCount   = 0;
    int   shotsFired    = 0;
    int   hits          = 0;
    float sessionTime   = 0.0f;
    bool  trainingActive = false;
    bool  showHitMarker  = false;
    float hitMarkerTimer = 0.0f;
};