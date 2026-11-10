#include "Weapon.h"
#include "WeaponConfig.h"

void Weapon::Draw() const {
    DrawSlide();
    DrawBarrel();
    DrawSights();
    DrawGrip();
}

void Weapon::DrawSlide() const {
    DrawCube(WeaponConfig::SlidePos, 
             WeaponConfig::SlideSize.x, 
             WeaponConfig::SlideSize.y, 
             WeaponConfig::SlideSize.z, 
             WeaponConfig::SlideColor);
}

void Weapon::DrawBarrel() const {
    DrawCylinderEx(WeaponConfig::BarrelStart, 
                   WeaponConfig::BarrelEnd, 
                   WeaponConfig::BarrelRadius, 
                   WeaponConfig::BarrelRadius, 
                   WeaponConfig::BarrelSides, 
                   WeaponConfig::BarrelColor);
}

void Weapon::DrawSights() const {
    DrawCube(WeaponConfig::FrontSightPos, 
             WeaponConfig::FrontSightSize.x, 
             WeaponConfig::FrontSightSize.y, 
             WeaponConfig::FrontSightSize.z, 
             BLACK);
    DrawCube(WeaponConfig::RearSightPos, 
             WeaponConfig::RearSightSize.x, 
             WeaponConfig::RearSightSize.y, 
             WeaponConfig::RearSightSize.z, 
             BLACK);
}

void Weapon::DrawGrip() const {
    DrawCube(WeaponConfig::GripPos, 
             WeaponConfig::GripSize.x, 
             WeaponConfig::GripSize.y, 
             WeaponConfig::GripSize.z, 
             WeaponConfig::GripColor);
    DrawCube(WeaponConfig::TriggerGuardPos, 
             WeaponConfig::TriggerGuardSize.x, 
             WeaponConfig::TriggerGuardSize.y, 
             WeaponConfig::TriggerGuardSize.z, 
             WeaponConfig::GripColor);
}