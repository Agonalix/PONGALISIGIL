#include "Rectangle.h"



void FirstPlayerMovement(rectangle& firstPlayer)
{
	if (IsKeyDown(KEY_W))
	{
		if (firstPlayer.Position.y >= 10)
		{
			firstPlayer.Position.y -= firstPlayer.speed * GetFrameTime();
		}
	}
	if (IsKeyDown(KEY_S))
	{
		if (firstPlayer.Position.y <= GetScreenHeight() - firstPlayer.Size.y - 10)
		{
			firstPlayer.Position.y += firstPlayer.speed * GetFrameTime();
		}
	}
}