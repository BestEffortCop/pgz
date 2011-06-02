/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef __STATEMENU_H__
#define __STATEMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"
#include "FriendlyTileMap.h"

#include "Stamp.h"
#include "PGZGame.h"

enum Focus {MAP, SAVEEXIT, MAIN};

class StateMenu : public GameMenuController
{

protected:
	GameMenuTextItemS* save;
	GameMenuTextItemS* exit;
	GameMenuTextItem* tPidgeons;

	//Porque tenemos que dibujar tantos como maximo de keyitems halla
	vector<GameMenuItem*>* keyItems;

	GameMenuItemS* saveExit;

	GameMenuItemS* miniMap;
	GameMenuItem* backgroundMiniMap;
		Image* bgImage;

	GameMenuItem* bossKey;
	GameMenuItem* pidgeons;


	TileFont* menuFont;
	Focus focus;

	FriendlyTileMap* getMiniMap();
	void moveMap(Direction dir);

public:
	
	StateMenu(int x, int y, Game* game, GameState* gstate);
	~StateMenu();

	void launch();
	
	//void onStep();
	void onRender();
	void onChosen(iSelectable* selectable);
	void onCancelled(iSelectable* selectable);
	void onSelectPressed(iSelectable* selectable);
	
	iSelectable* getMandatorySelectable(iSelectable* slc, Direction dir);
	
};

#endif __STATEMENU_H__
