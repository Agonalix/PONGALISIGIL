#pragma once
#include "Vector2.h"
#include "Scenes.h"
#include "Button.h"
#include "colors.h"
#include "ScreenSize.h"

void MenuLoop(Scenes& scene,  int font);
void MenuDraw( Button& singlePlayer, Button& multiPlayer,  color currentColorSingle, color currentColorMulti, int font);
void ContrastColorWhenColliding(Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer, color currentColorSingle, color currentColorMulti);
void InitializeMenu(Button& singlePlayer, Button& multiPlayer);
void ButtonPressed(Scenes& scene, Vector2& mousePosition, Button& singlePlayer, Button& multiPlayer);
bool MouseRecCollision(Vector2& position, Button& button);
void rulesDraw();