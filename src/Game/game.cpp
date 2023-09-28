#include "Objects/ball.h"
#include "Objects/rectangle.h"
#include "Game/game.h"
#include "Game/menu.h"
#include "Game/scenes.h"
#include <iostream>
#include <string>

using namespace colors;
using namespace std;

//-----------------------------------------------------------------------------------------------------------------------
//Start Game
void gameLoop();
void gameOver(rectangle& firstPlayer, ball& Ball, int font);
void singlePlayerMode(rectangle& firstPlayer, ball& Ball, int font);
void returnToStartingPosition(rectangle& firstPlayer, ball& Ball);
void gameDraw(rectangle& firstPlayer, ball& Ball, int font);
void ballDrawing(ball& Ball);
void paddleDrawing(rectangle& firstPlayer);
bool isWinner(rectangle& firstPlayer);
void initializeGameSingle(rectangle& firstPlayer, ball& ball); // inicializacion de las variables
void reset(rectangle& firstPlayer, ball& ball);
bool lostLives(rectangle& firstPlayer, ball Ball);
void brickInit(rectangle& brick, int startX, int col, const int& brickWidth, const int& brickSpacing, int row, const int& brickHeight);
void brickDraw(ball& Ball, rectangle& firstPlayer);
void bricksStarted();


//-----------------------------------------------------------------------------------------------------------------------
//Game Mechanics
bool collision(rectangle Player, ball Ball);
void ballPlayerCollision(const rectangle& firstPlayer, ball& Ball);
void randomBallStart(ball& Ball);


static Scenes scene = Scenes::Menu;

void runProgram()
{
	//Sizes
	gameLoop();
}

void gameLoop()
{
	// Initialization
	//--------------------------------------------------------------------------------------


	rectangle firstPlayer;
	ball Ball;


	slWindow(screenWidth, screenHeight, "Breakout", true);
	int font = slLoadFont("../Assets/HuLi-Regular.ttf");
	int fontRules = slLoadFont("../Assets/Mouly.ttf");
	int fontArrows = slLoadFont("../Assets/Citylist.ttf");
	//Inicio random de la pelota
	randomBallStart(Ball);
	initializeGameSingle(firstPlayer, Ball);
	bricksStarted();


	while (scene != Scenes::Exit && !slShouldClose() && !slGetKey(SL_KEY_ESCAPE))    // Detect window close button or ESC key
	{
		switch (scene)
		{
		case Scenes::Menu:
			bricksStarted();
			reset(firstPlayer, Ball);
			menuLoop(scene, font);
			break;

		case Scenes::SinglePlayerGame:
			singlePlayerMode(firstPlayer, Ball, font);
			break;

		case Scenes::Rules:
			rulesDraw(fontRules, fontArrows, scene);
			break;

		case Scenes::Pause:
			pauseDraw(fontRules, fontArrows, scene);
			break;

		case Scenes::GameOver:
			gameOver(firstPlayer, Ball, font);
			break;

		case Scenes::Exit:
			break;
		}
		slRender();
	}
	slClose();
}

