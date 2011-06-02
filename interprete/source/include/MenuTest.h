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

#include "GameMenuController.h"
#include "GameMenuStampItemS.h"
#include "Stamp.h"

class MenuTest : public GameMenuController
{

private:

	GameMenuItemS* i1;
	GameMenuItemS* i2;

	GameMenuItemS* i4;
	GameMenuItemS* i5;
	GameMenuItemS* i8;

	GameMenuItemS* i3;
	GameMenuItemS* i6;
	GameMenuItemS* i7;

public:
	MenuTest(int x, int y, Game* game, GameState* gstate);
	~MenuTest();

	void launch();
	void onChosen(iSelectable* selectable);
};

