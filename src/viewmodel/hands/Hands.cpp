#include "Hands.h"
#include "HandsConfig.h"

void Hands::Draw() const {
    DrawPalm();
    DrawThumb();
    DrawSleeve();
}

void Hands::DrawPalm() const {
    DrawCube(HandsConfig::HandPos, 
             HandsConfig::HandSize.x, 
             HandsConfig::HandSize.y, 
             HandsConfig::HandSize.z, 
             HandsConfig::SkinColor);
}

void Hands::DrawThumb() const {
    DrawCube(HandsConfig::ThumbPos, 
             HandsConfig::ThumbSize.x, 
             HandsConfig::ThumbSize.y, 
             HandsConfig::ThumbSize.z, 
             HandsConfig::SkinColor);
}

void Hands::DrawSleeve() const {
    DrawCube(HandsConfig::SleevePos, 
             HandsConfig::SleeveSize.x, 
             HandsConfig::SleeveSize.y, 
             HandsConfig::SleeveSize.z, 
             HandsConfig::SleeveColor);
}