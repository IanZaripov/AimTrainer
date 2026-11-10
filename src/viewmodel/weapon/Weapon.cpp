#include "Weapon.h"
#include "WeaponConfig.h"
#include "raylib.h"

void Weapon::Draw() const {
    // Затвор
    DrawCube(WeaponConfig::SlidePos, WeaponConfig::SlideSize.x, WeaponConfig::SlideSize.y, WeaponConfig::SlideSize.z, WeaponConfig::SlideColor);
    // Ствол
    DrawCylinderEx(WeaponConfig::BarrelStart, WeaponConfig::BarrelEnd, WeaponConfig::BarrelRadius, WeaponConfig::BarrelRadius, WeaponConfig::BarrelSides, WeaponConfig::BarrelColor);
    // Рукоять
    DrawCube(WeaponConfig::GripPos, WeaponConfig::GripSize.x, WeaponConfig::GripSize.y, WeaponConfig::GripSize.z, WeaponConfig::GripColor);
}