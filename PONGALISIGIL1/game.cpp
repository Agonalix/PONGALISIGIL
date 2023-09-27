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
void GameOver(rectangle& firstPlayer, ball& Ball, int font);
void singlePlayerMode(rectangle& firstPlayer, ball& Ball);
void ReturnToStartingPosition(rectangle& firstPlayer, ball& Ball);
void GameDraw(rectangle& firstPlayer, ball& Ball);
bool isWinner(rectangle& firstPlayer);
void InitializeGameSingle(rectangle& firstPlayer, ball& ball); // inicializacion de las variables
void reset(rectangle& firstPlayer, ball& ball);
bool lostLives(rectangle& firstPlayer, ball Ball);
void brickInit(rectangle& brick, int startX, int col, const int& brickWidth, const int& brickSpacing, int row, const int& brickHeight);
void brickDraw(ball& Ball, rectangle& firstPlayer);
void bricksArray();


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
	int fontRules = slLoadFont("../Mouly.ttf");
	int fontArrows = slLoadFont("../Citylist.ttf");
	//Inicio random de la pelota
	RandomBallStart(Ball);
	InitializeGameSingle(firstPlayer, Ball);

	bricksArray();

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
			rulesDraw(fontRules, fontArrows);
			break;

		case Scenes::GameOver:
			GameOver(firstPlayer, Ball, font);
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

		brickDraw(Ball, firstPlayer);
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
	firstPlayer.Position = { ScreenWidth / 2 + firstPlayer.Size.x / 2, ScreenHeight - 15 };
	firstPlayer.Size = { 185, 25 };
	firstPlayer.speed = 720;
	firstPlayer.bricksBroken = 0;
	firstPlayer.lives = 5;

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
	firstPlayer.Position = { ScreenWidth / 2 + firstPlayer.Size.x / 2, ScreenHeight - 15 };
	firstPlayer.Size = { 185, 25 };
	firstPlayer.speed = 720;
	firstPlayer.bricksBroken = 0;

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

	//Bricks;
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
		Ball.speed.y = Ball.speed.y;
	}
	else if (randomNumber == 2)
	{
		Ball.speed.x = Ball.speed.x;
		Ball.speed.y = Ball.speed.y;
	}
	else if (randomNumber == 3)
	{
		Ball.speed.x = Ball.speed.x;
		Ball.speed.y = -Ball.speed.y;
	}
	else
	{
		Ball.speed.x = -Ball.speed.x;
		Ball.speed.y = -Ball.speed.y;
	}
}


void GameOver(rectangle& firstPlayer, ball& Ball, int font)
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
	if (firstPlayer.bricksBroken == 10)
	{
		slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
		slSetFont(font, fontSize);
		slText(ScreenWidth / 2 - slGetTextWidth("PLAYER ONE WINS") / 2, ScreenHeight / 2 - fontSize, "PLAYER ONE WINS");
		slSetFont(font, fontSizeContinue);
		slText(ScreenWidth - slGetTextWidth("Press SPACE to continue..."), ScreenHeight - 55, "Press SPACE to continue...");
	}
}

void ReturnToStartingPosition(rectangle& firstPlayer, ball& Ball)
{
	if (lostLives(firstPlayer, Ball)) // Si suma un punto alguno de los jugadores, la pelota vuelve al (0;0)
	{
		Ball.Position.x = ScreenWidth / 2.0f;
		Ball.Position.y = ScreenHeight / 2.0f;
		RandomBallStart(Ball);
	}
	//----------------------------------------------------------------------------------
}

bool Collision(rectangle Player, ball Ball)
{
	if (Player.Position.x + Player.Size.x / 2 >= Ball.Position.x - Ball.Size.x / 2 &&
		Player.Position.x - Player.Size.x / 2 <= Ball.Position.x + Ball.Size.x / 2 &&
		Player.Position.y + Player.Size.y / 2 >= Ball.Position.y - Ball.Size.x / 2 &&
		Player.Position.y - Player.Size.y / 2 <= Ball.Position.y + Ball.Size.y / 2) {

		return true;
	}

	return false;
}

