#pragma once
#ifndef __GAME_MENUANIMITEM_S_H__
#define __GAME_MENUANIMITEM_S_H__

#include "GameMenuAnimItem.h"
#include "GameMenuItemS.h"
#include "iSelectable.h"

class GameMenuAnimItemS : public GameMenuAnimItem, public GameMenuItemS
{
public:
	GameMenuAnimItemS(SpriteMap* s, int x, int y, Game* game, GameState* gstate);
	~GameMenuAnimItemS();
};

#endif