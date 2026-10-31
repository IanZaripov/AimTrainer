#include "App.h"
#include "raygui.h"

App::App() : game(settings) {
    game.Init();
}

void App::Update() {
    if (currentScreen == AppScreen::PLAYING) {
        game.Update();
        
        // Если игра остановилась (например, нажат ESC), возвращаемся в меню
        if (!game.IsTrainingActive()) {
            currentScreen = AppScreen::ROUTINES;
        }
    }
}

void App::Draw() {
    ClearBackground(Color{ 18, 18, 22, 255 }); // Темный фон в стиле Valorant

    if (currentScreen == AppScreen::PLAYING) {
        game.Draw();
    } else {
        DrawTopBar();
        
        if (currentScreen == AppScreen::ROUTINES) {
            DrawRoutinesScreen();
        } else if (currentScreen == AppScreen::SETTINGS) {
            DrawSettingsScreen();
        }
    }
}

void App::DrawTopBar() {
    // Фон топбара
    DrawRectangle(0, 0, GetScreenWidth(), 60, Color{ 25, 25, 30, 255 });
    DrawLine(0, 60, GetScreenWidth(), 60, Color{ 50, 50, 60, 255 });
    
    // Заголовок
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    GuiLabel({ 20, 15, 200, 30 }, "AIM TRAINER");

    // Кнопки навигации
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    
    // Вкладка Routine
    if (GuiButton({ 250, 15, 120, 30 }, "Тренировки")) {
        currentScreen = AppScreen::ROUTINES;
    }
    
    // Вкладка Settings
    if (GuiButton({ 380, 15, 120, 30 }, "Настройки")) {
        currentScreen = AppScreen::SETTINGS;
    }
}

void App::DrawRoutinesScreen() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiLabel({ 40, 100, 300, 30 }, "Выберите рутину:");

    // Карточка тренировки (как выбор карты в CS)
    Rectangle card = { 40, 150, 250, 350 };
    bool hovered = CheckCollisionPointRec(GetMousePosition(), card);
    
    Color cardColor = hovered ? Color{ 60, 60, 70, 255 } : Color{ 40, 40, 50, 255 };
    DrawRectangleRec(card, cardColor);
    DrawRectangleLinesEx(card, 2, hovered ? GREEN : Color{ 80, 80, 90, 255 });

    // Превью тренировки (красный шарик)
    DrawCircle(40 + 125, 150 + 150, 40, Color{ 220, 60, 60, 255 });
    
    // Название карточки
    GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
    GuiLabel({ 40 + 20, 150 + 260, 200, 30 }, "Голова бота");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    GuiLabel({ 40 + 20, 150 + 290, 200, 30 }, "Статичные цели");

    // Обработка клика
    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = AppScreen::PLAYING;
        game.StartTraining();
    }
}

void App::DrawSettingsScreen() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    GuiLabel({ 40, 100, 300, 30 }, "НАСТРОЙКИ МЫШИ");

    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiLabel({ 40, 160, 300, 30 }, "Сенса (Множитель):");
    
    // Слайдер сенсы с минимальным и максимальным значением
    float sens = settings.sensitivity;
    GuiSlider({ 40, 200, 300, 30 }, "0.1", "10.0", &sens, 0.1f, 10.0f);
    settings.sensitivity = sens;

    // Вывод текущего значения (как в Valorant)
    GuiLabel({ 40, 240, 300, 30 }, TextFormat("Текущее значение: %.2f", settings.sensitivity));

    // Пояснение для пользователя
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    GuiLabel({ 40, 300, 500, 30 }, "Настройте ползунок так, чтобы ощущения от движения");
    GuiLabel({ 40, 325, 500, 30 }, "мышью совпадали с игрой (DPI 800, Sens 0.255).");
}