void BallPlayerCollision(const rectangle& firstPlayer, ball& Ball)
{
	if (Collision(firstPlayer, Ball))
	{
		if (Ball.Position.x > firstPlayer.Position.x - firstPlayer.Size.x * (1.0f / 6.0f) &&
			Ball.Position.x < firstPlayer.Position.x + firstPlayer.Size.x * (1.0f / 6.0f))
		{
			Ball.Position.y = firstPlayer.Position.y - Ball.Size.y;
			Ball.speed.y = -Ball.speed.y;
			Ball.speed.x = 0;
		}
		else if (Ball.Position.x < firstPlayer.Position.x - firstPlayer.Size.x * (1.0f / 6.0f))
		{
			Ball.Position.y = firstPlayer.Position.y - Ball.Size.x;
			Ball.speed.y = -Ball.speed.y;
			Ball.speed.x = -525;
		}
		else if (Ball.Position.x > firstPlayer.Position.x + firstPlayer.Size.x * (1.0f / 6.0f))
		{
			Ball.Position.y = firstPlayer.Position.y - Ball.Size.x;
			Ball.speed.y = -Ball.speed.y;
			Ball.speed.x = 525;
		}
	}
}

bool lostLives(rectangle& firstPlayer, ball Ball)
{
	if (Ball.Position.y >= ScreenHeight)
	{
		firstPlayer.lives--;
		return true;
	}

	return false;
}

void rulesDraw(int font, int fontSpecial)
{
	if (slGetKey(SL_KEY_BACKSPACE))
	{
		scene = Scenes::Menu;
		return;
	}
	int fontSizeMENU = 150;
	int fontSizeTEXT = 45;
	int textPositionX = 35;
	int textPositiony = ScreenHeight - 285;

	slSetForeColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFont(font, fontSizeMENU);
	slText(30, ScreenHeight - 130, "Rules");

	slSetFont(font, fontSizeTEXT);
	slText(textPositionX, textPositiony, "This is a breakout game, the rules are the same.");
	slText(textPositionX, textPositiony - 55, "You are the paddle and must destroy all the rectangles. But mine has a twist... literally.");


	slSetFont(font, fontSizeMENU - 30);
	slText(30, textPositiony - 200, "Movement: ");
	slSetFont(fontSpecial, fontSizeMENU - 50);
	slText(textPositionX + 30, textPositiony - 345, "<        >");

	slSetFont(font, fontSizeMENU - 30);
	slText(30, textPositiony - 470, "Exit Buttons: ");

	slSetFont(font, fontSizeMENU - 75);
	slText(textPositionX, textPositiony - 625, "ESC: EXIT PROGRAM");
	slText(textPositionX, textPositiony - 725, "BACKSPACE: MENU");
}


const int numRows = 5;       // Cantidad de filas de ladrillos
const int numCols = 12;      // Cantidad de columnas de ladrillos
bool bricks[numRows][numCols];

bool isWinner(rectangle& firstPlayer)
{
	if (firstPlayer.bricksBroken == numRows * numCols)
	{
		return true;
	}
	return false;
}
void brickDraw(ball& Ball, rectangle& firstPlayer)
{
	const int brickWidth = 120;
	const int brickHeight = 35;
	const int brickSpacing = 30;  // Espacio entre ladrillos
	rectangle brick;

	color rowColors[] = { RED, GREEN, BLUE, YELLOW, ORANGE }; // Colores para cada fila de ladrillos

	int totalWidth = numCols * (brickWidth + brickSpacing);
	int startX = (ScreenWidth - totalWidth + brickWidth) / 2; // arregle el bug del espacio en negro agregandole el ancho de un brick

	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			brickInit(brick, startX, col, brickWidth, brickSpacing, row, brickHeight);

			if (bricks[row][col]) // Solo verifica y dibuja ladrillos que no están rotos
			{
				if (Collision(brick, Ball))
				{
					Ball.speed.y *= -1;
					bricks[row][col] = false; // Marcar el ladrillo como roto
					firstPlayer.bricksBroken++;
					break;
				}

				slSetForeColor(rowColors[row].r, rowColors[row].g, rowColors[row].b, rowColors[row].a);
				slRectangleFill(brick.Position.x, brick.Position.y, brick.Size.x, brick.Size.y);
			}
		}
	}
}

void brickInit(rectangle& brick, int startX, int col, const int& brickWidth, const int& brickSpacing, int row, const int& brickHeight)
{
	brick.Position.x = startX + col * (brickWidth + brickSpacing);
	brick.Position.y = 100 + row * (brickHeight + brickSpacing);
	brick.Size.x = brickWidth;
	brick.Size.y = brickHeight;
}

void bricksArray()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			bricks[row][col] = true;
		}
	}
}