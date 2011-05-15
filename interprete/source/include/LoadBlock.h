#pragma once
#ifndef __LOADBLOCK_H__
#define __LOADBLOCK_H__

#include "TileTextLabel.h"
#include "GameMenuItem.h"
#include "Controller.h"

class LoadBlock : public GameMenuItem, public iSelectable {
	private:
		Controller* controller;

		int id;	// Identificador del archivo de carga

		TileFont* font;
		TileTextLabel* hpDisplay, 
			*progressDisplay,
			*moneyDisplay, 
			*heartPiecesDisplay, 
			*fileDisplay, 
			*timePlayedDisplay, 
			*dateDisplay, 
			*pigeonsDisplay,
			*cancelDisplay;
	public:
		LoadBlock(int i, Controller* c, FILE* file, TileFont* font, int x, int y, Game* game, GameState* gstate);
		~LoadBlock();

		int getID();
};

#endif