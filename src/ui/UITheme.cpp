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
        // Basic settings for all elements (text, background, frames)
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(TEXT));
        GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt(BORDER));
        GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(PANEL));
    }

    void SetupButtonStyle() {
        // Neutralize raygui default styling (in case we miss a GuiButton somewhere)
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(Color{ 20, 24, 30, 255 })); 
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(Color{ 32, 38, 46, 255 }));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(ACCENT)); 
        
        // No visible border
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(Color{ 20, 24, 30, 255 }));
        GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(Color{ 20, 24, 30, 255 }));
        GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(ACCENT));
        
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(TEXT));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(WHITE));
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
        
        // Tactical corner ticks (top-left + bottom-right)
        float t = Accent::CornerTickLength;
        float th = Accent::CornerTickThickness;
        Color c = Accent::TickIdle;
        
        // Top-left
        DrawLineEx({rect.x, rect.y + t}, {rect.x, rect.y}, th, c);
        DrawLineEx({rect.x, rect.y}, {rect.x + t, rect.y}, th, c);
        // Bottom-right
        DrawLineEx({rect.x + rect.width - t, rect.y + rect.height}, {rect.x + rect.width, rect.y + rect.height}, th, c);
        DrawLineEx({rect.x + rect.width, rect.y + rect.height - t}, {rect.x + rect.width, rect.y + rect.height}, th, c);
        
        // Small accent line before the title
        DrawRectangle(rect.x + 10, rect.y + 12, 3, 16, ACCENT);
        
        DrawTextEx(font, title, 
            { rect.x + Screens::Settings::GroupTitleOffsetX + 6, rect.y + Screens::Settings::GroupTitleOffsetY }, 
            Screens::Settings::GroupTitleFontSize, 1, ACCENT);
        DrawLine((int)rect.x + Screens::Settings::GroupSeparatorPadding, 
                (int)rect.y + Screens::Settings::GroupSeparatorYOffset, 
                (int)(rect.x + rect.width - Screens::Settings::GroupSeparatorPadding), 
                (int)rect.y + Screens::Settings::GroupSeparatorYOffset, BORDER);
    }

    void DrawCardBackground(Rectangle rect, bool hovered) {
        Color bg = hovered ? Color{ 32, 38, 46, 255 } : PANEL;
        Color border = hovered ? ACCENT : BORDER;
        float thickness = hovered ? 2.0f : 1.0f;
        
        DrawRectangleRec(rect, bg);
        DrawRectangleLinesEx(rect, thickness, border);
        
        // Tactical corner ticks
        float t = Accent::CornerTickLength;
        float th = Accent::CornerTickThickness;
        Color c = hovered ? ACCENT : Accent::TickIdle;
        
        // Top-left
        DrawLineEx({rect.x, rect.y + t}, {rect.x, rect.y}, th, c);
        DrawLineEx({rect.x, rect.y}, {rect.x + t, rect.y}, th, c);
        // Top-right
        DrawLineEx({rect.x + rect.width - t, rect.y}, {rect.x + rect.width, rect.y}, th, c);
        DrawLineEx({rect.x + rect.width, rect.y}, {rect.x + rect.width, rect.y + t}, th, c);
        // Bottom-left
        DrawLineEx({rect.x, rect.y + rect.height - t}, {rect.x, rect.y + rect.height}, th, c);
        DrawLineEx({rect.x, rect.y + rect.height}, {rect.x + t, rect.y + rect.height}, th, c);
        // Bottom-right
        DrawLineEx({rect.x + rect.width - t, rect.y + rect.height}, {rect.x + rect.width, rect.y + rect.height}, th, c);
        DrawLineEx({rect.x + rect.width, rect.y + rect.height - t}, {rect.x + rect.width, rect.y + rect.height}, th, c);
        
        // Left accent bar on hover
        if (hovered) {
            DrawRectangle(rect.x, rect.y + 15, Accent::ButtonAccentBarWidth, (int)rect.height - 30, ACCENT);
        }
    }
}