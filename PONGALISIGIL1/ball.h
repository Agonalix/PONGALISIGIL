#pragma once
#include "Vector2.h";

struct ball
{
	Vector2 Size;
	Vector2 Position;
	Vector2 speed;
};

void ballMovement(ball& Ball);
void borderBallCollision(ball& Ball);