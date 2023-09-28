#pragma once
#include "Game/Vector2.h";
#include "Game/Scenes.h"
#include "Objects/button.h"
#include "Game/colors.h"
#include "Game/ScreenSize.h"

void menuLoop(Scenes& scene,  int font);
void menuDraw( Button& singlePlayer, Button& multiPlayer,  color& currentColorSingle, color& currentColorRules, int font, Button& exit, color& currentColorExit);
void contrastColorWhenColliding(Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer, color& currentColorSingle, color& currentColorMulti, Button& exit, color& currentColorExit);
void initializeMenu(Button& singlePlayer, Button& multiPlayer, Button& exit);
void buttonPressed(Scenes& scene, Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer, Button& exit);
bool mouseRecCollision(Vector2& position, Button& button);
void rulesDraw(int font, int fontSpecial, Scenes& scene);
void pauseDraw(int font, int fontSpecial, Scenes& scene);