void singlePlayerMode(rectangle& firstPlayer, ball& Ball, int font)
{
	// Update
	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------

	if (slGetKey(SL_KEY_ENTER))
	{
		scene = Scenes::Pause;
		return;
	}

	if (isWinner(firstPlayer) != true)
	{
		// Pelota
		//----------------------------------------------------------------------------------
		ballMovement(Ball);

		//First player
		//----------------------------------------------------------------------------------
		firstPlayerMovement(firstPlayer);

		//Colisiones
		//----------------------------------------------------------------------------------

		borderBallCollision(Ball);
		ballPlayerCollision(firstPlayer, Ball);

		returnToStartingPosition(firstPlayer, Ball);

		gameDraw(firstPlayer, Ball, font);

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
	firstPlayer.Position = { screenWidth / 2 + firstPlayer.Size.x / 2, screenHeight - 15 };
	firstPlayer.Size = { 185, 25 };
	firstPlayer.speed = 720;
	firstPlayer.bricksBroken = 0;
	firstPlayer.lives = 5;

	//--------------------------------------------------------------------------------------
	//ball
	ball.Position = { screenWidth / 2, screenHeight / 2 };
	ball.Size = { 25, 25 };
	ball.speed.x = 475;
	ball.speed.y = 450;
}

void initializeGameSingle(rectangle& firstPlayer, ball& ball)
{
	srand(time(NULL));
	//--------------------------------------------------------------------------------------
	//FirstPlayer
	firstPlayer.Position = { screenWidth / 2 + firstPlayer.Size.x / 2, screenHeight - 30 };
	firstPlayer.Size = { 185, 25 };
	firstPlayer.speed = 720;
	firstPlayer.bricksBroken = 0;

	//--------------------------------------------------------------------------------------
	//ball
	ball.Position = { screenWidth / 2, screenHeight / 2 };
	ball.Size = { 25, 25 };
	ball.speed.x = 475;
	ball.speed.y = 450;

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

void gameDraw(rectangle& firstPlayer, ball& Ball, int font)
{
	// Draw
	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------
	slSetBackColor(BLACK.r, BLACK.g, BLACK.b);

	//Players
	//----------------------------------------------------------------------------------
	paddleDrawing(firstPlayer);

	//Ball
	//----------------------------------------------------------------------------------
	ballDrawing(Ball);

	slSetFont(font, 30);
	slText(30, slGetTextHeight("Lives: "), "Lives: ");
	slText(30 + slGetTextWidth("Lives: "), slGetTextHeight("Lives: "), to_string(firstPlayer.lives).c_str());
}

void ballDrawing(ball& Ball)
{
	slRectangleFill(Ball.Position.x, Ball.Position.y, Ball.Size.x, Ball.Size.y);
}

void paddleDrawing(rectangle& firstPlayer)
{
	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slRectangleFill(firstPlayer.Position.x, firstPlayer.Position.y, firstPlayer.Size.x, firstPlayer.Size.y); // Player one Drawing
}

void randomBallStart(ball& Ball)
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



void returnToStartingPosition(rectangle& firstPlayer, ball& Ball)
{
	if (lostLives(firstPlayer, Ball)) // Si suma un punto alguno de los jugadores, la pelota vuelve al (0;0)
	{
		Ball.Position.x = screenWidth / 2.0f;
		Ball.Position.y = screenHeight / 2.0f;
		randomBallStart(Ball);
	}
	//----------------------------------------------------------------------------------
}

bool collision(rectangle Player, ball Ball)
{
	if (Player.Position.x + Player.Size.x / 2 >= Ball.Position.x - Ball.Size.x / 2 &&
		Player.Position.x - Player.Size.x / 2 <= Ball.Position.x + Ball.Size.x / 2 &&
		Player.Position.y + Player.Size.y / 2 >= Ball.Position.y - Ball.Size.x / 2 &&
		Player.Position.y - Player.Size.y / 2 <= Ball.Position.y + Ball.Size.y / 2) {

		return true;
	}

	return false;
}

void ballPlayerCollision(const rectangle& firstPlayer, ball& Ball)
{
	if (collision(firstPlayer, Ball))
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
	if (Ball.Position.y >= screenHeight)
	{
		firstPlayer.lives--;
		return true;
	}

	return false;
}



const int numRows = 5;       // Cantidad de filas de ladrillos
const int numCols = 12;      // Cantidad de columnas de ladrillos
bool bricks[numRows][numCols];

void gameOver(rectangle& firstPlayer, ball& Ball, int font)
{

	int fontSize = 100;
	int fontSizeContinue = 30;

	slSetBackColor(BLACK.r, BLACK.g, BLACK.b);
	if (firstPlayer.bricksBroken == numRows * numCols)
	{
		slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
		slSetFont(font, fontSize);
		slText(screenWidth / 2 - slGetTextWidth("YOU WIN") / 2, screenHeight / 2, "YOU WIN");
		slSetFont(font, fontSizeContinue);
		slText(screenWidth - slGetTextWidth("Press BACKSPACE to continue..."), screenHeight - 55, "Press BACKSPACE to continue...");
	}
	else if (firstPlayer.lives == 0)
	{
		slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
		slSetFont(font, fontSize);
		slText(screenWidth / 2 - slGetTextWidth("GAME OVER") / 2, screenHeight / 2, "GAME OVER");
		slSetFont(font, fontSizeContinue);
		slText(screenWidth - slGetTextWidth("Press BACKSPACE to continue...") - 20, 55, "Press BACKSPACE to continue...");
	}
	if (slGetKey(SL_KEY_BACKSPACE))
	{
		randomBallStart(Ball);
		initializeGameSingle(firstPlayer, Ball);
		scene = Scenes::Menu;
	}
}

bool isWinner(rectangle& firstPlayer)
{
	if (firstPlayer.bricksBroken == numRows * numCols)
	{
		return true;
	}
	else if (firstPlayer.lives == 0)
	{
		return true;
	}
	return false;
}
void brickDraw(ball& Ball, rectangle& firstPlayer)
{
	const int brickWidth = 130;
	const int brickHeight = 35;
	const int brickSpacing = 15;  // Espacio entre ladrillos
	rectangle brick;

	color rowColors[] = { RED, GREEN, BLUE, YELLOW, ORANGE }; // Colores para cada fila de ladrillos

	int totalWidth = numCols * (brickWidth + brickSpacing);
	int startX = (screenWidth - totalWidth + brickWidth) / 2; // arregle el bug del espacio en negro agregandole el ancho de un brick



	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			brickInit(brick, startX, col, brickWidth, brickSpacing, row, brickHeight);

			if (bricks[row][col]) // Solo verifica y dibuja ladrillos que no están rotos
			{
				if (collision(brick, Ball))
				{
					Ball.speed.y *= -1;
					bricks[row][col] = false; // Marcar el ladrillo como roto
					firstPlayer.bricksBroken++;
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

void bricksStarted()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			bricks[row][col] = true;
		}
	}
}