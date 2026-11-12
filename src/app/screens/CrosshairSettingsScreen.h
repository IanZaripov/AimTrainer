#pragma once
#include "IScreen.h"

class CrosshairSettingsScreen : public IScreen {
public:
    void Update(ScreenManager& manager) override;
    void Draw(Font uiFont, ScreenManager& manager) override;
private:
    bool isDirty = false;
    char lenBuffer[16] = "4", thicBuffer[16] = "1", gapBuffer[16] = "0";
    bool lenEdit = false, thicEdit = false, gapEdit = false;
};