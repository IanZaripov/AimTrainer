#include "UiPanel.h"

UiPanel::UiPanel(Game& g, Settings& s) : game(g), settings(s) {}

void UiPanel::Draw() {
    int px = panelX();
    DrawRectangle(px, 0, settings.panelWidth, GetScreenHeight(), Color{ 25, 25, 30, 255 });

    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(LIGHTGRAY));

    int y = 30;
    GuiLabel({ (float)px + 20, (float)y, (float)settings.panelWidth - 40.0f, 30 }, "VALORANT AIM TRAINER");
    y += 45;

    GuiLabel({ (float)px + 20, (float)y, (float)settings.panelWidth - 40.0f, 25 }, "Режим: Шарики (голова)");
    y += 40;

    if (!game.IsTrainingActive()) {
        if (GuiButton({ (float)px + 20, (float)y, 200, 40 }, "НАЧАТЬ ТРЕНИРОВКУ")) {
            game.StartTraining();
        }
    } else {
        if (GuiButton({ (float)px + 20, (float)y, 200, 40 }, "ОСТАНОВИТЬ (ESC)")) {
            game.StopTraining();
        }
    }
    y += 60;

    GuiLabel({ (float)px + 20, (float)y, (float)settings.panelWidth - 40.0f, 25 },
             TextFormat("Лопнуто шариков: %d", game.GetPoppedCount()));
    y += 30;

    float accuracy = (game.GetShotsFired() > 0)
        ? 100.0f * game.GetHits() / game.GetShotsFired()
        : 0.0f;
    GuiLabel({ (float)px + 20, (float)y, (float)settings.panelWidth - 40.0f, 25 },
             TextFormat("Точность: %.1f%%", accuracy));
    y += 30;

    GuiLabel({ (float)px + 20, (float)y, (float)settings.panelWidth - 40.0f, 25 },
             TextFormat("Выстрелов: %d", game.GetShotsFired()));
    y += 50;

    // Блок настроек
    GuiLabel({ (float)px + 20, (float)y, (float)settings.panelWidth - 40.0f, 25 }, "НАСТРОЙКИ");
    y += 30;
    
    GuiLabel({ (float)px + 20, (float)y, (float)settings.panelWidth - 40.0f, 25 }, "Сенса (Множитель):");
    y += 25;
    
    // Напрямую меняем настройку
    GuiSlider({ (float)px + 20, (float)y, 200, 25 }, "0.1", "5.0", &settings.sensitivity, 0.1f, 5.0f);
    y += 40;

    // Подсказки
    GuiLabel({ (float)px + 20, (float)y, (float)settings.panelWidth - 40.0f, 25 }, "F11 - Полный экран");
    y += 25;
    GuiLabel({ (float)px + 20, (float)y, (float)settings.panelWidth - 40.0f, 25 }, "ESC - Выход из тренировки");
}