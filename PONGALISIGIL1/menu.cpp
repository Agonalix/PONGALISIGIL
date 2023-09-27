#include "menu.h"

using namespace colors;

void menuLoop(Scenes& scene, int font)
{
	Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };
	Button singlePlayer;
	Button rules;
	Button exit;

	color currentColorExit = WHITE;
	color currentColorSingle = WHITE;
	color currentColorMulti = WHITE;

	if (slGetKey(SL_KEY_ESCAPE))
	{
		scene = Scenes::Exit;
	}
	initializeMenu(singlePlayer, rules, exit);
	buttonPressed(scene, mousePosition, singlePlayer, rules, exit);
	contrastColorWhenColliding(mousePosition, singlePlayer, rules, currentColorSingle, currentColorMulti, exit, currentColorExit);

	menuDraw(singlePlayer, rules, currentColorSingle, currentColorMulti, font, exit, currentColorExit);
}
void menuDraw(Button& singlePlayer, Button& rules, color& currentColorSingle, color& currentColorRules, int font, Button& exit, color& currentColorExit)
{

	//----------------------------------------------------------------------------------------------
	//Menu
	int fontSizeMENU = 150;
	int fontSizeMODE = 90;
	int fontSizeCredits = 30;
	slSetBackColor(BLACK.r, BLACK.g, BLACK.b);

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);

	slSetFont(font, fontSizeMENU);
	slText(30, screenHeight - 130, "UpSide-Out");

	slSetForeColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
	slRectangleFill(singlePlayer.position.x, singlePlayer.position.y, singlePlayer.width, singlePlayer.height);

	slSetForeColor(currentColorSingle.r, currentColorSingle.g, currentColorSingle.b, currentColorSingle.a);
	slSetFont(font, fontSizeMODE);
	slText(singlePlayer.position.x, singlePlayer.position.y, "Single-Player");

	slSetForeColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
	slRectangleFill(rules.position.x, rules.position.y, rules.width, rules.height);

	slSetForeColor(currentColorRules.r, currentColorRules.g, currentColorRules.b, currentColorRules.a);
	slSetFont(font, fontSizeMODE);
	slText(rules.position.x, rules.position.y, "Rules");

	slSetForeColor(currentColorExit.r, currentColorExit.g, currentColorExit.b, currentColorExit.a);
	slSetFont(font, fontSizeMODE);
	slText(exit.position.x, exit.position.y, "Exit");

	slSetFont(font, fontSizeMODE);
	slText(exit.position.x, exit.position.y, "Exit");

	//----------------------------------------------------------------------------------------------
	//Creditos
	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFont(font, fontSizeCredits);
	slText(screenWidth - slGetTextWidth("Made by: Santiago Seara") - 10, 0 + fontSizeCredits * 3.0, "Made by Santiago Seara");

	slSetForeColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	slSetFont(font, fontSizeCredits);
	slText(screenWidth - slGetTextWidth("Institution: Image Campus") - 10, 0 + fontSizeCredits, "Institution Image Campus");

}
void contrastColorWhenColliding(Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer, color& currentColorSingle, color& currentColorRules, Button& exit, color& currentColorExit)
{
	if (mouseRecCollision(mousePosition, singlePlayer) == true)
	{
		currentColorSingle = GRAY;
	}
	else
	{
		currentColorSingle = WHITE;
	}

	if (mouseRecCollision(mousePosition, multiPlayer) == true)
	{
		currentColorRules = GRAY;
	}
	else
	{
		currentColorRules = WHITE;
	}

	if (mouseRecCollision(mousePosition, exit) == true)
	{
		currentColorExit = GRAY;
	}
	else
	{
		currentColorExit = WHITE;
	}
}
void buttonPressed(Scenes& scene, Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer, Button& exit)
{
	if (mouseRecCollision(mousePosition, singlePlayer) == true && slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
	{
		scene = Scenes::SinglePlayerGame;
	}
	else if (mouseRecCollision(mousePosition, multiPlayer) == true && slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
	{
		scene = Scenes::Rules;
	}
	else if (mouseRecCollision(mousePosition, exit) == true && slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
	{
		scene = Scenes::Exit;
	}
}
bool mouseRecCollision(Vector2& position, Button& button)
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
void initializeMenu(Button& singlePlayer, Button& multiPlayer, Button& exit)
{
	singlePlayer.width = 575;
	singlePlayer.height = 80;
	singlePlayer.color = BLACK;
	singlePlayer.position = { 35, screenHeight - 400 };

	multiPlayer.width = 225;
	multiPlayer.height = 90;
	multiPlayer.color = BLACK;
	multiPlayer.position = { 35, screenHeight - 550 };

	exit.width = 225;
	exit.height = 90;
	exit.color = BLACK;
	exit.position = { 35, screenHeight - 700 };
}