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
#include "SessionData.h"

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

    void StartTraining(GameMode mode, GameCategory category = GameCategory::NORMAL);
    void EndSession(GameExitReason reason);

    GameMode GetCurrentMode() const { return currentModeType; }
    GameCategory GetCurrentCategory() const { return currentCategory; }
    bool IsTrainingActive() const { return session.IsActive(); }
    const SessionData& GetData() const { return session; }
    
    float TrainingSession::GetCurrentAccuracy() const;

private:
    void UpdateCameraAngles();
    void UpdateTracking(float dt);
    void HandleShoot();

    Settings&   settings;
    Arena       arena;
    Viewmodel   viewmodel;
    HUD         hud;

    GameCategory currentCategory = GameCategory::NORMAL;
    GameMode    currentModeType = GameMode::STATIC;
    std::unique_ptr<TrainingMode> activeMode;
    
    TargetPool  targetPool;

    SessionData  session;
    CameraAngles camAngles;
    Camera3D     camera;
};