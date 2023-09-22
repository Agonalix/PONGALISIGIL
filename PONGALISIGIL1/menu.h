#pragma once
#include "Vector2.h"
#include "Scenes.h"
#include "Button.h"
#include "colors.h"

void MenuLoop(Scenes& scene);
void MenuDraw(int fontSizeMENU, Button& singlePlayer, int fontSizeMODE, const color& currentColorSingle, Button& multiPlayer, const color& currentColorMulti, int fontSizeCredits);
void ContrastColorWhenColliding(Vector2& mousePosition, Button& singlePlayer, color& currentColorSingle, Button& multiPlayer, color& currentColorMulti);
void InitializeMenu(Button& singlePlayer, Button& multiPlayer);
void ButtonPressed(Scenes& scene, Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer);
bool MouseRecCollision(Vector2& position, Button& button);
