#pragma once
#include "Vector2.h";

struct ball
{
	Vector2 size;
	Vector2 position;
	Vector2 speed;
};

void BallMovement(ball& Ball);
void BorderBallCollision(ball& Ball);