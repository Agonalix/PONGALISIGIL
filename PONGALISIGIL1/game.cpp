#include "ball.h"
#include "rectangle.h"
#include "game.h"
#include "menu.h"
#include "scenes.h"
#include <iostream>

using namespace colors;

//-----------------------------------------------------------------------------------------------------------------------
//Start Game
void gameLoop();
void gameOver(rectangle& firstPlayer, ball& Ball, int font);
void singlePlayerMode(rectangle& firstPlayer, ball& Ball);
void returnToStartingPosition(rectangle& firstPlayer, ball& Ball);
void gameDraw(rectangle& firstPlayer, ball& Ball);
void ballDrawing(ball& Ball);
void paddleDrawing(rectangle& firstPlayer);
bool isWinner(rectangle& firstPlayer);
void initializeGameSingle(rectangle& firstPlayer, ball& ball); // inicializacion de las variables
void reset(rectangle& firstPlayer, ball& ball);
bool lostLives(rectangle& firstPlayer, ball Ball);
void brickInit(rectangle& brick, int startX, int col, const int& brickWidth, const int& brickSpacing, int row, const int& brickHeight);
void brickDraw(ball& Ball, rectangle& firstPlayer);
void bricksStarted();
void pauseDraw(int font, int fontSpecial);



//-----------------------------------------------------------------------------------------------------------------------
//Game Mechanics
bool collision(rectangle Player, ball Ball);
void ballPlayerCollision(const rectangle& firstPlayer, ball& Ball);
void randomBallStart(ball& Ball);


static Scenes scene = Scenes::Menu;
float timer = 0;

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
	int font = slLoadFont("../HuLi-Regular.ttf");
	int fontRules = slLoadFont("../Mouly.ttf");
	int fontArrows = slLoadFont("../Citylist.ttf");
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
			singlePlayerMode(firstPlayer, Ball);
			break;

		case Scenes::Rules:
			rulesDraw(fontRules, fontArrows);
			break;

		case Scenes::Pause:
			pauseDraw(fontRules, fontArrows);
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

void singlePlayerMode(rectangle& firstPlayer, ball& Ball)
{
	// Update
	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------
	if (slGetKey(SL_KEY_ENTER))
	{
		scene = Scenes::Pause;
		return;
	}

	timer = 0;


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

		gameDraw(firstPlayer, Ball);

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
	ball.speed.x = 575;
	ball.speed.y = 525;
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

void gameDraw(rectangle& firstPlayer, ball& Ball)
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

void rulesDraw(int font, int fontSpecial)
{
	if (slGetKey(SL_KEY_BACKSPACE))
	{
		scene = Scenes::Menu;
		return;
	}
	int fontSizeMENU = 135;
	int fontSizeTEXT = 45;
	int textPositionX = 35;
	int textPositiony = screenHeight - 285;

	slSetForeColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFont(font, fontSizeMENU);
	slText(30, screenHeight - 130, "Rules");

	slSetFont(font, fontSizeTEXT);
	slText(textPositionX, textPositiony + 20, "This is a breakout game, the rules are the same.");
	slText(textPositionX, textPositiony - 35, "You are the paddle and must destroy all the rectangles. But mine has a twist... literally.");

	slSetFont(font, fontSizeMENU - 30);
	slText(30, textPositiony - 200, "Movement: ");
	slSetFont(fontSpecial, fontSizeMENU - 50);
	slText(textPositionX + 30, textPositiony - 300, "<        >");

	slSetFont(font, fontSizeMENU - 30);
	slText(30, textPositiony - 425, "Special Buttons: ");

	slSetFont(font, fontSizeMENU - 75);
	slText(textPositionX, textPositiony - 550, "ESC: EXIT PROGRAM");
	slText(textPositionX, textPositiony - 650, "BACKSPACE: MENU");
	slText(textPositionX, textPositiony - 750, "ENTER: PAUSE");
}

void pauseDraw(int font, int fontSpecial)
{
	timer += slGetDeltaTime();

	if (slGetKey(SL_KEY_BACKSPACE))
	{
		scene = Scenes::Menu;
		return;
	}
	int fontSizeMENU = 150;
	int fontSizeTEXT = 45;
	int textPositionX = screenWidth / 2;
	int textPositiony = screenHeight - 285;

	slSetForeColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFont(font, fontSizeMENU);
	slText(textPositionX - slGetTextWidth("Pause") / 2, screenHeight - 130, "Pause");

	slSetFont(font, fontSizeTEXT);
	slText(textPositionX - slGetTextWidth("Press ENTER to return to game") / 2, textPositiony, "Press ENTER to return to game");
	slText(textPositionX - slGetTextWidth("Press BACKSPACE to return to menu") / 2, textPositiony - 55, "Press BACKSPACE to return to menu");
	slText(textPositionX - slGetTextWidth("Press ESC to exit program") / 2, textPositiony - 110, "Press ESC to exit program");


	slSetFont(font, fontSizeMENU - 30);
	slText(textPositionX - slGetTextWidth("Movement:") / 2, textPositiony - 255, "Movement: ");
	slSetFont(fontSpecial, fontSizeMENU - 50);
	slText(textPositionX - slGetTextWidth("<        >") / 2 + 30, textPositiony - 400, "<        >");


	if (slGetKey(SL_KEY_ENTER) && timer >= 1.0f)
	{
		scene = Scenes::SinglePlayerGame;
		return;
	}
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
	const int brickWidth = 120;
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