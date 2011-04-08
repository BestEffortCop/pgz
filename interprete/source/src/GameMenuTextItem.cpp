#include "GameMenuTextItem.h"


GameMenuTextItem::GameMenuTextItem(TextLabel* text, int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate)
{
	graphic = text;
}


GameMenuTextItem::~GameMenuTextItem()
{
}

void GameMenuTextItem::setPos(int x, int y)
{
	GameMenuItem::setPos(x, y);
}

void GameMenuTextItem::setText(TextLabel* s)
{
	GameMenuItem::setGraphic(s);
}