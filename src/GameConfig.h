#pragma once

namespace GameConfig {
    constexpr float SessionTimeLimit = 60.0f; 
    constexpr float PitchLimit = 89.0f;       
    constexpr float SensMultiplier = 0.022f;  
    constexpr float EffectLifetime = 0.2f;    
    constexpr float EffectMaxScale = 2.0f;    
    
    // Детализация сферы (Rings, Slices)
    constexpr int EffectSphereRings = 8;
    constexpr int EffectSphereSlices = 8;
}