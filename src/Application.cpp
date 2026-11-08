#include "Application.h"
#include "UITheme.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

void Application::Run() {
    InitWindowAndContext();
    LoadResources();
    SetupUI();
    SetupRenderTarget();

    gameApp = std::make_unique<App>();

    while (!WindowShouldClose() && !gameApp->ShouldExit()) {
        gameApp->UpdateLogic();

        // 1. Рендерим всё в виртуальную текстуру
        BeginTextureMode(renderTarget);
        ClearBackground(UITheme::BG);
        gameApp->DrawUI(uiFont);
        EndTextureMode();

        // 2. Растягиваем текстуру на весь реальный экран
        BeginDrawing();
        ClearBackground(BLACK);
        
        // ВАЖНО: отрицательная высота (-height) в src переворачивает текстуру 
        // обратно, так как OpenGL хранит её снизу вверх.
        DrawTexturePro(
            renderTarget.texture,
            { 0.0f, 0.0f, (float)renderTarget.texture.width, -(float)renderTarget.texture.height },
            { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() },
            { 0.0f, 0.0f }, 0.0f, WHITE
        );
        
        EndDrawing();
    }

    Shutdown();
}

void Application::InitWindowAndContext() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_FULLSCREEN_MODE);
    InitWindow(0, 0, "Valorant Aim Trainer");
    SetTargetFPS(144);
    SetExitKey(KEY_NULL); 
}

void Application::SetupRenderTarget() {
    // Виртуальная ширина зависит от соотношения сторон монитора
    float aspect = (float)GetScreenWidth() / (float)GetScreenHeight();
    int virtualWidth = (int)(UITheme::VirtualHeight * aspect);

    renderTarget = LoadRenderTexture(virtualWidth, UITheme::VirtualHeight);
    SetTextureFilter(renderTarget.texture, TEXTURE_FILTER_BILINEAR);

    // Масштабируем мышь в виртуальное пространство
    SetMouseScale(
        (float)virtualWidth / (float)GetScreenWidth(),
        (float)UITheme::VirtualHeight / (float)GetScreenHeight()
    );
}

void Application::LoadResources() {
    const char* textToLoad = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:-%()[] "
                             "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                             "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    
    int codepointCount = 0;
    int* codepoints = LoadCodepoints(textToLoad, &codepointCount);
    
    uiFont = LoadFontEx("C:/Windows/Fonts/arial.ttf", 32, codepoints, codepointCount);
    
    UnloadCodepoints(codepoints);
}

void Application::SetupUI() {
    GuiSetFont(uiFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    UITheme::Setup();
}

void Application::Shutdown() {
    UnloadRenderTexture(renderTarget);
    UnloadFont(uiFont);
    CloseWindow();
}