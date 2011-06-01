/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once
#ifndef __TOOLMENU_H__
#define __TOOLMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"
#include "GameMenuItemS.h"

#include "Stamp.h"
#include "PGZGame.h"

#include <vector>

//Centro real 112,96
//Centro para que se dibuje bien 112 - 16/2 , 96 -16/2
//Radio 60

#define Pi 3.1415f

class ToolMenu : public GameMenuController
{

protected:
	vector<GameMenuItemS*>* iTools;
	GameMenuTextItem * iText;
	vector<int> idTools;
	TileFont* menuFont;

	int centroX;
	int centroY;
	int radio;


public:
	ToolMenu(int x, int y, Game* game, GameState* gstate,int centroX = 104, int centroY = 88, int radio = 60);
	~ToolMenu();

	void launch();

	void onStep();
	void onRender();
	void onChosen(iSelectable* selectable);
	void onCancelled(iSelectable* selectable);
	void onStartPressed(iSelectable* selectable);

	iSelectable* getMandatorySelectable(iSelectable* slc, Direction dir);
	iSelectable* getAlternativeSelectable(iSelectable* slc, Direction dir);
};

#endif __TOOLMENU_H__