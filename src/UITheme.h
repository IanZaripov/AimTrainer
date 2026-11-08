#pragma once
#include "raylib.h"
#include "raygui.h"

namespace UITheme {
    constexpr Color BG        = { 18, 22, 28, 255 };
    constexpr Color PANEL     = { 25, 30, 35, 255 };
    constexpr Color BORDER    = { 50, 60, 70, 255 };
    constexpr Color ACCENT    = { 255, 70, 85, 255 };
    constexpr Color TEXT      = { 220, 220, 220, 255 };
    constexpr Color TEXT_DIM  = { 150, 150, 150, 255 };

    // Виртуальное разрешение (эталон)
    constexpr int VirtualHeight = 1080;

    constexpr float TopBarHeight   = 60.0f;
    constexpr float TopBarButtonY  = 15.0f;
    constexpr float TopBarButtonW  = 120.0f;
    constexpr float TopBarButtonH  = 30.0f;
    constexpr float TopBarPaddingX = 20.0f;

    constexpr float NavButton1X = 20.0f;
    constexpr float NavButton2X = 150.0f;
    constexpr float NavButton3X = 280.0f;
    constexpr float NavButton4X = 410.0f;

    // Привязка к правому краю (использует виртуальную ширину)
    inline float GetRightButtonX() { 
        return (float)GetRenderWidth() - TopBarButtonW - TopBarPaddingX; 
    }

    void Setup();
    void DrawTitledGroup(Font font, Rectangle rect, const char* title);
    void DrawCardBackground(Rectangle rect, bool hovered);

    void SetupDefaultStyle();
    void SetupButtonStyle();
    void SetupCheckboxStyle();
    void SetupSliderStyle();
    void SetupTextBoxStyle();
    void SetupValueBoxStyle();
}