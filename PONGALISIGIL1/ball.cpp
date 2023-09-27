#include "ball.h"
#include "Vector2.h"
#include "include/sl.h"
#include "ScreenSize.h"

void ballMovement(ball& Ball)
{
	Ball.Position.y += Ball.speed.y * slGetDeltaTime();
	Ball.Position.x += Ball.speed.x * slGetDeltaTime();
}
void borderBallCollision(ball& Ball)
{
	if (Ball.Position.y <= 0)
	{
		Ball.Position.y = Ball.Size.y;
		Ball.speed.y *= -1;
	}
	else if (Ball.Position.x <= 0)
	{
		Ball.Position.x = 0;
		Ball.speed.x *= -1;
	}
	else if (Ball.Position.x >= screenWidth)
	{
		Ball.Position.x = screenWidth;
		Ball.speed.x *= -1;
	}
}
