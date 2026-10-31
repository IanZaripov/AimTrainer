#pragma once

struct Settings {
    // Настройки мыши
    float sensitivity = 2.0f; // Множитель (подбирается индивидуально под DPI)
    
    // Настройки арены и мишеней
    float fovDegrees  = 103.0f; // Горизонтальный FOV как в Valorant
    float headRadius  = 22.0f;  // Радиус головы бота
    int   panelWidth  = 280;    // Ширина панели UI
};