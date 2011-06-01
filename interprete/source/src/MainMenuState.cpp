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

#include "MainMenuState.h"


MainMenuState::MainMenuState(int w, int h, Game* g) : GameState(g, w, h)
{
	mainMenu = new MainMenu(0, 0, g, this, ((PGZGame*) game)->controller->getDataBaseInterface());

	mainMenu->setInputConfig(((PGZGame*) game)->controller->mainInputConfig);
	mainMenu->launch();
	loadMenu = NULL;
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::changeMenu(){
	if (loadMenu == NULL)
			loadMenu = new LoadMenu(0, 0, (PGZGame*)game, this, ((PGZGame*) game)->controller->getDataBaseInterface());

	if (!loadMenu->isEmpty()){
		mainMenu->quit();
		loadMenu->setInputConfig(((PGZGame*) game)->controller->mainInputConfig);
		loadMenu->launch();
	}
}
