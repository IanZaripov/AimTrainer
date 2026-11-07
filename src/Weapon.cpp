#include "Weapon.h"
#include "raymath.h"
#include "rlgl.h"

void Weapon::Draw(const Camera3D& camera) const {
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
    Vector3 up = Vector3CrossProduct(right, forward);

    Vector3 pos = camera.position;
    pos = Vector3Add(pos, Vector3Scale(forward, 0.25f));
    pos = Vector3Add(pos, Vector3Scale(right, 0.12f));
    pos = Vector3Subtract(pos, Vector3Scale(up, 0.12f));

    rlPushMatrix();
    rlTranslatef(pos.x, pos.y, pos.z);
    
    Matrix mat = { 0 };
    mat.m0 = right.x;   mat.m1 = right.y;   mat.m2 = right.z;   mat.m3 = 0.0f;
    mat.m4 = up.x;      mat.m5 = up.y;      mat.m6 = up.z;      mat.m7 = 0.0f;
    mat.m8 = forward.x; mat.m9 = forward.y; mat.m10 = forward.z; mat.m11 = 0.0f;
    mat.m12 = 0.0f;     mat.m13 = 0.0f;     mat.m14 = 0.0f;     mat.m15 = 1.0f;
    rlMultMatrixf(MatrixToFloat(mat));

    DrawSlide();
    DrawBarrel();
    DrawSights();
    DrawGrip();
    DrawHand();
    DrawSleeve();

    rlPopMatrix();
}

void Weapon::DrawSlide() const {
    Color slideColor = Color{ 60, 65, 75, 255 };
    DrawCube({0, 0.01f, 0.05f}, 0.035f, 0.035f, 0.18f, slideColor);
}

void Weapon::DrawBarrel() const {
    Color barrelColor = Color{ 30, 30, 35, 255 };
    DrawCylinderEx({0, 0.01f, 0.14f}, {0, 0.01f, 0.20f}, 0.012f, 0.012f, 8, barrelColor);
}

void Weapon::DrawSights() const {
    DrawCube({0, 0.035f, 0.13f}, 0.008f, 0.01f, 0.01f, BLACK);
    DrawCube({0, 0.035f, -0.02f}, 0.015f, 0.01f, 0.01f, BLACK);
}

void Weapon::DrawGrip() const {
    Color gripColor = Color{ 35, 40, 45, 255 };
    DrawCube({0, -0.05f, -0.01f}, 0.03f, 0.10f, 0.05f, gripColor);
    DrawCube({0, -0.02f, 0.04f}, 0.015f, 0.03f, 0.06f, gripColor);
}

void Weapon::DrawHand() const {
    Color skinColor = Color{ 220, 180, 150, 255 };
    DrawCube({0.01f, -0.08f, -0.01f}, 0.05f, 0.08f, 0.07f, skinColor);
    DrawCube({-0.01f, -0.04f, 0.02f}, 0.02f, 0.04f, 0.03f, skinColor);
}

void Weapon::DrawSleeve() const {
    Color sleeveColor = Color{ 40, 60, 110, 255 };
    DrawCube({0.02f, -0.15f, -0.06f}, 0.07f, 0.12f, 0.12f, sleeveColor);
}