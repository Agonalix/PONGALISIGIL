#pragma once
#include "Vector2.h"
#include "Scenes.h"
#include "Button.h"
#include "colors.h"

void MenuLoop(Scenes& scene, int ScreenHeight, int ScreenWidth);
void MenuDraw(int fontSizeMENU, Button& singlePlayer, int fontSizeMODE, Button& multiPlayer, int fontSizeCredits, int ScreenHeight, int ScreenWidth, color currentColorSingle, color currentColorMulti);
void ContrastColorWhenColliding(Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer, color currentColorSingle, color currentColorMulti);
void InitializeMenu(Button& singlePlayer, Button& multiPlayer);
void ButtonPressed(Scenes& scene, Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer);
bool MouseRecCollision(Vector2& position, Button& button);
void rulesDraw();