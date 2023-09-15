#pragma once

struct ball
{
	int sizeX;
	int sizeY;
	int positionX;
	int positionY;
	int speedX;
	int speedY;
};

void BallMovement(ball& Ball);
void BorderBallCollision(ball& Ball);