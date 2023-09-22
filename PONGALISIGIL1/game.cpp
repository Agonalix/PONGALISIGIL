#include "ball.h"
#include "rectangle.h"
#include "game.h"
#include "menu.h"
#include "scenes.h"


//-----------------------------------------------------------------------------------------------------------------------
//Start Game
void GameLoop();
void GameOver(rectangle& firstPlayer, rectangle& secondPlayer, ball& Ball);
void singlePlayerMode(rectangle& firstPlayer, rectangle& IAPlayer, ball& Ball);
void ReturnToStartingPosition(rectangle& firstPlayer, rectangle& secondPlayer, ball& Ball);
void GameDraw(rectangle& firstPlayer, rectangle& secondPlayer, ball& Ball);
bool isWinner(rectangle& firstPlayer, rectangle& secondPlayer);
void InitializeGameSingle(rectangle& firstPlayer, rectangle& secondPlayer, ball& ball); // inicializacion de las variables
void reset(rectangle& firstPlayer, rectangle& secondPlayer, rectangle& IAPlayer, ball& ball);
bool isScoring(rectangle& firstPlayer, rectangle& secondPlayer, ball Ball);


//-----------------------------------------------------------------------------------------------------------------------
//Game Mechanics
bool Collision(rectangle Player, ball Ball);
void BallPlayerCollision(const rectangle& firstPlayer, ball& Ball, const rectangle& secondPlayer);
void RandomBallStart(ball& Ball);


static Scenes scene = Scenes::Menu;
int ScreenWidth = 900;
int ScreenHeight = 500;

void RunProgram()
{
	//Sizes
	slWindow(ScreenWidth, ScreenHeight, "LOCO", 20);
	SetExitKey(KEY_NULL);
	GameLoop(singlePlayer);
}

void GameLoop()
{
	// Initialization
	//--------------------------------------------------------------------------------------


	rectangle firstPlayer;
	rectangle secondPlayer;
	rectangle IAPlayer;
	ball Ball;

	//Inicio random de la pelota
	RandomBallStart(Ball);
	InitializeGameSingle(firstPlayer, secondPlayer, Ball);
	InitializeGameMulti(firstPlayer, IAPlayer, Ball);


	while (scene != Scenes::Exit && !WindowShouldClose())    // Detect window close button or ESC key
	{
		switch (scene)
		{
		case Scenes::Menu:
			reset(firstPlayer, secondPlayer, IAPlayer, Ball);
			MenuLoop(scene);
			break;

		case Scenes::SinglePlayerGame:
			singlePlayerMode(firstPlayer, IAPlayer, Ball);
			break;

		case Scenes::Rules:
			MultiPlayerMode(firstPlayer, secondPlayer, Ball);
			break;

		case Scenes::GameOver:
			GameOver(firstPlayer, secondPlayer, Ball);
			GameOver(firstPlayer, IAPlayer, Ball);
			break;

		case Scenes::Exit:
			break;
		}
	}
}

