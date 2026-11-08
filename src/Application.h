#pragma once
#include <memory>
#include "raylib.h"
#include "App.h"

class Application {
public:
    Application() = default;
    ~Application() = default;

    void Run();

private:
    Font uiFont;
    std::unique_ptr<App> gameApp;
    RenderTexture2D renderTarget;

    void InitWindowAndContext();
    void SetupRenderTarget();
    void LoadResources();
    void SetupUI();
    void Shutdown();
};