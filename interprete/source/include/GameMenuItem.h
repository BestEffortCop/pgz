#pragma once
#ifndef __GAME_MENUITEM_H__
#define __GAME_MENUITEM_H__

#include "HelperTypes.h"

#include "Entity.h"
#include "iSelectable.h"

class GameMenuItem : public Entity
{
	protected:

	public:
		GameMenuItem(int x, int y, Game* game, GameState* gstate);
		~GameMenuItem();

		void setPos(int x, int y);
		void setGraphic(Graphic* g);
};

#endif