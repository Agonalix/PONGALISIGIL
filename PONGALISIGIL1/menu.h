#pragma once
#include "Vector2.h"
#include "Scenes.h"
#include "Button.h"
#include "colors.h"
#include "ScreenSize.h"

void menuLoop(Scenes& scene,  int font);
void menuDraw( Button& singlePlayer, Button& multiPlayer,  color currentColorSingle, color currentColorMulti, int font);
void contrastColorWhenColliding(Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer, color currentColorSingle, color currentColorMulti);
void initializeMenu(Button& singlePlayer, Button& multiPlayer);
void buttonPressed(Scenes& scene, Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer);
bool mouseRecCollision(Vector2& position, Button& button);
void rulesDraw(int font, int fontSpecial);
