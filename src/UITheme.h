#pragma once
#include "raylib.h"
#include "raygui.h"

namespace UITheme {
    // Цвета
    constexpr Color BG        = { 18, 22, 28, 255 };
    constexpr Color PANEL     = { 25, 30, 35, 255 };
    constexpr Color BORDER    = { 50, 60, 70, 255 };
    constexpr Color ACCENT    = { 255, 70, 85, 255 };
    constexpr Color TEXT      = { 220, 220, 220, 255 };
    constexpr Color TEXT_DIM  = { 150, 150, 150, 255 };

    // Инициализация стилей raygui
    void Setup();

    // Отрисовка группы настроек (панель с заголовком)
    void DrawTitledGroup(Font font, Rectangle rect, const char* title);
    
    // Отрисовка фона и рамки карточки тренировки
    void DrawCardBackground(Rectangle rect, bool hovered);

    void SetupDefaultStyle();
    void SetupButtonStyle();
    void SetupCheckboxStyle();
    void SetupSliderStyle();
    void SetupTextBoxStyle();
    void SetupValueBoxStyle();
}