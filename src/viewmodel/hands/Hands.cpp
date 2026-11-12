#include "Hands.h"
#include "HandsConfig.h"
#include "raylib.h"

void Hands::Draw() const {
    DrawPalm();
    DrawThumb();
    DrawSleeve();
}

void Hands::DrawPalm() const {
    DrawCube(HandsConfig::Palm::Pos, 
             HandsConfig::Palm::Size.x, 
             HandsConfig::Palm::Size.y, 
             HandsConfig::Palm::Size.z, 
             HandsConfig::Palm::Color);
}

void Hands::DrawThumb() const {
    DrawCube(HandsConfig::Thumb::Pos, 
             HandsConfig::Thumb::Size.x, 
             HandsConfig::Thumb::Size.y, 
             HandsConfig::Thumb::Size.z, 
             HandsConfig::Thumb::Color);
}

void Hands::DrawSleeve() const {
    DrawCube(HandsConfig::Sleeve::Pos, 
             HandsConfig::Sleeve::Size.x, 
             HandsConfig::Sleeve::Size.y, 
             HandsConfig::Sleeve::Size.z, 
             HandsConfig::Sleeve::Color);
}