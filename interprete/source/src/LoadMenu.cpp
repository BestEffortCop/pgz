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

#include "LoadMenu.h"

LoadMenu::LoadMenu(int x, int y, Game* game, GameState* gstate, DataBaseInterface* dbi) : GameMenuController(x, y, game, gstate) {
	numSaves = ((PGZGame*)game)->controller->getMaxSaves();

	setGraphic(new Stamp(((PGZGame*) game)->controller->getDataBaseInterface()->getLoadMenu(), game->getGfxEngine()));

	setCursorImage(new Stamp(((PGZGame*) game)->controller->getDataBaseInterface()->getCursorLoad(), game->getGfxEngine()));

	Color colorEnabled = Color(38,38,38);

	menuFont = new TileFont(dbi->getFont(), game->getGfxEngine());

	loadBlocks = new vector<LoadBlock*>();
	char buffer[33];
	char str[80];

	FILE * f = NULL; LoadBlock* block;
	for (int i = 0; i < numSaves; i++){
		strcpy(str,"data/save");
		strcat(str,itoa(i,buffer,10));
		f = fopen(str, "rb");
		if (f != NULL){
			/*crear bloque de carga*/
			block = new LoadBlock(i, f, menuFont, 0, 65*(i+1), game, gstate);
			loadBlocks->push_back(block);
			block->setCursorLocation(NONE);
		}
	}
	cancel = new GameMenuTextItemS("Cancel ", menuFont, 85, 131, game, gstate);
	cancel->setCursorLocation(LEFT);

	if (loadBlocks->size() == 0)
		((PGZGame*)game)->resetGame();
}

LoadMenu::~LoadMenu() {
	delete menuFont;
	delete loadBlocks;
}

void LoadMenu::launch() {
	for (int i = 0; i < loadBlocks->size(); i++){
		addMenuItem(loadBlocks->at(i));
	}
	addMenuItem(cancel);
	GameMenuController::launch();
}

void LoadMenu::onStep() {
	GameMenuController::onStep();
}

void LoadMenu::onChosen(iSelectable* selectable) {
	int i = 0;
	bool selected = false;

	if (selectable == cancel){
		// Volver al mainMenu
		((PGZGame*)game)->resetGame();
	}
	else{
		while (!selected && i < numSaves){
			selected = selectable == loadBlocks->at(i);
			i++;
		}
		// Si se ha seleccionado algún bloque...
		if (selected){
			i--;
			((PGZGame*)game)->loadGame(loadBlocks->at(i)->getID());
		}
	}
}

iSelectable* LoadMenu::getMandatorySelectable(iSelectable* slc, Direction dir){
	switch (dir){
		case Direction::DOWN:
			if (slc == cancel){
				return cancel;
			}
			else{
				if (((LoadBlock*)slc)->getID() == loadBlocks->size() - 1){
					setCursorImage(new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getCursor(), game->getGfxEngine()));
					return cancel;
				}
				else return loadBlocks->at(((LoadBlock*)slc)->getID() + 1);
			}
			break;
		case Direction::UP:
			if (slc == cancel){
				setCursorImage(new Stamp(((PGZGame*) game)->controller->getDataBaseInterface()->getCursorLoad(), game->getGfxEngine()));
				return loadBlocks->at(loadBlocks->size() - 1);
			}
			else{
				if (((LoadBlock*)slc)->getID() == 0){
					return loadBlocks->at(0);
				}
				else return loadBlocks->at(((LoadBlock*)slc)->getID() - 1);
			}
			break;
		default:
			return slc;
	}
}

bool LoadMenu::isEmpty(){
	return loadBlocks->size() == 0;
}