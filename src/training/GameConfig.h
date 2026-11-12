#pragma once

namespace GameConfig {
    namespace Limits {
        constexpr float SessionTime = 60.0f;
        constexpr float Pitch = 89.0f;
    }
    
    namespace Mouse {
        constexpr float SensMultiplier = 0.022f;
    }

    namespace Effect {
        constexpr float Lifetime = 0.2f;
        constexpr float MaxScale = 2.0f;
        constexpr int SphereRings = 8;
        constexpr int SphereSlices = 8;
    }

    namespace Spawn {
        constexpr int XMin = -600;
        constexpr int XMax = 600;
        constexpr int YMin = 150;
        constexpr int YMax = 400;
        constexpr float Scale = 100.0f;
    }

    namespace TimedMode {
        constexpr float LifeEasy = 1.5f;
        constexpr float LifeMedium = 1.0f;
        constexpr float LifeHard = 0.6f;
    }

    namespace MultiStaticMode {
        constexpr int BallCount = 8;
    }
}