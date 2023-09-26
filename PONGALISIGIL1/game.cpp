#include "ball.h"
#include "rectangle.h"
#include "game.h"
#include "menu.h"
#include "scenes.h"
#include <iostream>

using namespace colors;

//-----------------------------------------------------------------------------------------------------------------------
//Start Game
void GameLoop();
void GameOver(rectangle& firstPlayer, ball& Ball);
void singlePlayerMode(rectangle& firstPlayer, ball& Ball);
void ReturnToStartingPosition(rectangle& firstPlayer, ball& Ball);
void GameDraw(rectangle& firstPlayer, ball& Ball);
bool isWinner(rectangle& firstPlayer);
void InitializeGameSingle(rectangle& firstPlayer, ball& ball); // inicializacion de las variables
void reset(rectangle& firstPlayer, ball& ball);
bool isScoring(rectangle& firstPlayer, ball Ball);


//-----------------------------------------------------------------------------------------------------------------------
//Game Mechanics
bool Collision(rectangle Player, ball Ball);
void BallPlayerCollision(const rectangle& firstPlayer, ball& Ball);
void RandomBallStart(ball& Ball);


static Scenes scene = Scenes::Menu;

void RunProgram()
{
	//Sizes
	GameLoop();
}

void GameLoop()
{
	// Initialization
	//--------------------------------------------------------------------------------------


	rectangle firstPlayer;
	ball Ball;

	slWindow(ScreenWidth, ScreenHeight, "Breakout", true);
	int font = slLoadFont("../HuLi-Regular.ttf");
	//Inicio random de la pelota
	/*RandomBallStart(Ball);
	InitializeGameSingle(firstPlayer, Ball);*/
	scene = Scenes::Menu;

	while (scene != Scenes::Exit && !slShouldClose() && !slGetKey(SL_KEY_ESCAPE))    // Detect window close button or ESC key
	{
		switch (scene)
		{
		case Scenes::Menu:
			reset(firstPlayer, Ball);
			MenuLoop(scene, font);
			break;

		case Scenes::SinglePlayerGame:
			singlePlayerMode(firstPlayer, Ball);
			break;

		case Scenes::Rules:
			rulesDraw();
			break;

		case Scenes::GameOver:
			GameOver(firstPlayer, Ball);
			GameOver(firstPlayer,Ball);
			break;

		case Scenes::Exit:
			break;
		}
		slRender();
	}
	slClose();
}

void singlePlayerMode(rectangle& firstPlayer, ball& Ball)
{
	// Update
	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------
	if (slGetKey(SL_KEY_BACKSPACE))
	{
		scene = Scenes::Menu;
		return;
	}

	if (isWinner(firstPlayer) != true)
	{
		// Pelota
		//----------------------------------------------------------------------------------
		BallMovement(Ball);

		//First player
		//----------------------------------------------------------------------------------
		FirstPlayerMovement(firstPlayer);

		//Colisiones
		//----------------------------------------------------------------------------------

		BorderBallCollision(Ball);
		BallPlayerCollision(firstPlayer, Ball);

		ReturnToStartingPosition(firstPlayer, Ball);

		GameDraw(firstPlayer, Ball);
	}
	else
	{
		scene = Scenes::GameOver;
	}
}

void reset(rectangle& firstPlayer, ball& ball)
{
	//--------------------------------------------------------------------------------------
	//FirstPlayer
	firstPlayer.Position = { ScreenWidth / 2 + firstPlayer.Size.x / 2, 15 };
	firstPlayer.Size = { 185, 25 };
	firstPlayer.speed = 720;
	firstPlayer.score = 0;

	//--------------------------------------------------------------------------------------
	//ball
	ball.Position = { ScreenWidth / 2, ScreenHeight / 2 };
	ball.Size = { 25, 25 };
	ball.speed.x = 575;
	ball.speed.y = 525;
}

void InitializeGameSingle(rectangle& firstPlayer, ball& ball)
{
	srand(time(NULL));
	//--------------------------------------------------------------------------------------
	//FirstPlayer
	firstPlayer.Position = { ScreenWidth /2 + firstPlayer.Size.x /2, 15 };
	firstPlayer.Size = { 185, 25 };
	firstPlayer.speed = 720;
	firstPlayer.score = 0;

	//--------------------------------------------------------------------------------------
	//ball
	ball.Position = { ScreenWidth / 2, ScreenHeight / 2 };
	ball.Size = { 25, 25 };
	ball.speed.x = 525;
	ball.speed.y = 525;

	if (rand() % 1 == 0)
	{
		ball.Position.x -= ball.speed.x * slGetDeltaTime();
		ball.Position.y -= ball.speed.y * slGetDeltaTime();
	}
	else
	{
		ball.Position.x += ball.speed.x * slGetDeltaTime();
		ball.Position.y += ball.speed.y * slGetDeltaTime();
	}

}

