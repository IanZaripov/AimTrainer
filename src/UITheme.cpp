#include "UITheme.h"

namespace UITheme {
    void Setup() {
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(TEXT));
        GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt(BORDER));
        GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(PANEL));
        
        GuiSetStyle(CHECKBOX, BASE_COLOR_NORMAL, ColorToInt(PANEL));
        GuiSetStyle(CHECKBOX, BORDER_COLOR_NORMAL, ColorToInt(BORDER));
        GuiSetStyle(CHECKBOX, TEXT_COLOR_NORMAL, ColorToInt(TEXT));
        GuiSetStyle(CHECKBOX, BASE_COLOR_PRESSED, ColorToInt(ACCENT));
        
        GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, ColorToInt(WHITE));
        GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, ColorToInt(BORDER));
        GuiSetStyle(SLIDER, BASE_COLOR_PRESSED, ColorToInt(ACCENT));
        
        GuiSetStyle(VALUEBOX, BASE_COLOR_NORMAL, ColorToInt(BLACK));
        GuiSetStyle(VALUEBOX, BORDER_COLOR_NORMAL, ColorToInt(WHITE));
        
        GuiSetStyle(TEXTBOX, BASE_COLOR_NORMAL, ColorToInt(BG));
        GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, ColorToInt(BORDER));

        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(BG)); 
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(BORDER));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(ACCENT)); 
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(TEXT));
    }

    void DrawPanel(Font font, Rectangle rect, const char* title) {
        DrawRectangleRounded(rect, 0.05f, 4, PANEL);
        DrawRectangleLinesEx(rect, 1.0f, BORDER);
        DrawTextEx(font, title, { rect.x + 15, rect.y + 10 }, 14, 1, ACCENT);
        DrawLine((int)rect.x + 15, (int)rect.y + 30, (int)(rect.x + rect.width - 15), (int)rect.y + 30, BORDER);
    }

    void DrawCardFrame(Rectangle rect, bool hovered) {
        DrawRectangleRec(rect, hovered ? Color{ 30, 35, 45, 255 } : PANEL);
        DrawRectangleLinesEx(rect, hovered ? 2.0f : 1.0f, hovered ? ACCENT : BORDER);
    }
}