#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Settings.h"
#include "Arena.h"
#include "Weapon.h"
#include "HUD.h"
#include <vector>

enum class GameMode {
    STATIC,
    MOVING,
    BOUNCING,
    TIMED
};

struct Target3D {
    Vector3 position;
    bool    active = true;
    float   speed = 0.0f;      
    int     direction = 1;     
    Vector2 velocity = { 0.0f, 0.0f };
    float   lifeTimer = 0.0f;  
};

// Структура для анимации лопания
struct PopEffect {
    Vector3 position;
    float   life = 0.2f; // Живет 0.2 секунды
};

class Game {
public:
    Game(Settings& settings);
    void Init();
    void Update();
    void Draw(Font uiFont) const;

    bool IsTrainingActive() const { return trainingActive; }
    void StartTraining(GameMode mode);
    void StopTraining();

    // Геттеры для экрана результатов
    GameMode GetCurrentMode() const { return currentMode; }
    int GetPoppedCount() const { return poppedCount; }
    int GetSpawnedBalls() const { return spawnedBalls; }
    int GetShotsFired() const { return shotsFired; }
    int GetHits() const { return hits; }
    float GetSessionTime() const { return sessionTime; }

private:
    void SpawnNewTarget();
    void HandleShoot();
    void DrawTargets() const;
    void DrawEffects() const; // Отрисовка анимации
    void UpdateCameraAngles();

    Settings& settings;
    Arena     arena;
    Weapon    weapon;
    HUD       hud;
    
    GameMode currentMode = GameMode::STATIC;
    std::vector<Target3D> targets;
    std::vector<PopEffect> effects; // Вектор активных анимаций
    
    Camera3D camera;
    float yaw = 0.0f;   
    float pitch = 0.0f; 

    int   poppedCount   = 0;
    int   spawnedBalls  = 0; // Сколько всего шаров появилось
    int   shotsFired    = 0;
    int   hits          = 0;
    int   misses        = 0;
    float sessionTime   = 0.0f;
    
    float trackTimeOnTarget = 0.0f;
    float trackTimeTotal    = 0.0f;

    bool  trainingActive = false;
    bool  showHitMarker  = false;
    float hitMarkerTimer = 0.0f;
};