#include "Target3D.h"

Target3D::Target3D() = default;

void Target3D::Hit() {
    active = false;
    isExploding = true;
    explosionLife = GameConfig::EffectLifetime;
}

void Target3D::ForceKill() {
    active = false;
    isExploding = false;
}

void Target3D::Update(float dt) {
    if (isExploding) {
        explosionLife -= dt;
        if (explosionLife <= 0.0f) {
            isExploding = false;
        }
    }
}

void Target3D::Draw(const Settings& settings) const {
    if (active) {
        DrawSphere(position, settings.arena.targetRadius, settings.arena.ballColor);
    }
    
    if (isExploding) {
        float progress = 1.0f - (explosionLife / GameConfig::EffectLifetime); 
        float radius = settings.arena.targetRadius * (1.0f + progress * GameConfig::EffectMaxScale); 
        
        Color col = settings.arena.ballColor;
        col.a = (unsigned char)(255 * (1.0f - progress));
        
        DrawSphereWires(position, radius, GameConfig::EffectSphereRings, GameConfig::EffectSphereSlices, col);
    }
}