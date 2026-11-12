#pragma once

class Hands {
public:
    void Draw() const;

private:
    void DrawPalm() const;
    void DrawFingers() const;
    void DrawThumb() const;
    void DrawSleeve() const;
};