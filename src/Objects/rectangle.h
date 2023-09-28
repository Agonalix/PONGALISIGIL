#pragma once
#include "Game/Vector2.h";
#include "Objects/ball.h"
#include "include/sl.h"

struct rectangle
{
    Vector2 Position;
    Vector2 Size;
    int speed;
    int bricksBroken;
    int lives;
};
void firstPlayerMovement(rectangle& firstPlayer);