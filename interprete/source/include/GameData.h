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

#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <vector>
#include "GameStatus.h"

// Almacena info invariable sobre el juego
// y guarda la clase que almacena la info variable
class GameData 
{
private:
	int neededHeartPieces;
	GameStatus* gameStatus;

public:
	GameData();
	~GameData();

	void init(int maxHeartPieces, int maxPigeons, int maxKeyItems);

	int getNeededHeartPieces();
	void setNeededHeartPieces(int number);

	GameStatus* getGameStatus();

	int maxKeyItems;
	int maxPigeons;

	int getMaxKeyItems();
	void setMaxKeyItems(int number);
	int getMaxPigeons();
	void setMaxPigeons(int number);

	void save(FILE* f);
	void load(FILE* f);
};
#endif
