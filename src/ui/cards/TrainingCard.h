#pragma once
#include "raylib.h"
#include "Settings.h"
#include "GameMode.h"

class TrainingCard {
public:
    TrainingCard(Rectangle rect, GameMode mode, const char* title, const char* sub1, const char* sub2);
    virtual ~TrainingCard() = default;

    virtual void Update(Settings& settings);
    virtual void Draw(Font font, const Settings& settings) const;

    bool WasClicked() const { return clicked; }
    GameMode GetMode() const { return mode; }
    void ResetClicked() { clicked = false; }

protected:
    Rectangle rect;
    GameMode mode;
    const char* title;
    const char* sub1;
    const char* sub2;
    bool hovered = false;
    bool clicked = false;

    virtual void DrawIcon(Vector2 center, const Settings& settings) const = 0;

    void DrawBase() const;
    void DrawTitleBlock(Font font) const;
    void DrawHorizontalArrows(Vector2 center) const;
    void DrawVerticalArrows(Vector2 center) const;
};

class StaticCard : public TrainingCard {
public:
    explicit StaticCard(Rectangle rect);
protected:
    void DrawIcon(Vector2 center, const Settings& settings) const override;
};

class MovingCard : public TrainingCard {
public:
    explicit MovingCard(Rectangle rect);
protected:
    void DrawIcon(Vector2 center, const Settings& settings) const override;
};

class BouncingCard : public TrainingCard {
public:
    explicit BouncingCard(Rectangle rect);
protected:
    void DrawIcon(Vector2 center, const Settings& settings) const override;
};

class TimedCard : public TrainingCard {
public:
    explicit TimedCard(Rectangle rect);
    void Update(Settings& settings) override;
    void Draw(Font font, const Settings& settings) const override;
protected:
    void DrawIcon(Vector2 center, const Settings& settings) const override;
private:
    void DrawDifficultyButtons(Font font, const Settings& settings) const;
    bool clickedDifficulty = false;
};

class MultiStaticCard : public TrainingCard {
public:
    explicit MultiStaticCard(Rectangle rect);
protected:
    void DrawIcon(Vector2 center, const Settings& settings) const override;
};