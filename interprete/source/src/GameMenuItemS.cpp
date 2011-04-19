#include "GameMenuItemS.h"


GameMenuItemS::GameMenuItemS(int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate)
{
	cursorPlaceX = Entity::x - 8;
	cursorPlaceY = Entity::y + 16;
}


GameMenuItemS::~GameMenuItemS()
{
}

void GameMenuItemS::setGraphic(Graphic* g)
{
	GameMenuItem::setGraphic(g);
}