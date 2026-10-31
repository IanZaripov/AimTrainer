#include "Weapon.h"
#include "raymath.h"

void Weapon::Draw(const Camera3D& camera) const {
    // Базис камеры
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
    Vector3 up = Vector3CrossProduct(right, forward);

    // Позиция оружия (справа, снизу, впереди)
    Vector3 pos = camera.position;
    pos = Vector3Add(pos, Vector3Scale(forward, 0.35f));
    pos = Vector3Add(pos, Vector3Scale(right, 0.18f));
    pos = Vector3Subtract(pos, Vector3Scale(up, 0.15f));

    // --- МОДЕЛЬ ПИСТОЛЕТА (BANDIT / SHERIFF) ---
    
    // Рукоятка (темная)
    Vector3 gripPos = Vector3Add(pos, Vector3Scale(up, -0.1f));
    DrawCube(gripPos, 0.06f, 0.15f, 0.08f, Color{ 40, 40, 45, 255 });

    // Основной корпус (слайд)
    Vector3 slidePos = Vector3Add(pos, Vector3Scale(up, 0.03f));
    DrawCube(slidePos, 0.06f, 0.06f, 0.25f, Color{ 80, 85, 90, 255 });

    // Ствол (цилиндр)
    Vector3 barrelStart = Vector3Add(slidePos, Vector3Scale(forward, 0.12f));
    Vector3 barrelEnd = Vector3Add(barrelStart, Vector3Scale(forward, 0.1f));
    DrawCylinderEx(barrelStart, barrelEnd, 0.025f, 0.025f, 8, Color{ 60, 60, 65, 255 });

    // Курок / прицельные (мелочи для детализации)
    Vector3 sightPos = Vector3Add(slidePos, Vector3Scale(up, 0.04f));
    DrawCube(sightPos, 0.01f, 0.02f, 0.02f, BLACK);

    // --- РУКА ---
    // Ладонь
    Vector3 handPos = Vector3Add(gripPos, Vector3Scale(up, -0.06f));
    DrawCube(handPos, 0.08f, 0.1f, 0.1f, Color{ 220, 180, 150, 255 });
    
    // Большой палец
    Vector3 thumbPos = Vector3Add(gripPos, Vector3Scale(right, -0.04f));
    thumbPos = Vector3Add(thumbPos, Vector3Scale(up, -0.02f));
    DrawCube(thumbPos, 0.03f, 0.06f, 0.04f, Color{ 220, 180, 150, 255 });
    
    // Рукав (синий, как у агентов)
    Vector3 sleevePos = Vector3Add(handPos, Vector3Scale(forward, -0.15f));
    sleevePos = Vector3Add(sleevePos, Vector3Scale(right, 0.05f));
    DrawCube(sleevePos, 0.1f, 0.1f, 0.3f, Color{ 30, 50, 100, 255 });
}