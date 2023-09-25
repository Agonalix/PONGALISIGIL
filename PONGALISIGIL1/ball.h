#pragma once
#include "Vector2.h";

struct ball
{
	Vector2 Size;
	Vector2 Position;
	Vector2 speed;
};

void BallMovement(ball& Ball);
void BorderBallCollision(ball& Ball, int ScreenHeight, int ScreenWidth);