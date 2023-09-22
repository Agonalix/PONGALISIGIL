#include "ball.h"

void BallMovement(ball& Ball)
{
	Ball.Position.y += Ball.speed.y * GetFrameTime();
	Ball.Position.x += Ball.speed.x * GetFrameTime();
}
void BorderBallCollision(ball& Ball)
{
	if ((Ball.Position.y >= (GetScreenHeight() - Ball.Size.y)))
	{
		Ball.Position.y = GetScreenHeight() - Ball.Size.y;
		Ball.speed.y *= -1;
	}
	else if ((Ball.Position.y <= 0))
	{
		Ball.Position.y = 0;
		Ball.speed.y *= -1;
	}
}