void GameDraw(rectangle& firstPlayer, ball& Ball)
{
	// Draw
	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------
	slSetBackColor(BLACK.r, BLACK.g, BLACK.b);

	//Players
	//----------------------------------------------------------------------------------
	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slRectangleFill(firstPlayer.Position.x, firstPlayer.Position.y, firstPlayer.Size.x, firstPlayer.Size.y); // Player one Drawing

	//Ball
	//----------------------------------------------------------------------------------
	slRectangleFill(Ball.Position.x, Ball.Position.y, Ball.Size.x, Ball.Size.y); // Player one Drawing
	//----------------------------------------------------------------------------------
}

void RandomBallStart(ball& Ball)
{
	srand(time(NULL));

	int randomNumber = rand() % 4 + 1;

	//Random number to start the ball
	//------------------------------------------------------------------------------------------
	if (randomNumber == 1)
	{
		Ball.speed.x = -Ball.speed.x;
		Ball.speed.y = -Ball.speed.y;
	}
	else if (randomNumber == 2)
	{
		Ball.speed.x = Ball.speed.x;
		Ball.speed.y = Ball.speed.y;
	}
	else if (randomNumber == 3)
	{
		Ball.speed.x = -Ball.speed.x;
		Ball.speed.y = -Ball.speed.y;
	}
	else
	{
		Ball.speed.x = Ball.speed.x;
		Ball.speed.y = Ball.speed.y;
	}
}

bool isWinner(rectangle& firstPlayer)
{
	if (firstPlayer.score == 10)
	{
		return true;
	}
	return false;
}

void GameOver(rectangle& firstPlayer, ball& Ball)
{

	int fontSize = 100;
	int fontSizeContinue = 30;
	if (slGetKey(SL_KEY_ESCAPE))
	{
		RandomBallStart(Ball);
		InitializeGameSingle(firstPlayer, Ball);
		scene = Scenes::Menu;
	}

	slSetBackColor(BLACK.r, BLACK.g, BLACK.b);
	if (firstPlayer.score == 10)
	{
		slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
		slSetFontSize(fontSize);
		slText(ScreenWidth / 2 - slGetTextWidth("PLAYER ONE WINS") / 2, ScreenHeight / 2 - fontSize, "PLAYER ONE WINS");
		slSetFontSize(fontSizeContinue);
		slText(ScreenWidth - slGetTextWidth("Press SPACE to continue..."), ScreenHeight - 55, "Press SPACE to continue...");
	}
}

void ReturnToStartingPosition(rectangle& firstPlayer, ball& Ball)
{
	if (isScoring(firstPlayer, Ball)) // Si suma un punto alguno de los jugadores, la pelota vuelve al (0;0)
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

void BallPlayerCollision(const rectangle& firstPlayer, ball& Ball)
{
	if (Collision(firstPlayer, Ball))
	{
		if (Ball.Position.x > firstPlayer.Position.x + (firstPlayer.Size.x / 3) && Ball.Position.x < firstPlayer.Position.x + (firstPlayer.Size.x * (2.0f / 3.0f)))
		{
			Ball.Position.y = firstPlayer.Position.y + Ball.Size.y;
			Ball.speed.y *= -1;
			Ball.speed.x = 0;
		}
		else if (Ball.Position.x < firstPlayer.Position.x + firstPlayer.Size.x / 3)
		{
			Ball.Position.y = firstPlayer.Position.y + Ball.Size.y;
			Ball.speed.y *= -1;
			Ball.speed.x = -525;

		}
		else if (Ball.Position.x > firstPlayer.Position.x + firstPlayer.Size.x * (2.0f / 3.0f))
		{
			Ball.Position.y = firstPlayer.Position.y + Ball.Size.y;
			Ball.speed.y *= -1;
			Ball.speed.x = 525;
		}

	}
}

bool isScoring(rectangle& firstPlayer, ball Ball)
{


	return false;
}