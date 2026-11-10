#pragma once
#include <memory>
#include "raylib.h"
#include "ScreenManager.h"

class Engine {
public:
    Engine() = default;
    ~Engine() = default;

    void Run();

private:
    Font uiFont;
    std::unique_ptr<ScreenManager> screenManager;
    RenderTexture2D renderTarget;

    void InitWindowAndContext();
    void SetupRenderTarget();
    void LoadResources();
    void SetupUI();
    void Shutdown();
};