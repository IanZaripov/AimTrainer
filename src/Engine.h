#pragma once
#include <memory>
#include "raylib.h"
#include "ScreenManager.h"

class Engine {
public:
    Engine();
    ~Engine();
    void Run();

private:
    Font uiFont = { 0 };
    std::unique_ptr<ScreenManager> screenManager;
    RenderTexture2D renderTarget = { 0 };

    void InitWindowAndContext();
    void LoadFontsResources();
    void SetupUI();
    void SetupRenderTarget();
    void Shutdown();
};