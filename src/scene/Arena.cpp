#include "Arena.h"
#include "RoomConfig.h"

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
    float floorY = -RoomConfig::Dimensions::FloorThickness / 2.0f;
    DrawCube({0.0f, floorY, 0.0f}, RoomConfig::Dimensions::Width, RoomConfig::Dimensions::FloorThickness, RoomConfig::Dimensions::Depth, RoomConfig::Colors::Floor);
}

void Arena::DrawCeiling() const {
    DrawCube({0.0f, RoomConfig::Dimensions::Height, 0.0f}, RoomConfig::Dimensions::Width, RoomConfig::Dimensions::FloorThickness, RoomConfig::Dimensions::Depth, RoomConfig::Colors::Ceiling);
}

void Arena::DrawBackWall() const {
    DrawCube({0.0f, RoomConfig::Dimensions::Height / 2.0f, -RoomConfig::Dimensions::Depth / 2.0f}, RoomConfig::Dimensions::Width, RoomConfig::Dimensions::Height, RoomConfig::Dimensions::WallThickness, RoomConfig::Colors::Wall);
}

void Arena::DrawFrontWall() const {
    DrawCube({0.0f, RoomConfig::Dimensions::Height / 2.0f, RoomConfig::Dimensions::Depth / 2.0f}, RoomConfig::Dimensions::Width, RoomConfig::Dimensions::Height, RoomConfig::Dimensions::WallThickness, RoomConfig::Colors::Wall);
}

void Arena::DrawLeftWall() const {
    DrawCube({-RoomConfig::Dimensions::Width / 2.0f, RoomConfig::Dimensions::Height / 2.0f, 0.0f}, RoomConfig::Dimensions::WallThickness, RoomConfig::Dimensions::Height, RoomConfig::Dimensions::Depth, RoomConfig::Colors::Wall);
}

void Arena::DrawRightWall() const {
    DrawCube({RoomConfig::Dimensions::Width / 2.0f, RoomConfig::Dimensions::Height / 2.0f, 0.0f}, RoomConfig::Dimensions::WallThickness, RoomConfig::Dimensions::Height, RoomConfig::Dimensions::Depth, RoomConfig::Colors::Wall);
}

void Arena::DrawGridLines() const {
    float halfW = RoomConfig::Dimensions::Width / 2.0f;
    float halfD = RoomConfig::Dimensions::Depth / 2.0f;
    int h = (int)RoomConfig::Dimensions::Height;

    DrawGridLinesAlongX(halfW, halfD, h);
    DrawGridLinesAlongY(halfW, halfD, h);
    DrawGridLinesAlongZ(halfW, halfD, h);
}

void Arena::DrawGridLinesAlongX(float halfW, float halfD, int h) const {
    int startX = (int)-halfW;
    int endX = (int)halfW;
    for (int x = startX; x <= endX; x += RoomConfig::Grid::Step) {
        DrawLine3D({(float)x, 0, -halfD}, {(float)x, (float)h, -halfD}, RoomConfig::Colors::Grid);
        DrawLine3D({(float)x, 0, halfD}, {(float)x, (float)h, halfD}, RoomConfig::Colors::Grid);
    }
}

void Arena::DrawGridLinesAlongY(float halfW, float halfD, int h) const {
    for (int y = 0; y <= h; y += RoomConfig::Grid::Step) {
        DrawLine3D({-halfW, (float)y, -halfD}, {halfW, (float)y, -halfD}, RoomConfig::Colors::Grid);
        DrawLine3D({-halfW, (float)y, halfD}, {halfW, (float)y, halfD}, RoomConfig::Colors::Grid);
        DrawLine3D({-halfW, (float)y, -halfD}, {-halfW, (float)y, halfD}, RoomConfig::Colors::Grid);
        DrawLine3D({halfW, (float)y, -halfD}, {halfW, (float)y, halfD}, RoomConfig::Colors::Grid);
    }
}

void Arena::DrawGridLinesAlongZ(float halfW, float halfD, int h) const {
    int startZ = (int)-halfD;
    int endZ = (int)halfD;
    for (int z = startZ; z <= endZ; z += RoomConfig::Grid::Step) {
        DrawLine3D({-halfW, 0, (float)z}, {-halfW, (float)h, (float)z}, RoomConfig::Colors::Grid);
        DrawLine3D({halfW, 0, (float)z}, {halfW, (float)h, (float)z}, RoomConfig::Colors::Grid);
    }
}

void Arena::DrawNeonLines() const {
    float halfW = RoomConfig::Dimensions::Width / 2.0f;
    float halfD = RoomConfig::Dimensions::Depth / 2.0f;
    float y = RoomConfig::Grid::NeonHeightOffset;

    DrawLine3D({-halfW, y, -halfD}, {halfW, y, -halfD}, RoomConfig::Colors::Neon);
    DrawLine3D({-halfW, y, halfD}, {halfW, y, halfD}, RoomConfig::Colors::Neon);
    DrawLine3D({-halfW, y, -halfD}, {-halfW, y, halfD}, RoomConfig::Colors::Neon);
    DrawLine3D({halfW, y, -halfD}, {halfW, y, halfD}, RoomConfig::Colors::Neon);
}