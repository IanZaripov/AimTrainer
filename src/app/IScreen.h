#pragma once
#include "raylib.h"

class ScreenManager;

class IScreen {
public:
    virtual ~IScreen() = default;
    virtual void Update(ScreenManager& manager) = 0;
    virtual void Draw(Font uiFont, ScreenManager& manager) = 0;
};