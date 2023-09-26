#include "menu.h"

using namespace colors;

void MenuLoop(Scenes& scene, int font)
{
	Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };
	Button singlePlayer;
	Button Rules;

	color currentColorSingle = BLACK;
	color currentColorMulti = BLACK;

	if (slGetKey(SL_KEY_ESCAPE))
	{
		scene = Scenes::Exit;
	}
	InitializeMenu(singlePlayer, Rules);
	ButtonPressed(scene, mousePosition, singlePlayer, Rules);
	ContrastColorWhenColliding(mousePosition, singlePlayer, Rules, currentColorSingle, currentColorMulti);

	MenuDraw(singlePlayer, Rules, currentColorSingle, currentColorMulti, font);
}
void MenuDraw(Button& singlePlayer, Button& rules, color currentColorSingle, color currentColorMulti, int font)
{

	//----------------------------------------------------------------------------------------------
	//Menu
	int fontSizeMENU = 150;
	int fontSizeMODE = 90;
	int fontSizeCredits = 30;
	slSetBackColor(BLACK.r, BLACK.g, BLACK.b);

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);

	slSetFont(font, fontSizeMENU);
	slText(30, ScreenHeight - 130, "MENU");
	//slRectangleFill(25, 135, 350, 5);

	slSetForeColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
	//slRectangleFill(singlePlayer.position.x, singlePlayer.position.y, singlePlayer.width, singlePlayer.height);

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFont(font, fontSizeMODE);
	slText(singlePlayer.position.x, singlePlayer.position.y, "Single-Player");

	slSetForeColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
	//slRectangleFill(rules.position.x, rules.position.y, rules.width, rules.height);

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFont(font, fontSizeMODE);
	slText(rules.position.x, rules.position.y, "Rules");


	//----------------------------------------------------------------------------------------------
	//Creditos
	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFont(font, fontSizeCredits);
	slText(ScreenWidth - slGetTextWidth("Made by: Santiago Seara"), ScreenHeight - fontSizeCredits * 3.0, "Made by: Santiago Seara");

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFont(font, fontSizeCredits);
	slText(ScreenWidth - slGetTextWidth("Institution: Image Campus"), ScreenHeight - fontSizeCredits, "Institution: Image Campus");

}
void ContrastColorWhenColliding(Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer, color currentColorSingle, color currentColorMulti)
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
	if (MouseRecCollision(mousePosition, singlePlayer) == true && slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
	{
		scene = Scenes::SinglePlayerGame;
	}
	else if (MouseRecCollision(mousePosition, multiPlayer) == true && slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
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
	singlePlayer.width = 100;
	singlePlayer.height = 80;
	singlePlayer.color = BLACK;
	singlePlayer.position = { 35, ScreenHeight - 400 };

	multiPlayer.width = 550;
	multiPlayer.height = 90;
	multiPlayer.color = BLACK;
	multiPlayer.position = { 35, ScreenHeight - 550 };
}
void rulesDraw()
{



}