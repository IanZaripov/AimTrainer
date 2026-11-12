#pragma once
#include "IScreen.h"

class Settings;

class ArenaSettingsScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override;
    void Draw(Font uiFont, ScreenManager& manager) override;

private:
    bool isDirty = false;
    char distBuffer[16] = "15";
    bool distEdit = false;
    char sizeBuffer[16] = "0.30";
    bool sizeEdit = false;

    void DrawTitle(Font uiFont) const;
    bool DrawDistanceGroup(Font uiFont, Settings& settings);
    bool DrawColorGroup(Font uiFont, Settings& settings);
    bool DrawSizeGroup(Font uiFont, Settings& settings);

    void DrawPreview(Font uiFont, const Settings& settings) const;
    void drawBackGroundAndFlorPreview(Rectangle previewBox) const;
    void DrawTargetPreview(Font uiFont, Rectangle previewBox, const Settings& settings) const;
    float CalculatePixelRadius(const Settings& settings) const;
    void DrawTargetCircle(Rectangle previewBox, const Settings& settings, float pxRadius) const;
    void DrawInfoText(Font uiFont, Rectangle previewBox, const Settings& settings, float pxRadius) const;
};