#pragma once

namespace GameConfig {
    constexpr float SessionTimeLimit = 60.0f; 
    constexpr float PitchLimit = 89.0f;       
    constexpr float SensMultiplier = 0.022f;  
    constexpr float EffectLifetime = 0.2f;    
    constexpr float EffectMaxScale = 2.0f;    
    constexpr int EffectSphereRings = 8;
    constexpr int EffectSphereSlices = 8;

    // Параметры спавна шаров
    constexpr int SpawnXMin = -600;
    constexpr int SpawnXMax = 600;
    constexpr int SpawnYMin = 150;
    constexpr int SpawnYMax = 400;
    constexpr float SpawnScale = 100.0f;

    // Время жизни шаров в режиме на время
    constexpr float TimedLifeEasy = 1.5f;
    constexpr float TimedLifeMedium = 1.0f;
    constexpr float TimedLifeHard = 0.6f;

    // Количество шаров в режиме Мульти-цель
    constexpr int MultiStaticBallCount = 8; 
}