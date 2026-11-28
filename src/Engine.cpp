#include "Engine.h"
#include "UITheme.h"
#include "Audio.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

Engine::Engine() {
    InitWindowAndContext();
    SetupRenderTarget();
    LoadResources();
    SetupUI();
    
    // Show loading screen and compile shaders BEFORE the main loop
    ShowLoadingScreen();

    Audio::Init();
    screenManager = std::make_unique<ScreenManager>();
}

Engine::~Engine() {
    Shutdown();
}

void Engine::Run() {
    while (!WindowShouldClose() && !screenManager->ShouldExit()) {
        screenManager->UpdateLogic();

        BeginTextureMode(renderTarget);
        ClearBackground(UITheme::BG);
        screenManager->DrawUI(uiFont);
        EndTextureMode();

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

// =========================================================
// Initialization
// =========================================================

void Engine::InitWindowAndContext() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_UNDECORATED);
    InitWindow(1280, 720, "Valorant Aim Trainer");
    
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    SetWindowPosition(0, 0);

    SetTargetFPS(144);
    SetExitKey(KEY_NULL); 
}

void Engine::SetupRenderTarget() {
    float aspect = (float)GetScreenWidth() / (float)GetScreenHeight();
    int virtualWidth = (int)(UITheme::VirtualHeight * aspect);

    renderTarget = LoadRenderTexture(virtualWidth, UITheme::VirtualHeight);
    SetTextureFilter(renderTarget.texture, TEXTURE_FILTER_BILINEAR);

    SetMouseScale(
        (float)virtualWidth / (float)GetScreenWidth(),
        (float)UITheme::VirtualHeight / (float)GetScreenHeight()
    );
}

void Engine::LoadResources() {
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

// =========================================================
// Splash Screen & Warmup
// =========================================================

void Engine::ShowLoadingScreen() {
    const float duration = 15.0f;
    float timer = 0.0f;

    // Run a temporary loop for the splash screen
    while (timer < duration && !WindowShouldClose()) {
        timer += GetFrameTime();

        // Compile shaders on the first frame to avoid lag later
        if (timer <= GetFrameTime()) {
            WarmupShaders();
        }

        BeginTextureMode(renderTarget);
        ClearBackground(UITheme::BG);
        DrawLoadingScreen(timer, duration);
        EndTextureMode();

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

void Engine::DrawLoadingScreen(float time, float duration) const {
    float cx = GetRenderWidth() / 2.0f;
    float cy = GetRenderHeight() / 2.0f;

    float progress = time / duration;
    
    // Easing functions
    float barProgress = std::min(1.0f, progress * 2.0f);
    float textAlpha = std::max(0.0f, std::min(1.0f, (progress - 0.3f) * 2.5f));
    
    // Pulsing effect for the bars
    float pulse = 1.0f + 0.05f * sinf(time * 15.0f);

    // 1. The two horizontal red bars
    float maxBarWidth = GetRenderWidth() * 0.6f;
    float barWidth = maxBarWidth * barProgress;
    float barHeight = 3.0f * pulse;
    float gap = 40.0f;

    Color accentColor = UITheme::ACCENT;

    DrawRectangle((int)(cx - barWidth / 2), (int)(cy - gap / 2 - barHeight), (int)barWidth, (int)barHeight, accentColor);
    DrawRectangle((int)(cx - barWidth / 2), (int)(cy + gap / 2), (int)barWidth, (int)barHeight, accentColor);

    // 2. Scanning Line Effect (Tactical style)
    if (progress < 0.9f) {
        float scanY = cy - 150.0f + (time * 300.0f);
        Color scanColor = UITheme::ACCENT;
        scanColor.a = 40;
        DrawLineEx({0, scanY}, {(float)GetRenderWidth(), scanY}, 2.0f, scanColor);
    }

    // 3. Draw Text
    if (textAlpha > 0.0f) {
        const char* title = "AIM TRAINER";
        float titleSize = 64.0f;
        Vector2 titleDim = MeasureTextEx(uiFont, title, titleSize, 2.0f);
        
        Color titleColor = WHITE;
        titleColor.a = (unsigned char)(255 * textAlpha);
        
        DrawTextEx(uiFont, title, 
            { cx - titleDim.x / 2.0f, cy - gap / 2.0f - titleDim.y - 10.0f }, 
            titleSize, 2.0f, titleColor);

        const char* subtitle = "created by IanZaripov";
        float subSize = 20.0f;
        Vector2 subDim = MeasureTextEx(uiFont, subtitle, subSize, 1.0f);
        
        Color subColor = UITheme::TEXT_DIM;
        subColor.a = (unsigned char)(255 * textAlpha);
        
        DrawTextEx(uiFont, subtitle, 
            { cx - subDim.x / 2.0f, cy + gap / 2.0f + 10.0f }, 
            subSize, 1.0f, subColor);
            
        // Loading percentage
        const char* loadText = TextFormat("%d%%", (int)(progress * 100));
        float loadSize = 16.0f;
        Vector2 loadDim = MeasureTextEx(uiFont, loadText, loadSize, 1.0f);
        
        Color percentColor = UITheme::ACCENT;
        percentColor.a = (unsigned char)(255 * textAlpha);
        
        DrawTextEx(uiFont, loadText, 
            { cx - loadDim.x / 2.0f, cy + gap / 2.0f + 40.0f }, 
            loadSize, 1.0f, percentColor);
    }
}

void Engine::WarmupShaders() {
    // Force-compile ALL shaders and allocate ALL buffers used in the game.
    Camera3D dummyCam = { {0,0,0}, {0,0,1}, {0,1,0}, 45.0f, CAMERA_PERSPECTIVE };
    
    BeginMode3D(dummyCam);
    DrawCube({0,0,0}, 1,1,1, WHITE);                       // Weapon parts
    DrawPlane({0,0,0}, {1,1}, WHITE);                      // Arena floor
    DrawSphere({0,0,0}, 1, WHITE);                         // Targets
    DrawSphereWires({0,0,0}, 1, 8, 8, WHITE);              // Target explosion
    DrawCylinderEx({0,0,0}, {0,1,0}, 1, 1, 8, WHITE);      // Weapon barrel
    DrawLine3D({0,0,0}, {1,1,1}, WHITE);                   // Arena grid
    EndMode3D();

    // 2D UI Elements
    DrawRectangle(0, 0, 10, 10, WHITE);                    // UI backgrounds
    DrawRectanglePro({0,0,10,10}, {0,0}, 0, WHITE);        // Crosshair lines
    DrawRectangleRounded({0,0,10,10}, 0.2f, 4, WHITE);     // Top Panel
    DrawRectangleRoundedLinesEx({0,0,10,10}, 0.2f, 4, 2.0f, WHITE); 
    DrawCircleV({0,0}, 5, WHITE);                          // Crosshair center dot
    DrawLineEx({0,0}, {10,10}, 1, WHITE);                  // Crosshair lines
    
    // Warmup Cyrillic font atlas generation
    DrawTextEx(uiFont, "ВРЕМЯ ТОЧНОСТЬ СЧЕТ", {0,0}, 20, 1, WHITE);
}


void Engine::Shutdown() {
    Audio::Close();
    UnloadRenderTexture(renderTarget);
    UnloadFont(uiFont);
    CloseWindow();
}