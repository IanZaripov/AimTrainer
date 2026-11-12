#include "Weapon.h"
#include "WeaponConfig.h"
#include "raylib.h"

void Weapon::Draw() const {
    DrawSlide();
    DrawBarrel();
    DrawGrip();
}

void Weapon::DrawSlide() const {
    DrawCube(WeaponConfig::Slide::Pos, 
             WeaponConfig::Slide::Size.x, 
             WeaponConfig::Slide::Size.y, 
             WeaponConfig::Slide::Size.z, 
             WeaponConfig::Slide::color);
}

void Weapon::DrawBarrel() const {
    DrawCylinderEx(WeaponConfig::Barrel::Start,
                   WeaponConfig::Barrel::End,
                   WeaponConfig::Barrel::Radius,
                   WeaponConfig::Barrel::Radius,
                   WeaponConfig::Barrel::Sides,
                   WeaponConfig::Barrel::color);
}

void Weapon::DrawGrip() const {
    DrawCube(WeaponConfig::Grip::Pos, 
             WeaponConfig::Grip::Size.x, 
             WeaponConfig::Grip::Size.y, 
             WeaponConfig::Grip::Size.z, 
             WeaponConfig::Grip::color);
}