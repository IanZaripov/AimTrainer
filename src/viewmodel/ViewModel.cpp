#include "Viewmodel.h"
#include "WeaponConfig.h"
#include "raymath.h"
#include "rlgl.h"

void Viewmodel::Draw(const Camera3D& camera) const {
    SetupTransform(camera);

    weapon.Draw();
    hands.Draw();

    rlPopMatrix();
}

void Viewmodel::SetupTransform(const Camera3D& camera) const {
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
    Vector3 up = Vector3CrossProduct(right, forward);

    Vector3 pos = camera.position;
    pos = Vector3Add(pos, Vector3Scale(forward, WeaponConfig::OffsetForward));
    pos = Vector3Add(pos, Vector3Scale(right, WeaponConfig::OffsetRight));
    pos = Vector3Subtract(pos, Vector3Scale(up, WeaponConfig::OffsetDown));

    rlPushMatrix();
    rlTranslatef(pos.x, pos.y, pos.z);
    
    Matrix mat = { 0 };
    mat.m0 = right.x;   mat.m1 = right.y;   mat.m2 = right.z;   mat.m3 = 0.0f;
    mat.m4 = up.x;      mat.m5 = up.y;      mat.m6 = up.z;      mat.m7 = 0.0f;
    mat.m8 = forward.x; mat.m9 = forward.y; mat.m10 = forward.z; mat.m11 = 0.0f;
    mat.m12 = 0.0f;     mat.m13 = 0.0f;     mat.m14 = 0.0f;     mat.m15 = 1.0f;
    rlMultMatrixf(MatrixToFloat(mat));
}