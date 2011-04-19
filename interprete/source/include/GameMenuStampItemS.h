#pragma once
#ifndef __GAME_MENUSTAMPITEM_S_H__
#define __GAME_MENUSTAMPITEM_S_H__


#include "GameMenuStampItem.h"
#include "GameMenuItemS.h"
#include "iSelectable.h"

class GameMenuStampItemS : public GameMenuStampItem, public GameMenuItemS
{
public:
	GameMenuStampItemS(Stamp* s, int x, int y, Game* game, GameState* gstate);
	~GameMenuStampItemS();
};

#endif
