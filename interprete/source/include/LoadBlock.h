#pragma once
#ifndef __LOADBLOCK_H__
#define __LOADBLOCK_H__

#include "Stamp.h"
#include "TileTextLabel.h"
//#include "Controller.h"

//class Controller;

class LoadBlock/* : public GameMenuItem, public iSelectable*/ {
	private:
		//Controller* controller;
		Stamp* iMoney;
		Stamp* iKey;
		int id;	// Identificador del archivo de carga

		TileFont* font;
		TileTextLabel *moneyDisplay, *heartPiecesDisplay, *fileDisplay, *pigeonsDisplay;
	public:
		LoadBlock(/*int i, Controller* c, FILE* file, TileFont* font, int x, int y, Game* game, GameState* gstate*/);
		~LoadBlock();

		int getID();
};

#endif