#include "menu.h"

using namespace colors;

void MenuLoop(Scenes& scene, int ScreenHeight, int ScreenWidth)
{
	Vector2 mousePosition = { slGetMouseX(), slGetMouseY()};
	Button singlePlayer;
	Button Rules;

	int fontSizeMENU = 120;
	int fontSizeMODE = 90;
	int fontSizeCredits = 30;
	color currentColorSingle = BLACK;
	color currentColorMulti = BLACK;

	if (slGetKey(SL_KEY_ESCAPE))
	{
		scene = Scenes::Exit;
	}
	InitializeMenu(singlePlayer, Rules);
	ButtonPressed(scene, mousePosition, singlePlayer, Rules);
	ContrastColorWhenColliding(mousePosition, singlePlayer, Rules, currentColorSingle, currentColorMulti);

	MenuDraw(fontSizeMENU, singlePlayer, fontSizeMODE, Rules, fontSizeCredits, ScreenHeight, ScreenWidth, currentColorSingle, currentColorMulti);
}
void MenuDraw(int fontSizeMENU, Button& singlePlayer, int fontSizeMODE, Button& rules,  int fontSizeCredits, int ScreenHeight, int ScreenWidth, color currentColorSingle, color currentColorMulti)
{
	//----------------------------------------------------------------------------------------------
	//Menu

	slSetBackColor(BLACK.r, BLACK.g, BLACK.b);

	// large text and fat line
	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFontSize(fontSizeMENU);
	slText(30, 25, "MENU");
	slRectangleFill(25, 135, 350, 5);

	// smaller subtext
	slSetFontSize(fontSizeMODE);
	slText(singlePlayer.position.x, singlePlayer.position.y, "Single-Player");

	slSetForeColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
	slRectangleFill(singlePlayer.position.x, singlePlayer.position.y, singlePlayer.width, singlePlayer.height);

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFontSize(fontSizeMODE);
	slText(rules.position.x, rules.position.y, "Rules");

	slSetForeColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
	slRectangleFill(singlePlayer.position.x, singlePlayer.position.y, singlePlayer.width, singlePlayer.height);

	//----------------------------------------------------------------------------------------------
	//Creditos
	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFontSize(fontSizeCredits);
	slText(ScreenWidth - slGetTextWidth("Made by: Santiago Seara"), ScreenHeight - fontSizeCredits* 2.0, "Made by: Santiago Seara");

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFontSize(fontSizeCredits);
	slText(ScreenWidth - slGetTextWidth("Institution: Image Campus"), ScreenHeight - fontSizeCredits * 1.5, "Institution: Image Campus");

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
	singlePlayer.width = 625;
	singlePlayer.height = 90;
	singlePlayer.color = BLACK;
	singlePlayer.position = { 35, 200 };

	multiPlayer.width = 550;
	multiPlayer.height = 90;
	multiPlayer.color = BLACK;
	multiPlayer.position = { 35, 325 };
}
void rulesDraw()
{

}