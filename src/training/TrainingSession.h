#pragma once
#include <memory>
#include "raylib.h"
#include "raymath.h"
#include "Settings.h"
#include "Arena.h"
#include "Viewmodel.h"
#include "HUD.h"
#include "ITrainingMode.h"
#include "GameMode.h"
#include "GameConfig.h"
#include "TargetPool.h"

enum class GameExitReason { None, UserQuit, TimeExpired };

struct SessionData {
    int   poppedCount   = 0;
    int   spawnedBalls  = 0;
    int   shotsFired    = 0;
    int   hits          = 0;
    float sessionTime   = 0.0f;
    float trackTimeOnTarget = 0.0f;
    float trackTimeTotal    = 0.0f;
    bool  isActive      = false;
    GameExitReason exitReason = GameExitReason::None;
};

struct CameraAngles {
    float yaw = 0.0f;
    float pitch = 0.0f;
};

class TrainingSession {
public:
    TrainingSession(Settings& settings);
    void Init();
    void Update();
    void Draw(Font uiFont) const;

    bool IsTrainingActive() const { return session.isActive; }
    void StartTraining(GameMode mode);
    void EndSession(GameExitReason reason);

    GameMode GetCurrentMode() const { return currentModeType; }
    GameExitReason GetExitReason() const { return session.exitReason; }
    int GetPoppedCount() const { return session.poppedCount; }
    int GetSpawnedBalls() const { return session.spawnedBalls; }
    int GetShotsFired() const { return session.shotsFired; }
    int GetHits() const { return session.hits; }
    float GetSessionTime() const { return session.sessionTime; }

private:
    void UpdateCameraAngles();
    void UpdateTracking(float dt);
    void HandleShoot();

    Settings&   settings;
    RoomConfig  roomConfig;
    Arena       arena;
    Viewmodel   viewmodel;
    HUD         hud;

    GameMode    currentModeType = GameMode::STATIC;
    std::unique_ptr<TrainingMode> activeMode;
    
    TargetPool  targetPool; // Replaced std::vector

    SessionData  session;
    CameraAngles camAngles;
    Camera3D     camera;
};