#include "Application.h"
#include "UITheme.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

void Application::Run() {
    InitWindowAndContext();
    LoadResources();
    SetupUI();

    gameApp = std::make_unique<App>();

    while (!WindowShouldClose() && !gameApp->ShouldExit()) {
        gameApp->Update();

        BeginDrawing();
        gameApp->Draw(uiFont);
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
    UnloadFont(uiFont);
    CloseWindow();
}