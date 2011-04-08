#pragma once
#ifndef __GAME_MENUSTAMPITEM_H__
#define __GAME_MENUSTAMPITEM_H__


#include "GameMenuItem.h"
#include "Stamp.h"

class GameMenuStampItem : private GameMenuItem
{
public:
	GameMenuStampItem(Stamp* s, int x, int y, Game* game, GameState* gstate);
	~GameMenuStampItem();

	void setPos(int x, int y);
	void setStamp(Stamp* s);
};


#endif