void singlePlayerMode(rectangle& firstPlayer, rectangle& IAPlayer, ball& Ball)
{
	// Update
	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------
	if (IsKeyPressed(KEY_BACKSPACE))
	{
		scene = Scenes::Menu;
		return;
	}

	if (isWinner(firstPlayer, IAPlayer) != true)
	{
		// Pelota
		//----------------------------------------------------------------------------------
		BallMovement(Ball);

		//First player
		//----------------------------------------------------------------------------------
		FirstPlayerMovement(firstPlayer);


		//IA player
		//----------------------------------------------------------------------------------
		IAPlayerMovement(IAPlayer, Ball);

		//Colisiones
		//----------------------------------------------------------------------------------

		BorderBallCollision(Ball);
		BallPlayerCollision(firstPlayer, Ball, IAPlayer);

		ReturnToStartingPosition(firstPlayer, IAPlayer, Ball);

		GameDraw(firstPlayer, IAPlayer, Ball);
	}
	else
	{
		scene = Scenes::GameOver;
	}
}
void reset(rectangle& firstPlayer, rectangle& secondPlayer, rectangle& IAPlayer, ball& ball)
{
	//--------------------------------------------------------------------------------------
	//FirstPlayer
	firstPlayer.Position = { 20, 395 };
	firstPlayer.Size = { 25, 185 };
	firstPlayer.speed = 720;
	firstPlayer.score = 0;

	//--------------------------------------------------------------------------------------
	//SecondPlayer
	secondPlayer.Position = { 1875, 395 };
	secondPlayer.Size = { 25, 185 };
	secondPlayer.speed = 720;
	secondPlayer.score = 0;

	//--------------------------------------------------------------------------------------
	//IA
	IAPlayer.Position = { 1875, 395 };
	IAPlayer.Size = { 25, 185 };
	IAPlayer.speed = 425;
	IAPlayer.score = 0;

	//--------------------------------------------------------------------------------------
	//ball
	ball.Position = { ScreenWidth / 2, ScreenHeight / 2 };
	ball.Size = { 25, 25 };
	ball.speed.x = 575;
	ball.speed.y = 525;
}
void InitializeGameSingle(rectangle& firstPlayer, rectangle& secondPlayer, ball& ball)
{
	//--------------------------------------------------------------------------------------
	//FirstPlayer
	firstPlayer.Position = { 20, 395 };
	firstPlayer.Size = { 25, 185 };
	firstPlayer.speed = 720;
	firstPlayer.score = 0;

	//--------------------------------------------------------------------------------------
	//SecondPlayer
	secondPlayer.Position = { 1875, 395 };
	secondPlayer.Size = { 25, 185 };
	secondPlayer.speed = 720;
	secondPlayer.score = 0;

	//--------------------------------------------------------------------------------------
	//ball
	ball.Position = { ScreenWidth / 2, ScreenHeight / 2 };
	ball.Size = { 25, 25 };
	ball.speed.x = 525;
	ball.speed.y = 525;

	if (GetRandomValue(0, 1) == 0)
	{
		ball.Position.x -= ball.speed.x * GetFrameTime();
		ball.Position.y -= ball.speed.y * GetFrameTime();
	}
	else
	{
		ball.Position.x += ball.speed.x * GetFrameTime();
		ball.Position.y += ball.speed.y * GetFrameTime();
	}

}

void GameDraw(rectangle& firstPlayer, rectangle& secondPlayer, ball& Ball)
{
	// Draw
	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(BLACK);

	DrawText("PONG", 850, 465, 80, DARKGRAY);
	DrawText(TextFormat("%01i", firstPlayer.score), 200, 80, 100, WHITE);
	DrawText(TextFormat("%01i", secondPlayer.score), ScreenWidth - 280, 80, 100, WHITE);

	//Players
	//----------------------------------------------------------------------------------
	DrawRectangleV(firstPlayer.Position, firstPlayer.Size, WHITE); // Player one Drawing
	DrawRectangleV(secondPlayer.Position, secondPlayer.Size, WHITE); // Player two Drawing

	//Ball
	//----------------------------------------------------------------------------------
	DrawRectangleV(Ball.Position, Ball.Size, WHITE); //Ball Drawing

	EndDrawing();
	//----------------------------------------------------------------------------------
}
void RandomBallStart(ball& Ball)
{
	//Random number to start the ball
	//------------------------------------------------------------------------------------------
	if (GetRandomValue(0, 1) == 0)
	{
		if (GetRandomValue(0, 1) == 0)
		{
			Ball.speed.x *= -1;
			Ball.speed.y = -1;
		}
		else
		{
			Ball.speed.x = Ball.speed.x;
			Ball.speed.y = Ball.speed.y;
		}
	}
	else
	{
		if (GetRandomValue(0, 1) == 0)
		{
			Ball.speed.x *= -1;
			Ball.speed.y *= -1;
		}
		else
		{
			Ball.speed.x = Ball.speed.x;
			Ball.speed.y = Ball.speed.y;
		}
	}
}
bool isWinner(rectangle& firstPlayer, rectangle& secondPlayer)
{
	if (firstPlayer.score == 10 || secondPlayer.score == 10)
	{
		return true;
	}
	return false;
}
void GameOver(rectangle& firstPlayer, rectangle& secondPlayer, ball& Ball)
{

	int fontSize = 100;
	int fontSizeContinue = 30;
	if (IsKeyPressed(KEY_SPACE))
	{
		RandomBallStart(Ball);
		InitializeGameSingle(firstPlayer, secondPlayer, Ball);
		scene = Scenes::Menu;
	}

	BeginDrawing();
	ClearBackground(BLACK);
	if (firstPlayer.score == 10)
	{
		DrawText("PLAYER ONE WINS", ScreenWidth / 2 - MeasureText("PLAYER ONE WINS", fontSize) / 2, ScreenHeight / 2 - fontSize, fontSize, WHITE);
		DrawText("Press SPACE to continue...", ScreenWidth - MeasureText("Press SPACE to continue...", fontSizeContinue), ScreenHeight - 55, fontSizeContinue, WHITE);
	}
	else if (secondPlayer.score == 10)
	{
		DrawText("PLAYER TWO WINS", ScreenWidth / 2 - MeasureText("PLAYER TWO WINS", fontSize) / 2, ScreenHeight / 2 - fontSize, fontSize, WHITE);
		DrawText("Press SPACE to continue...", ScreenWidth - MeasureText("Press SPACE to continue...", fontSizeContinue), ScreenHeight - 55, fontSizeContinue, WHITE);
	}
	EndDrawing();
}

