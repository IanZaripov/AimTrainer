#include "Hands.h"
#include "HandsConfig.h"
#include "raylib.h"

void Hands::Draw() const {
    // Ладонь
    DrawCube(HandsConfig::HandPos, HandsConfig::HandSize.x, HandsConfig::HandSize.y, HandsConfig::HandSize.z, HandsConfig::SkinColor);
    // Палец
    DrawCube(HandsConfig::ThumbPos, HandsConfig::ThumbSize.x, HandsConfig::ThumbSize.y, HandsConfig::ThumbSize.z, HandsConfig::SkinColor);
    // Рукав
    DrawCube(HandsConfig::SleevePos, HandsConfig::SleeveSize.x, HandsConfig::SleeveSize.y, HandsConfig::SleeveSize.z, HandsConfig::SleeveColor);
}