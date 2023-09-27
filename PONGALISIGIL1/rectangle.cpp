#include "Rectangle.h"
#include "ScreenSize.h"

void firstPlayerMovement(rectangle& firstPlayer)
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
		if (firstPlayer.Position.x <= screenWidth - firstPlayer.Size.x /2 - 10)
		{
			firstPlayer.Position.x += firstPlayer.speed * slGetDeltaTime();
		}
	}
}