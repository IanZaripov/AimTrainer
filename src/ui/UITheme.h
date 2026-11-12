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
        constexpr float TitleY   = 18.0f;
        constexpr float TitleFontSize = 24.0f;

        constexpr float Nav1X = 20.0f;
        constexpr float Nav2X = 150.0f;
        constexpr float Nav3X = 280.0f;
        constexpr float Nav4X = 410.0f;
    }

    inline float GetRightButtonX() { 
        return (float)GetRenderWidth() - TopBar::ButtonW - TopBar::PaddingX; 
    }

    // --- Common Widgets ---
    namespace Widgets {
        namespace SliderBox {
            constexpr float LabelFontSize = 16.0f;
            constexpr float SliderWidth = 200.0f;
            constexpr float SliderHeight = 20.0f;
            constexpr float SliderYOffset = 25.0f;
            constexpr float TextBoxXOffset = 220.0f;
            constexpr float TextBoxYOffset = 25.0f;
            constexpr float TextBoxWidth = 80.0f;
            constexpr float TextBoxHeight = 30.0f;
        }
        namespace ColorPicker {
            constexpr float ButtonSize = 30.0f;
            constexpr float ButtonSpacing = 40.0f;
            constexpr float BorderThicknessNormal = 1.0f;
            constexpr float BorderThicknessSelected = 2.0f;
        }
    }

    // --- Training Cards ---
    namespace Card {
        namespace Grid {
            constexpr float X       = 40.0f;
            constexpr float Y       = 150.0f;
            constexpr float Width   = 210.0f;
            constexpr float Height  = 350.0f;
            constexpr float Spacing = 20.0f;
        }
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
                constexpr float ButtonXOffset = 15.0f;
                constexpr float FontSize = 12.0f;
            }
        }
        namespace Text {
            constexpr float TitleX = 20.0f;
            constexpr float TitleY      = 220.0f;
            constexpr float SubtitleX = 15.0f;
            constexpr float Subtitle1Y  = 250.0f;
            constexpr float Subtitle2Y  = 270.0f;
            constexpr float TimedTitleY = 190.0f;
            constexpr float TitleFontSize = 20.0f;
            constexpr float SubtitleFontSize = 12.0f;
        }
    }

    // --- Screens ---
    namespace Screens {
        namespace Routines {
            constexpr float TitleX = 40.0f;
            constexpr float TitleY = 100.0f;
            constexpr float TitleFontSize = 20.0f;
        }

        namespace Settings {
            constexpr float TitleX = 40.0f;
            constexpr float TitleY = 90.0f;
            constexpr float TitleFontSize = 24.0f;
            constexpr float GroupX = 40.0f;
            constexpr float GroupWidth = 350.0f;
            constexpr float GroupRoundness = 0.05f;
            constexpr float GroupSegments = 4.0f;
            constexpr float GroupBorderThickness = 1.0f;
            constexpr float GroupTitleOffsetX = 15.0f;
            constexpr float GroupTitleOffsetY = 10.0f;
            constexpr float GroupTitleFontSize = 14.0f;
            constexpr float GroupSeparatorYOffset = 30.0f;
            constexpr float GroupSeparatorPadding = 15.0f;

            namespace Mouse {
                constexpr float SensGroupY = 140.0f;
                constexpr float SensGroupH = 100.0f;
                constexpr float SensLabelX = 60.0f;
                constexpr float SensLabelY = 180.0f;

                constexpr float MultGroupY = 260.0f;
                constexpr float MultGroupH = 100.0f;
                constexpr float MultLabelX = 60.0f;
                constexpr float MultLabelY = 300.0f;
            }

            namespace Crosshair {
                constexpr float FormGroupY = 140.0f;
                constexpr float FormGroupH = 210.0f;
                constexpr float FormLabelX = 60.0f;
                constexpr float FormLabelStartY = 180.0f;
                constexpr float FormRowSpacing = 50.0f;

                constexpr float ExtraGroupY = 370.0f;
                constexpr float ExtraGroupH = 100.0f;
                constexpr float ExtraCheckboxX = 60.0f;
                constexpr float ExtraCheckbox1Y = 400.0f;
                constexpr float ExtraCheckbox2Y = 430.0f;

                constexpr float ColorGroupY = 490.0f;
                constexpr float ColorGroupH = 90.0f;
                constexpr float ColorPickerX = 60.0f;
                constexpr float ColorPickerY = 520.0f;

                constexpr float PreviewX = 420.0f;
                constexpr float PreviewY = 140.0f;
                constexpr float PreviewW = 500.0f;
                constexpr float PreviewH = 440.0f;
                constexpr float PreviewFloorY = 300.0f;
                constexpr float PreviewCenterYOffset = -50.0f;
                constexpr float PreviewRoundness = 0.02f;
                constexpr float PreviewBorderThickness = 2.0f;
            }

            namespace ArenaSettings {
                constexpr float DistGroupY = 140.0f;
                constexpr float DistGroupH = 100.0f;
                constexpr float DistLabelX = 60.0f;
                constexpr float DistLabelY = 180.0f;

                constexpr float ColorGroupY = 260.0f;
                constexpr float ColorGroupH = 100.0f;
                constexpr float ColorPickerX = 60.0f;
                constexpr float ColorPickerY = 300.0f;

                constexpr float SizeGroupY = 380.0f;
                constexpr float SizeGroupH = 100.0f;
                constexpr float SizeLabelX = 60.0f;
                constexpr float SizeLabelY = 420.0f;

                constexpr float PreviewX = 420.0f;
                constexpr float PreviewY = 140.0f;
                constexpr float PreviewW = 500.0f;
                constexpr float PreviewH = 340.0f;
                constexpr float PreviewFloorY = 250.0f;
                constexpr float PreviewCenterYOffset = -30.0f;
                constexpr float PreviewInfoYOffset = -40.0f;
                constexpr float PreviewRoundness = 0.02f;
                constexpr float PreviewBorderThickness = 2.0f;
            }
        }

        namespace Results {
            constexpr float PanelWidth = 500.0f;
            constexpr float PanelHeight = 450.0f;
            constexpr float PanelRoundness = 0.05f;
            constexpr int PanelSegments = 4;
            constexpr float PanelBorderThickness = 2.0f;
            
            constexpr float TitleFontSize = 32.0f;
            constexpr float TitleYOffset = 30.0f;
            constexpr float SeparatorYOffset = 80.0f;
            constexpr float SeparatorPaddingX = 20.0f;
            constexpr float SeparatorThickness = 1.0f;
            
            constexpr float StatsStartY = 110.0f;
            constexpr float StatLabelX = 50.0f;
            constexpr float StatValueX = 300.0f;
            constexpr float StatRowSpacing = 40.0f;
            constexpr float StatFontSize = 20.0f;
            
            constexpr float Btn1X = 50.0f;
            constexpr float Btn2X = 270.0f;
            constexpr float BtnY = 350.0f;
            constexpr float BtnWidth = 180.0f;
            constexpr float BtnHeight = 40.0f;
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