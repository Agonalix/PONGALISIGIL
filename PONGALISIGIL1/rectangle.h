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
void FirstPlayerMovement(rectangle& firstPlayer);