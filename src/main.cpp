#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION 

#include "App.h"

int main() {
    const int INIT_SCREEN_W = 1280;
    const int INIT_SCREEN_H = 720;

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(INIT_SCREEN_W, INIT_SCREEN_H, "Valorant Aim Trainer");
    SetTargetFPS(144);

    // --- ФИКС КИРИЛЛИЦЫ ---
    // Загружаем нужные нам символы: ASCII + Кириллица + спецсимволы
    const char* textToLoad = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:-%()[] "
                             "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                             "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    
    int codepointCount = 0;
    int* codepoints = LoadCodepoints(textToLoad, &codepointCount);
    
    // Загружаем Arial с нашими кодовыми точками
    Font font = LoadFontEx("C:/Windows/Fonts/arial.ttf", 32, codepoints, codepointCount);
    UnloadCodepoints(codepoints);

    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    App app;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        app.Update();

        BeginDrawing();
        app.Draw();
        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();
    return 0;
}