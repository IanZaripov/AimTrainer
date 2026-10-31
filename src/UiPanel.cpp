#include "UiPanel.h"

UiPanel::UiPanel(Game& g, int sw, int pw)
    : game(g), screenWidth(sw), panelWidth(pw) {}

void UiPanel::Draw() {
    int px = panelX();
    DrawRectangle(px, 0, panelWidth, GetScreenHeight(), Color{ 25, 25, 30, 255 });

    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(LIGHTGRAY));

    int y = 30;
    GuiLabel({ (float)px + 20, (float)y, panelWidth - 40.0f, 30 }, "VALORANT AIM TRAINER");
    y += 45;

    GuiLabel({ (float)px + 20, (float)y, panelWidth - 40.0f, 25 }, "Режим: Шарики (голова)");
    y += 35;

    if (!game.IsTrainingActive()) {
        if (GuiButton({ (float)px + 20, (float)y, 200, 40 }, "НАЧАТЬ ТРЕНИРОВКУ")) {
            game.StartTraining();
        }
    } else {
        if (GuiButton({ (float)px + 20, (float)y, 200, 40 }, "ОСТАНОВИТЬ")) {
            game.StopTraining();
        }
    }
    y += 60;

    GuiLabel({ (float)px + 20, (float)y, panelWidth - 40.0f, 25 },
             TextFormat("Лопнуто шариков: %d", game.GetPoppedCount()));
    y += 30;

    float accuracy = (game.GetShotsFired() > 0)
        ? 100.0f * game.GetHits() / game.GetShotsFired()
        : 0.0f;
    GuiLabel({ (float)px + 20, (float)y, panelWidth - 40.0f, 25 },
             TextFormat("Точность: %.1f%%", accuracy));
    y += 30;

    GuiLabel({ (float)px + 20, (float)y, panelWidth - 40.0f, 25 },
             TextFormat("Выстрелов: %d", game.GetShotsFired()));
}