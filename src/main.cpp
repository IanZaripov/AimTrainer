#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION 

#include "App.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_FULLSCREEN_MODE);
    
    InitWindow(0, 0, "Valorant Aim Trainer");
    SetTargetFPS(144);
    
    SetExitKey(KEY_NULL); 

    const char* textToLoad = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:-%()[] "
                             "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                             "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    
    int codepointCount = 0;
    int* codepoints = LoadCodepoints(textToLoad, &codepointCount);
    Font font = LoadFontEx("C:/Windows/Fonts/arial.ttf", 32, codepoints, codepointCount);
    UnloadCodepoints(codepoints);

    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    App app;

    // Добавлена проверка !app.ShouldExit()
    while (!WindowShouldClose() && !app.ShouldExit()) {
        app.Update();

        BeginDrawing();
        app.Draw(font);
        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();
    return 0;
}