#pragma once
#include "IScreen.h"

class Settings;

class CrosshairSettingsScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override;
    void Draw(Font uiFont, ScreenManager& manager) override;

private:
    bool isDirty = false;
    char lenBuffer[16] = "4", thicBuffer[16] = "1", gapBuffer[16] = "0";
    bool lenEdit = false, thicEdit = false, gapEdit = false;

    void DrawTitle(Font uiFont) const;
    bool DrawFormGroup(Font uiFont, Settings& settings);
    bool DrawExtraGroup(Font uiFont, Settings& settings);
    bool DrawColorGroup(Font uiFont, Settings& settings);
    
    void DrawPreview(Font uiFont, const Settings& settings) const;
    void drawBackGroundAndFlorPreview(Rectangle previewBox) const;
    void DrawCrosshairPreview(const Settings& settings) const;

    // --- New methods for crosshair components ---
    void DrawOutline(float cx, float cy, float len, float thic, float gap) const;
    void DrawMainLines(float cx, float cy, float len, float thic, float gap, Color color) const;
    void DrawCenterDot(float cx, float cy, float thic, Color color) const;
};