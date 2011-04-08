#include "GameMenuItem.h"


GameMenuItem::GameMenuItem(int x, int y, Game* game, GameState* gstate) : Entity(x, y, game, gstate)
{
}


GameMenuItem::~GameMenuItem()
{
}

void GameMenuItem::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void GameMenuItem::setGraphic(Graphic* g)
{
	if (graphic != NULL)
		delete this->graphic;
	graphic = g;
}
