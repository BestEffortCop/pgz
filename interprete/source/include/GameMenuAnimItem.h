#pragma once
#ifndef __GAME_MENUANIMITEM_H__
#define __GAME_MENUANIMITEM_H__

#include "GameMenuItem.h"
#include "SpriteMap.h"


class GameMenuAnimItem : private GameMenuItem
{
public:
	GameMenuAnimItem(SpriteMap* s, int x, int y, Game* game, GameState* gstate);
	~GameMenuAnimItem();

	void setPos(int x, int y);
	void setAnim(SpriteMap* s);
};

#endif