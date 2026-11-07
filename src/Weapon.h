#pragma once
#include "raylib.h"

class Weapon {
public:
    void Draw(const Camera3D& camera) const;
private:
    void DrawSlide() const;
    void DrawBarrel() const;
    void DrawSights() const;
    void DrawGrip() const;
    void DrawHand() const;
    void DrawSleeve() const;
};