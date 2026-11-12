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

    inline float GetRightButtonX() { 
        return (float)GetRenderWidth() - TopBarButtonW - TopBarPaddingX; 
    }

    namespace Card {
        constexpr float IconCenterY = 120.0f;
        constexpr float IconRadius  = 40.0f;

        constexpr float TitleY      = 220.0f;
        constexpr float Subtitle1Y  = 250.0f;
        constexpr float Subtitle2Y  = 270.0f;
        constexpr float TimedTitleY = 190.0f;

        // Arrows (MovingCard, BouncingCard)
        constexpr float ArrowOffsetX = 60.0f;
        constexpr float ArrowOffsetY = 20.0f;
        constexpr float ArrowSize    = 10.0f;

        // Clock (TimedCard)
        constexpr float TimerHandLength = 25.0f;

        // Difficulty buttons (TimedCard)
        constexpr float DiffBtnY       = 370.0f;
        constexpr float DiffBtnW       = 55.0f;
        constexpr float DiffBtnH       = 25.0f;
        constexpr float DiffBtnSpacing = 60.0f;

        // Card layout on the selection screen
        constexpr float LayoutX       = 40.0f;
        constexpr float LayoutY       = 150.0f;
        constexpr float LayoutWidth   = 210.0f;
        constexpr float LayoutHeight  = 350.0f;
        constexpr float LayoutSpacing = 20.0f;
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