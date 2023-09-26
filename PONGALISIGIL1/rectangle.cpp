#include "Rectangle.h"
#include "ScreenSize.h"

void FirstPlayerMovement(rectangle& firstPlayer)
{
	if (slGetKey(SL_KEY_LEFT))
	{
		if (firstPlayer.Position.x >= firstPlayer.Size.x / 2 + 10)
		{
			firstPlayer.Position.x -= firstPlayer.speed * slGetDeltaTime();
		}
	}
	if (slGetKey(SL_KEY_RIGHT))
	{
		if (firstPlayer.Position.x <= ScreenWidth - firstPlayer.Size.x /2 - 10)
		{
			firstPlayer.Position.x += firstPlayer.speed * slGetDeltaTime();
		}
	}
}