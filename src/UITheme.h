#pragma once
#include "raylib.h"
#include "raygui.h"

namespace UITheme {
    // Все цвета интерфейса в одном месте
    constexpr Color BG        = { 18, 22, 28, 255 };
    constexpr Color PANEL     = { 25, 30, 35, 255 };
    constexpr Color BORDER    = { 50, 60, 70, 255 };
    constexpr Color ACCENT    = { 255, 70, 85, 255 };
    constexpr Color TEXT      = { 220, 220, 220, 255 };
    constexpr Color TEXT_DIM  = { 150, 150, 150, 255 };

    // Инициализация стилей raygui (вызывается 1 раз)
    void Setup();

    // Отрисовка стандартной панели с заголовком
    void DrawPanel(Font font, Rectangle rect, const char* title);
    
    // Отрисовка карточки тренировки (рамка + фон)
    void DrawCardFrame(Rectangle rect, bool hovered);
}