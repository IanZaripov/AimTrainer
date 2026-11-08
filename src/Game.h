#pragma once
#include <memory>
#include "raylib.h"
#include "raymath.h"
#include "Settings.h"
#include "Arena.h"
#include "Weapon.h"
#include "HUD.h"
#include "ITrainingMode.h"
#include "GameConfig.h"

enum class GameMode { STATIC, MOVING, BOUNCING, TIMED, MULTI_STATIC };

struct PopEffect {
    Vector3 position;
    float   life = GameConfig::EffectLifetime;

    float GetProgress() const { return 1.0f - (life / GameConfig::EffectLifetime); }
    float GetRadius(float baseRadius) const { return baseRadius * (1.0f + GetProgress() * GameConfig::EffectMaxScale); }
    Color GetColor(Color baseColor) const {
        Color col = baseColor;
        col.a = (unsigned char)(255 * (1.0f - GetProgress()));
        return col;
    }
};

struct SessionData {
    int   poppedCount   = 0;
    int   spawnedBalls  = 0;
    int   shotsFired    = 0;
    int   hits          = 0;
    float sessionTime   = 0.0f;
    float trackTimeOnTarget = 0.0f;
    float trackTimeTotal    = 0.0f;
    bool  isActive      = false;
};

struct CameraAngles {
    float yaw = 0.0f;
    float pitch = 0.0f;
};

class Game {
public:
    Game(Settings& settings);
    void Init();
    void Update();
    void Draw(Font uiFont) const;

    bool IsTrainingActive() const { return session.isActive; }
    void StartTraining(GameMode mode);
    void StopTraining();

    GameMode GetCurrentMode() const { return currentModeType; }
    int GetPoppedCount() const { return session.poppedCount; }
    int GetSpawnedBalls() const { return session.spawnedBalls; }
    int GetShotsFired() const { return session.shotsFired; }
    int GetHits() const { return session.hits; }
    float GetSessionTime() const { return session.sessionTime; }

private:
    // --- Предикаты (проверки) ---
    bool IsPauseRequested() const;
    bool IsShootRequested() const;

    // --- Действия и обновления ---
    void UpdateCameraAngles();
    void UpdateEffects(float dt);
    void UpdateTracking(float dt);
    void CleanupTargets();
    void HandleShoot();

    // --- Отрисовка ---
    void DrawTargets() const;
    void DrawEffects() const;
    void DrawSingleEffect(const PopEffect& effect) const;

    Settings& settings;
    Arena     arena;
    Weapon    weapon;
    HUD       hud;
    
    GameMode currentModeType = GameMode::STATIC;
    std::unique_ptr<TrainingMode> activeMode; 
    
    std::vector<Target3D> targets;
    std::vector<PopEffect> effects;
    
    SessionData  session;
    CameraAngles camAngles;
    Camera3D     camera;
};