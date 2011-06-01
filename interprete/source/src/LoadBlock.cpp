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

#include "LoadBlock.h"
#include "PGZGame.h"

LoadBlock::LoadBlock(int i, FILE* file, TileFont* font, int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate)/*GameMenuController(x, y, game, gstate)*/, iSelectable(x, y, 100,100){
	this->font = font;
	id = i;

	// Hacemos una carga
	((PGZGame*)game)->controller->getData()->load(file);

	char buffer[33];
	char str[80];
	strcpy (str,"file ");
	strcat (str,itoa(i,buffer,10));
	fileDisplay = new TileTextLabel(str, font, game->getGfxEngine(),6, 1);

	/* ------------- Life -------------------- */
	ihp = new FriendlyTileMap(16, 16, game->getGfxEngine());
	ihp->setTileSet(((PGZGame*)game)->controller->getDataBaseInterface()->getHud());
	ihp->setScale(0.5f,0.5f);

	/* ------------- Money ----------------- */
	iMoney = new FriendlyTileMap(16, 16, game->getGfxEngine());
	iMoney->setTileSet(((PGZGame*)game)->controller->getDataBaseInterface()->getHud());
	int** map = (int**)malloc(sizeof(int*)*1);
	map[0] = (int*) malloc(sizeof(int));
	map[0][0] = 4;
	iMoney->setMap(map, 1, 1);
	iMoney->setScale(0.8f,0.8f);

	itoa(((PGZGame*)game)->controller->getData()->getCurrentMoney(), buffer, 10);
	moneyDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 5, 1);

	/* ------------ Pigeons------------------ */
	iKey = new FriendlyTileMap(16, 16, game->getGfxEngine());
	iKey->setTileSet(((PGZGame*)game)->controller->getDataBaseInterface()->getHud());
	map = (int**)malloc(sizeof(int*)*1);
	map[0] = (int*) malloc(sizeof(int));
	map[0][0] = 3;
	iKey->setMap(map, 1, 1);
	iKey->setScale(0.8f,0.8f);

	itoa(((PGZGame*)game)->controller->getData()->getNumPigeons(), buffer, 10);
	pigeonsDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);

	xDisplay = new TileTextLabel("x", font, game->getGfxEngine(), 1, 1);
}

LoadBlock::~LoadBlock(){
	delete fileDisplay;
	delete moneyDisplay;
	delete pigeonsDisplay;
	delete iMoney;
	delete iKey;
	delete xDisplay;
	delete ihp;
}

int LoadBlock::getID(){
	return id;
}

void LoadBlock::onRender(){
	int filex = x + 4;
	int filey = y + 10;
	int imoneyx = filex + 10;
	int imoneyy = filey + 15;
	int moneyx = imoneyx + 20;
	int moneyy = imoneyy;
	int ikeyx = imoneyx;
	int ikeyy = imoneyy + 20;
	int keyx = ikeyx + 20;
	int keyy = ikeyy;
	int hpx = moneyx + 100;
	int hpy = imoneyy;

	fileDisplay->render(filex, filey);

	iKey->render(ikeyx, ikeyy);
	xDisplay ->render(ikeyx + 10, ikeyy);
	pigeonsDisplay->render(keyx, keyy);

	iMoney->render(imoneyx, imoneyy);
	xDisplay->render(imoneyx + 10, imoneyy);
	moneyDisplay->render(moneyx, moneyy);

	//Calculo las dimensiones de la vida
	int cols = (((PGZGame*)game)->controller->getData()->getMaxLife()/4);
	int rows = 1;

	if (cols > 13) {
		rows = cols/13 + 1;
		cols = 13;
	}

	int**map = (int**) malloc(cols*sizeof(int*));
	for (int i = 0; i < cols;i++)
		map[i] = (int*) malloc(rows*sizeof(int));

	for (int i = 0; i < cols;i++)
		for (int j = 0; j < rows;j++) {
			if ((i + j*cols)*4 < ((PGZGame*)game)->controller->getData()->getMaxLife())
				map[i][j] = 0;
			else if (((i + j*cols)*4 > ((PGZGame*)game)->controller->getData()->getMaxLife()) && (((i+ j*cols) - 1)*4< ((PGZGame*)game)->controller->getData()->getMaxLife()))
				map[i][j] = 1;
			else if((i + j*cols) >= ((PGZGame*)game)->controller->getData()->getMaxLife())
				map[i][j] = -1;
			else
				map[i][j] = 2;
		}

	ihp->setMap(map, cols, rows);
	ihp->setScale(0.5f,0.5f);
	ihp->render(hpx,hpy);
}