#pragma once

class Weapon {
public:
    void Draw() const;

private:
    void DrawSlide() const;
    void DrawBarrel() const;
    void DrawGrip() const;
};