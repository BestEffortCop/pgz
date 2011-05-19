#pragma once
#ifndef __LOADBLOCK_H__
#define __LOADBLOCK_H__

#include "Stamp.h"
#include "TileTextLabel.h"
#include "iSelectable.h"

class LoadBlock : public GameMenuItem/* public GameMenuController*/, public iSelectable {
	private:
		FriendlyTileMap 
			*iMoney,
			*iKey;
		int id;			// Identificador del archivo de carga

		TileFont* font;
		TileTextLabel 
			*moneyDisplay, 
			*hpDisplay, 
			*fileDisplay, 
			*pigeonsDisplay,
			*xDisplay;

		FriendlyTileMap* ihp;
	public:
		LoadBlock(int i, FILE* file, TileFont* font, int x, int y, Game* game, GameState* gstate);
		~LoadBlock();

		int getID();
		void onRender();
};

#endif