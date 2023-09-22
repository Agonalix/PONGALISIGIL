#include "menu.h"

using namespace colors;

void MenuLoop(Scenes& scene)
{
	Vector2 mousePosition = { slGetMouseX(), slGetMouseY()};
	Button singlePlayer;
	Button Rules;

	int fontSizeMENU = 120;
	int fontSizeMODE = 90;
	int fontSizeCredits = 30;
	color currentColorSingle;
	color currentColorMulti;

	if (slGetKey(SL_KEY_ESCAPE))
	{
		scene = Scenes::Exit;
	}
	InitializeMenu(singlePlayer, Rules);
	ButtonPressed(scene, mousePosition, singlePlayer, Rules);
	ContrastColorWhenColliding(mousePosition, singlePlayer, currentColorSingle, Rules, currentColorMulti);

	MenuDraw(fontSizeMENU, singlePlayer, fontSizeMODE, currentColorSingle, Rules, currentColorMulti, fontSizeCredits);
}
void MenuDraw(int fontSizeMENU, Button& singlePlayer, int fontSizeMODE, const color& currentColorSingle, Button& rules, const color& currentColorMulti, int fontSizeCredits)
{
	BeginDrawing();
	slSetBackColor(0, 0, 0);
	//----------------------------------------------------------------------------------------------
	//Menu
	DrawRectangle(25, 135, 350, 5, WHITE); //Subrayado
	DrawText("MENU", 30, 25, fontSizeMENU, WHITE);


	DrawRectangle(singlePlayer.position.x, singlePlayer.position.y, singlePlayer.width, singlePlayer.height, singlePlayer.color); //Click option
	DrawText("Single-Player", singlePlayer.position.x, singlePlayer.position.y, fontSizeMODE, currentColorSingle);



	DrawRectangle(rules.position.x, rules.position.y, rules.width, rules.height, rules.color); //Click option
	DrawText("Rules", rules.position.x, rules.position.y, fontSizeMODE, currentColorMulti);


	//----------------------------------------------------------------------------------------------
	//Creditos
	DrawText("Made by: Santiago Seara", GetScreenWidth() - slGetTextWidth("Made by: Santiago Seara"), GetScreenHeight() - fontSizeCredits * 2.5, fontSizeCredits, WHITE);
	DrawText("Institution: Image Campus", GetScreenWidth() - slGetTextWidth("Institution: Image Campus"), GetScreenHeight() - fontSizeCredits * 1.5, fontSizeCredits, WHITE);

	EndDrawing();
}
void ContrastColorWhenColliding(Vector2& mousePosition, Button& singlePlayer, color& currentColorSingle, Button& multiPlayer, color& currentColorMulti)
{
	if (MouseRecCollision(mousePosition, singlePlayer) == true)
	{
		currentColorSingle = GRAY;
	}
	else
	{
		currentColorSingle = WHITE;
	}
	if (MouseRecCollision(mousePosition, multiPlayer) == true)
	{
		currentColorMulti = GRAY;
	}
	else
	{
		currentColorMulti = WHITE;
	}
}
void ButtonPressed(Scenes& scene, Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer)
{
	if (MouseRecCollision(mousePosition, singlePlayer) == true && IsMouseButtonPressed(0))
	{
		scene = Scenes::SinglePlayerGame;
	}
	else if (MouseRecCollision(mousePosition, multiPlayer) == true && IsMouseButtonPressed(0))
	{
		scene = Scenes::Rules;
	}
}
bool MouseRecCollision(Vector2& position, Button& button)
{
	// Collision check for point to rectangle
	if (position.x >= button.position.x &&
		position.x <= button.position.x + button.width &&
		position.y >= button.position.y &&
		position.y <= button.position.y + button.height) {

		return true;
	}

	return false;
}
void InitializeMenu(Button& singlePlayer, Button& multiPlayer)
{
	singlePlayer.width = 625;
	singlePlayer.height = 90;
	singlePlayer.color = BLACK;
	singlePlayer.position = { 35, 200 };

	multiPlayer.width = 550;
	multiPlayer.height = 90;
	multiPlayer.color = BLACK;
	multiPlayer.position = { 35, 325 };
}