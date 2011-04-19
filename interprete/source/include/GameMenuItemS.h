#pragma once
#ifndef __GAME_MENUITEM_S_H__
#define __GAME_MENUITEM_S_H__

#include "GameMenuItem.h"
#include "iSelectable.h"

class GameMenuItemS : public GameMenuItem, public iSelectable
{
public:
	GameMenuItemS(int x, int y, Game* game, GameState* gstate);
	~GameMenuItemS();

	void setGraphic(Graphic* g);
};

#endif
