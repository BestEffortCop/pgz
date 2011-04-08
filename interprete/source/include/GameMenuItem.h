#pragma once
#ifndef __GAME_MENUITEM_H__
#define __GAME_MENUITEM_H__

#include "Entity.h"

class GameMenuItem : public Entity
{
	public:
		GameMenuItem(int x, int y, Game* game, GameState* gstate);
		~GameMenuItem();

		void setPos(int x, int y);
		void setGraphic(Graphic* g);
};

#endif