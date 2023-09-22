#pragma once
#include "Vector2.h"
#include "ball.h"

struct rectangle
{
    Vector2 Position;
    Vector2 Size;
    int speed;
    int score;
};
void SecondPlayerMovement(rectangle& secondPlayer, rectangle& firstPlayer);
void FirstPlayerMovement(rectangle& firstPlayer);
void IAPlayerMovement(rectangle& IAPlayer, ball& Ball);