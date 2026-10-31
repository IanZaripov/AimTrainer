#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION 

#include "Game.h"
#include "UiPanel.h"
#include "Settings.h"

int main() {
    const int INIT_SCREEN_W = 1280;
    const int INIT_SCREEN_H = 720;

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(INIT_SCREEN_W, INIT_SCREEN_H, "Valorant Aim Trainer");
    SetTargetFPS(144);

    // Загружаем системный шрифт Arial (он есть на любой Windows) для поддержки кириллицы
    Font font = LoadFontEx("C:/Windows/Fonts/arial.ttf", 20, 0, 0);
    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    Settings settings;
    
    Game    game(settings);
    UiPanel ui(game, settings);
    game.Init();

    while (!WindowShouldClose()) {
        // Переключение на полный экран по F11
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        game.Draw();
        ui.Draw();
        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();
    return 0;
}