#pragma once
#include "raylib.h"
#include "RoomConfig.h"

class Arena {
public:
    Arena(const RoomConfig& config = RoomConfig{});
    void Draw() const;

private:
    RoomConfig config;

    void DrawFloor() const;
    void DrawCeiling() const;
    void DrawBackWall() const;
    void DrawFrontWall() const;
    void DrawLeftWall() const;
    void DrawRightWall() const;
    void DrawGridLines() const;
    void DrawGridLinesAlongX(float halfW, float halfD, int h) const;
    void DrawGridLinesAlongY(float halfW, float halfD, int h) const;
    void DrawGridLinesAlongZ(float halfW, float halfD, int h) const;
    void DrawNeonLines() const;
};