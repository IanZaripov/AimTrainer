#include "Weapon.h"
#include "WeaponConfig.h"
#include "raymath.h"
#include "rlgl.h"

void Weapon::Draw(const Camera3D& camera) const {
    SetupWeaponTransform(camera);

    DrawSlide();
    DrawBarrel();
    DrawSights();
    DrawGrip();
    DrawHand();
    DrawSleeve();

    rlPopMatrix(); // Восстанавливаем матрицу
}

// Этот метод создает локальную систему координат для оружия, 
// чтобы нам не приходилось считать мировые координаты для каждой детали
void Weapon::SetupWeaponTransform(const Camera3D& camera) const {
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
    Vector3 up = Vector3CrossProduct(right, forward);

    // Вычисляем позицию оружия в мире (относительно камеры)
    Vector3 pos = camera.position;
    pos = Vector3Add(pos, Vector3Scale(forward, WeaponConfig::OffsetForward));
    pos = Vector3Add(pos, Vector3Scale(right, WeaponConfig::OffsetRight));
    pos = Vector3Subtract(pos, Vector3Scale(up, WeaponConfig::OffsetDown));

    // Применяем трансформации
    rlPushMatrix();
    rlTranslatef(pos.x, pos.y, pos.z);
    
    // Создаем матрицу поворота, чтобы локальная ось Z смотрела вперед, Y — вверх, X — вправо
    Matrix mat = { 0 };
    mat.m0 = right.x;   mat.m1 = right.y;   mat.m2 = right.z;   mat.m3 = 0.0f;
    mat.m4 = up.x;      mat.m5 = up.y;      mat.m6 = up.z;      mat.m7 = 0.0f;
    mat.m8 = forward.x; mat.m9 = forward.y; mat.m10 = forward.z; mat.m11 = 0.0f;
    mat.m12 = 0.0f;     mat.m13 = 0.0f;     mat.m14 = 0.0f;     mat.m15 = 1.0f;
    rlMultMatrixf(MatrixToFloat(mat));
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

void Weapon::DrawHand() const {
    DrawCube(WeaponConfig::HandPos, 
             WeaponConfig::HandSize.x, 
             WeaponConfig::HandSize.y, 
             WeaponConfig::HandSize.z, 
             WeaponConfig::SkinColor);
             
    DrawCube(WeaponConfig::ThumbPos, 
             WeaponConfig::ThumbSize.x, 
             WeaponConfig::ThumbSize.y, 
             WeaponConfig::ThumbSize.z, 
             WeaponConfig::SkinColor);
}

void Weapon::DrawSleeve() const {
    DrawCube(WeaponConfig::SleevePos, 
             WeaponConfig::SleeveSize.x, 
             WeaponConfig::SleeveSize.y, 
             WeaponConfig::SleeveSize.z, 
             WeaponConfig::SleeveColor);
}