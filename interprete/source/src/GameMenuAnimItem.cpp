#include "GameMenuAnimItem.h"


GameMenuAnimItem::GameMenuAnimItem(SpriteMap* s, int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate)
{
	graphic = s;
}


GameMenuAnimItem::~GameMenuAnimItem(void)
{
}


void GameMenuAnimItem::setPos(int x, int y)
{
	GameMenuItem::setPos(x, y);
}

void GameMenuAnimItem::setAnim(SpriteMap* s)
{
	GameMenuItem::setGraphic(s);
}