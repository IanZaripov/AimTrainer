#pragma once
#include "raylib.h"
#include "Settings.h"
#include "GameConfig.h"

class Target3D {
public:
    Vector3 position;
    bool    active = true;
    
    // Movement data (used by training modes)
    float   speed = 0.0f;
    int     direction = 1;
    Vector2 velocity = { 0.0f, 0.0f };
    float   lifeTimer = 0.0f;

    Target3D();
    
    // Triggers the explosion effect and starts the death animation
    void Hit();
    
    // Updates the explosion animation timer
    void Update(float dt);
    
    // Draws the sphere and the explosion effect
    void Draw(const Settings& settings) const;

    bool IsExploding() const { return isExploding; }

private:
    bool  isExploding = false;
    float explosionLife = 0.0f; 
};