void ReturnToStartingPosition(rectangle& firstPlayer, rectangle& secondPlayer, ball& Ball)
{
	if (isScoring(firstPlayer, secondPlayer, Ball)) // Si suma un punto alguno de los jugadores, la pelota vuelve al (0;0)
	{
		Ball.Position.x = ScreenWidth / 2.0f;
		Ball.Position.y = ScreenHeight / 2.0f;
		RandomBallStart(Ball);
	}
	//----------------------------------------------------------------------------------
}
bool Collision(rectangle Player, ball Ball)
{
	if (Player.Position.x + Player.Size.x >= Ball.Position.x &&
		Player.Position.x <= Ball.Position.x + Ball.Size.x &&
		Player.Position.y + Player.Size.y >= Ball.Position.y &&
		Player.Position.y <= Ball.Position.y + Ball.Size.y) {

		return true;
	}

	return false;
}
void BallPlayerCollision(const rectangle& firstPlayer, ball& Ball, const rectangle& secondPlayer)
{
	if (Collision(firstPlayer, Ball))
	{
		if (Ball.Position.y > firstPlayer.Position.y + (firstPlayer.Size.y / 3) && Ball.Position.y < firstPlayer.Position.y + (firstPlayer.Size.y * (2.0f / 3.0f)))
		{
			Ball.Position.x = firstPlayer.Position.x + Ball.Size.x;
			Ball.speed.x *= -1;
			Ball.speed.y = 0;
		}
		else if (Ball.Position.y < firstPlayer.Position.y + firstPlayer.Size.y / 3)
		{
			Ball.Position.x = firstPlayer.Position.x + Ball.Size.x;
			Ball.speed.x *= -1;
			Ball.speed.y = -525;

		}
		else if (Ball.Position.y > firstPlayer.Position.y + firstPlayer.Size.y * (2.0f / 3.0f))
		{
			Ball.Position.x = firstPlayer.Position.x + Ball.Size.x;
			Ball.speed.x *= -1;
			Ball.speed.y = 525;
		}

	}
	if (Collision(secondPlayer, Ball))
	{
		if (Ball.Position.y <= secondPlayer.Position.y + secondPlayer.Size.y / 3)
		{
			Ball.Position.x = secondPlayer.Position.x - Ball.Size.x;
			Ball.speed.x *= -1;
			Ball.speed.y = -525;

		}
		else if (Ball.Position.y >= secondPlayer.Position.y + secondPlayer.Size.y / 3 && Ball.Position.y <= secondPlayer.Position.y + secondPlayer.Size.y * (2.0f / 3.0f))
		{
			Ball.Position.x = secondPlayer.Position.x - Ball.Size.x;
			Ball.speed.x *= -1;
			Ball.speed.y = 0;
		}
		else if (Ball.Position.y >= secondPlayer.Position.y + secondPlayer.Size.y * (2.0f / 3.0f))
		{
			Ball.Position.x = secondPlayer.Position.x - Ball.Size.x;
			Ball.speed.x *= -1;
			Ball.speed.y = 525;
		}

	}
}
bool isScoring(rectangle& firstPlayer, rectangle& secondPlayer, ball Ball)
{
	if (Ball.Position.x >= ScreenWidth)
	{
		firstPlayer.score++;
		return true;
	}
	if (Ball.Position.x <= 0)
	{
		secondPlayer.score++;
		return true;
	}

	return false;
}