#include "Engine.h"
#include "UITheme.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

Engine::Engine() {
    InitWindowAndContext();
    LoadFontsResources();
    SetupUI();
    SetupRenderTarget();
    screenManager = std::make_unique<ScreenManager>();
}

Engine::~Engine() {
    Shutdown();
}

void Engine::Run() {
    while (!WindowShouldClose() && !screenManager->ShouldExit()) {
        screenManager->UpdateLogic();

        // draw onto a virtual texture
        BeginTextureMode(renderTarget);
        ClearBackground(UITheme::BG);
        screenManager->DrawUI(uiFont);
        EndTextureMode();

        // stretch it to fit the actual screen
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(
            renderTarget.texture,
            { 0.0f, 0.0f, (float)renderTarget.texture.width, -(float)renderTarget.texture.height },
            { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() },
            { 0.0f, 0.0f }, 0.0f, WHITE
        );
        EndDrawing();
    }
}

void Engine::InitWindowAndContext() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_FULLSCREEN_MODE);
    InitWindow(0, 0, "Valorant Aim Trainer");
    SetTargetFPS(144);
    SetExitKey(KEY_NULL);
}

void Engine::LoadFontsResources() {
    
    const char* textToLoad = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:-%()[] "
                             "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                             "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    
    int codepointCount = 0;
    int* codepoints = LoadCodepoints(textToLoad, &codepointCount);
    uiFont = LoadFontEx("C:/Windows/Fonts/arial.ttf", 32, codepoints, codepointCount);
    UnloadCodepoints(codepoints);
}

void Engine::SetupUI() {
    GuiSetFont(uiFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    UITheme::Setup();
}

void Engine::SetupRenderTarget() {
    // Virtual resolution: the height is fixed, the width depends on the monitor’s aspect ratio
    float aspect = (float)GetScreenWidth() / (float)GetScreenHeight();
    int virtualWidth = (int)(UITheme::VirtualHeight * aspect);

    renderTarget = LoadRenderTexture(virtualWidth, UITheme::VirtualHeight);
    SetTextureFilter(renderTarget.texture, TEXTURE_FILTER_BILINEAR);
    // scale the mouse in the virtual space so that the sensation feels the same at any resolution
    SetMouseScale(
        (float)virtualWidth / (float)GetScreenWidth(),
        (float)UITheme::VirtualHeight / (float)GetScreenHeight()
    );
}

void Engine::Shutdown() {
    UnloadRenderTexture(renderTarget);
    UnloadFont(uiFont);
    CloseWindow();
}