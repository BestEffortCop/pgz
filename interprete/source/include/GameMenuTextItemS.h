#pragma once
#ifndef __GAME_MENUTEXTITEM_S_H__
#define __GAME_MENUTEXTITEM_S_H__

#include "GameMenuTextItem.h"
#include "GameMenuItemS.h"
#include "iSelectable.h"

class GameMenuTextItemS : public GameMenuTextItem, public GameMenuItemS
{
public:
	GameMenuTextItemS(TextLabel* text, int x, int y, Game* game, GameState* gstate);
	~GameMenuTextItemS();
};


#endif