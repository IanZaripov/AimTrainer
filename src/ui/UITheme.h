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

    // --- Top Navigation Bar ---
    namespace TopBar {
        constexpr float Height   = 60.0f;
        constexpr float ButtonY  = 15.0f;
        constexpr float ButtonW  = 120.0f;
        constexpr float ButtonH  = 30.0f;
        constexpr float PaddingX = 20.0f;

        constexpr float Nav1X = 20.0f;   // Trainings
        constexpr float Nav2X = 150.0f;  // Arena
        constexpr float Nav3X = 280.0f;  // Mouse
        constexpr float Nav4X = 410.0f;  // Crosshair
    }

    // Helper for the right-aligned exit button
    inline float GetRightButtonX() { 
        return (float)GetRenderWidth() - TopBar::ButtonW - TopBar::PaddingX; 
    }

    // --- Training Cards ---
    namespace Card {
        // Layout on the selection screen
        namespace Grid {
            constexpr float X       = 40.0f;
            constexpr float Y       = 150.0f;
            constexpr float Width   = 210.0f;
            constexpr float Height  = 350.0f;
            constexpr float Spacing = 20.0f;
        }

        // Internal card elements
        namespace Layout {
            namespace Icon {
                constexpr float CenterY = 120.0f;
                constexpr float Radius  = 40.0f;
            }
            namespace Arrows {
                constexpr float OffsetX = 60.0f;
                constexpr float OffsetY = 20.0f;
                constexpr float Size    = 10.0f;
            }
            namespace Clock {
                constexpr float HandLength = 25.0f;
            }
            namespace Difficulty {
                constexpr float Y       = 370.0f;
                constexpr float Width   = 55.0f;
                constexpr float Height  = 25.0f;
                constexpr float Spacing = 60.0f;
            }
        }

        // Internal card text positions
        namespace Text {
            constexpr float TitleY      = 220.0f;
            constexpr float Subtitle1Y  = 250.0f;
            constexpr float Subtitle2Y  = 270.0f;
            constexpr float TimedTitleY = 190.0f; // For TimedCard (higher due to buttons)
        }
    }

    // --- Individual Screens ---
    namespace Screens {
        namespace Routines {
            constexpr float TitleX = 40.0f;
            constexpr float TitleY = 100.0f;
        }
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