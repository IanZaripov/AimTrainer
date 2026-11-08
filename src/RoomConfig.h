#pragma once
#include "raylib.h"

struct RoomConfig {
    // Размеры комнаты
    float width = 40.0f;
    float depth = 100.0f;
    float height = 12.0f;

    // Толщина стен и пола
    float wallThickness = 1.0f;
    float floorThickness = 1.0f;

    // Параметры сетки и неона
    int gridStep = 4;
    float neonHeightOffset = 0.05f;

    // Цветовая палитра
    Color floorColor   = { 80, 95, 115, 255 };
    Color wallColor    = { 60, 75, 95, 255 };
    Color ceilingColor = { 90, 105, 125, 255 };
    Color gridColor    = { 100, 115, 135, 255 };
    Color neonColor    = { 255, 70, 85, 255 };
};