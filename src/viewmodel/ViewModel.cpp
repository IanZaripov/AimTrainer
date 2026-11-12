#include "Viewmodel.h"
#include "WeaponConfig.h"
#include "raymath.h"
#include "rlgl.h"

void Viewmodel::Draw(const Camera3D& camera) const {
    BeginViewmodelSpace(camera);

    weapon.Draw();
    hands.Draw();

    EndViewmodelSpace();
}

void Viewmodel::BeginViewmodelSpace(const Camera3D& camera) const {
    CameraBasis basis = CalculateCameraBasis(camera);
    Vector3 pos = CalculateViewmodelPosition(camera, basis);

    rlPushMatrix();
    rlTranslatef(pos.x, pos.y, pos.z);
    ApplyCameraOrientation(basis);

}

void Viewmodel::EndViewmodelSpace() const {
    rlPopMatrix();
}

Viewmodel::CameraBasis Viewmodel::CalculateCameraBasis(const Camera3D& camera) const {
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
    Vector3 up = Vector3CrossProduct(right, forward);
    return { forward, right, up };
}

Vector3 Viewmodel::CalculateViewmodelPosition(const Camera3D& camera, const CameraBasis& basis) const {
    Vector3 pos = camera.position;
    pos = Vector3Add(pos, Vector3Scale(basis.forward, WeaponConfig::Offsets::Forward));
    pos = Vector3Add(pos, Vector3Scale(basis.right, WeaponConfig::Offsets::Right));
    pos = Vector3Subtract(pos, Vector3Scale(basis.up, WeaponConfig::Offsets::Down));
    return pos;
}

void Viewmodel::ApplyCameraOrientation(const CameraBasis& basis) const {
    Matrix mat = { 0 };
    mat.m0 = basis.right.x;   mat.m1 = basis.right.y;   mat.m2 = basis.right.z;   mat.m3 = 0.0f;
    mat.m4 = basis.up.x;      mat.m5 = basis.up.y;      mat.m6 = basis.up.z;      mat.m7 = 0.0f;
    mat.m8 = basis.forward.x; mat.m9 = basis.forward.y; mat.m10 = basis.forward.z; mat.m11 = 0.0f;
    mat.m12 = 0.0f;           mat.m13 = 0.0f;           mat.m14 = 0.0f;           mat.m15 = 1.0f;
    rlMultMatrixf(MatrixToFloat(mat));
}