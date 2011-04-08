#include "GameMenuStampItem.h"


GameMenuStampItem::GameMenuStampItem(Stamp* s, int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate)
{
	graphic = s;
}


GameMenuStampItem::~GameMenuStampItem()
{
}


void GameMenuStampItem::setPos(int x, int y)
{
	GameMenuItem::setPos(x, y);
}

void GameMenuStampItem::setStamp(Stamp* s)
{
	GameMenuItem::setGraphic(s);
}