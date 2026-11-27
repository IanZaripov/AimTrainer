#pragma once

enum class GameMode {
    STATIC, 
    MOVING, 
    BOUNCING, 
    TIMED, 
    MULTI_STATIC
};

enum class GameCategory {
    NORMAL,
    COMPETITIVE
};

inline bool IsModeAvailableIn(GameMode mode, GameCategory category) {
    if (category == GameCategory::NORMAL) {
        return mode != GameMode::TIMED;
    }
    return mode != GameMode::STATIC; // COMPETITIVE
}