#include "Rectangle.h"


void FirstPlayerMovement(rectangle& firstPlayer, int ScreenHeight)
{
	if (slGetKey(SL_KEY_RIGHT))
	{
		if (firstPlayer.Position.x >= 10)
		{
			firstPlayer.Position.x -= firstPlayer.speed * slGetDeltaTime();
		}
	}
	if (slGetKey(SL_KEY_LEFT))
	{
		if (firstPlayer.Position.x <= ScreenHeight - firstPlayer.Size.x - 10)
		{
			firstPlayer.Position.x += firstPlayer.speed * slGetDeltaTime();
		}
	}
}