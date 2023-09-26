#include "ball.h"
#include "Vector2.h"
#include "include/sl.h"
#include "ScreenSize.h"

void BallMovement(ball& Ball)
{
	Ball.Position.y += Ball.speed.y * slGetDeltaTime();
	Ball.Position.x += Ball.speed.x * slGetDeltaTime();
}
void BorderBallCollision(ball& Ball)
{
	if (Ball.Position.y >= (ScreenHeight - Ball.Size.y))
	{
		Ball.Position.y = ScreenHeight - Ball.Size.y;
		Ball.speed.y *= -1;
	}
	else if (Ball.Position.x <= 0)
	{
		Ball.Position.x = 0;
		Ball.speed.x *= -1;
	}
	else if (Ball.Position.x >= ScreenWidth)
	{
		Ball.Position.x = ScreenWidth;
		Ball.speed.x *= -1;
	}
}
