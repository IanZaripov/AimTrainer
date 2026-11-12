#pragma once
#include "raylib.h"
#include "Weapon.h"
#include "Hands.h"

class Viewmodel {
public:
    void Draw(const Camera3D& camera) const;

private:
    Weapon weapon;
    Hands  hands;

    struct CameraBasis {
        Vector3 forward;
        Vector3 right;
        Vector3 up;
    };

    void BeginViewmodelSpace(const Camera3D& camera) const;
    void EndViewmodelSpace() const;

    CameraBasis CalculateCameraBasis(const Camera3D& camera) const;
    Vector3 CalculateViewmodelPosition(const Camera3D& camera, const CameraBasis& basis) const;
    void ApplyCameraOrientation(const CameraBasis& basis) const;
};