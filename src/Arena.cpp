#include "Arena.h"

Arena::Arena(const RoomConfig& cfg) : config(cfg) {}

void Arena::Draw() const {
    DrawFloor();
    DrawCeiling();
    DrawBackWall();
    DrawFrontWall();
    DrawLeftWall();
    DrawRightWall();
    DrawGridLines();
    DrawNeonLines();
}

void Arena::DrawFloor() const {
    float floorY = -config.floorThickness / 2.0f;
    DrawCube({0.0f, floorY, 0.0f}, config.width, config.floorThickness, config.depth, config.floorColor);
}

void Arena::DrawCeiling() const {
    DrawCube({0.0f, config.height, 0.0f}, config.width, config.floorThickness, config.depth, config.ceilingColor);
}

void Arena::DrawBackWall() const {
    DrawCube({0.0f, config.height / 2.0f, -config.depth / 2.0f}, config.width, config.height, config.wallThickness, config.wallColor);
}

void Arena::DrawFrontWall() const {
    DrawCube({0.0f, config.height / 2.0f, config.depth / 2.0f}, config.width, config.height, config.wallThickness, config.wallColor);
}

void Arena::DrawLeftWall() const {
    DrawCube({-config.width / 2.0f, config.height / 2.0f, 0.0f}, config.wallThickness, config.height, config.depth, config.wallColor);
}

void Arena::DrawRightWall() const {
    DrawCube({config.width / 2.0f, config.height / 2.0f, 0.0f}, config.wallThickness, config.height, config.depth, config.wallColor);
}

void Arena::DrawGridLines() const {
    float halfW = config.width / 2.0f;
    float halfD = config.depth / 2.0f;
    int h = (int)config.height;

    DrawGridLinesAlongX(halfW, halfD, h);
    DrawGridLinesAlongY(halfW, halfD, h);
    DrawGridLinesAlongZ(halfW, halfD, h);
}

void Arena::DrawGridLinesAlongX(float halfW, float halfD, int h) const {
    int startX = (int)-halfW;
    int endX = (int)halfW;
    for (int x = startX; x <= endX; x += config.gridStep) {
        DrawLine3D({(float)x, 0, -halfD}, {(float)x, (float)h, -halfD}, config.gridColor);
        DrawLine3D({(float)x, 0, halfD}, {(float)x, (float)h, halfD}, config.gridColor);
    }
}

void Arena::DrawGridLinesAlongY(float halfW, float halfD, int h) const {
    for (int y = 0; y <= h; y += config.gridStep) {
        DrawLine3D({-halfW, (float)y, -halfD}, {halfW, (float)y, -halfD}, config.gridColor);
        DrawLine3D({-halfW, (float)y, halfD}, {halfW, (float)y, halfD}, config.gridColor);
        DrawLine3D({-halfW, (float)y, -halfD}, {-halfW, (float)y, halfD}, config.gridColor);
        DrawLine3D({halfW, (float)y, -halfD}, {halfW, (float)y, halfD}, config.gridColor);
    }
}

void Arena::DrawGridLinesAlongZ(float halfW, float halfD, int h) const {
    int startZ = (int)-halfD;
    int endZ = (int)halfD;
    for (int z = startZ; z <= endZ; z += config.gridStep) {
        DrawLine3D({-halfW, 0, (float)z}, {-halfW, (float)h, (float)z}, config.gridColor);
        DrawLine3D({halfW, 0, (float)z}, {halfW, (float)h, (float)z}, config.gridColor);
    }
}

void Arena::DrawNeonLines() const {
    float halfW = config.width / 2.0f;
    float halfD = config.depth / 2.0f;
    float y = config.neonHeightOffset;

    DrawLine3D({-halfW, y, -halfD}, {halfW, y, -halfD}, config.neonColor);
    DrawLine3D({-halfW, y, halfD}, {halfW, y, halfD}, config.neonColor);
    DrawLine3D({-halfW, y, -halfD}, {-halfW, y, halfD}, config.neonColor);
    DrawLine3D({halfW, y, -halfD}, {halfW, y, halfD}, config.neonColor);
}