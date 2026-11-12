#include "UITheme.h"

namespace UITheme {

    void Setup() {
        SetupDefaultStyle();
        SetupButtonStyle();
        SetupCheckboxStyle();
        SetupSliderStyle();
        SetupTextBoxStyle();
        SetupValueBoxStyle();
    }

    void SetupDefaultStyle() {
        // Базовые настройки для всех элементов (текст, фон, рамки)
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(TEXT));
        GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt(BORDER));
        GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(PANEL));
    }

    void SetupButtonStyle() {
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(BG)); 
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(BORDER));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(ACCENT)); 
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(TEXT));
    }

    void SetupCheckboxStyle() {
        GuiSetStyle(CHECKBOX, BASE_COLOR_NORMAL, ColorToInt(PANEL));
        GuiSetStyle(CHECKBOX, BORDER_COLOR_NORMAL, ColorToInt(BORDER));
        GuiSetStyle(CHECKBOX, TEXT_COLOR_NORMAL, ColorToInt(TEXT));
        GuiSetStyle(CHECKBOX, BASE_COLOR_PRESSED, ColorToInt(ACCENT));
    }

    void SetupSliderStyle() {
        GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, ColorToInt(WHITE));
        GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, ColorToInt(BORDER));
        GuiSetStyle(SLIDER, BASE_COLOR_PRESSED, ColorToInt(ACCENT));
    }

    void SetupTextBoxStyle() {
        GuiSetStyle(TEXTBOX, BASE_COLOR_NORMAL, ColorToInt(BG));
        GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, ColorToInt(BORDER));
    }

    void SetupValueBoxStyle() {
        // Styles for the slider runner
        GuiSetStyle(VALUEBOX, BASE_COLOR_NORMAL, ColorToInt(BLACK));
        GuiSetStyle(VALUEBOX, BORDER_COLOR_NORMAL, ColorToInt(WHITE));
    }

    void DrawTitledGroup(Font font, Rectangle rect, const char* title) {
        DrawRectangleRounded(rect, Screens::Settings::GroupRoundness, Screens::Settings::GroupSegments, PANEL);
        DrawRectangleLinesEx(rect, Screens::Settings::GroupBorderThickness, BORDER);
        DrawTextEx(font, title, { rect.x + Screens::Settings::GroupTitleOffsetX, rect.y + Screens::Settings::GroupTitleOffsetY }, Screens::Settings::GroupTitleFontSize, 1, ACCENT);
        DrawLine((int)rect.x + Screens::Settings::GroupSeparatorPadding, (int)rect.y + Screens::Settings::GroupSeparatorYOffset, (int)(rect.x + rect.width - Screens::Settings::GroupSeparatorPadding), (int)rect.y + Screens::Settings::GroupSeparatorYOffset, BORDER);
    }

    void DrawCardBackground(Rectangle rect, bool hovered) {
        Color bg = hovered ? Color{ 30, 35, 45, 255 } : PANEL;
        Color border = hovered ? ACCENT : BORDER;
        float thickness = hovered ? 2.0f : 1.0f;
        
        DrawRectangleRec(rect, bg);
        DrawRectangleLinesEx(rect, thickness, border);
    }
}