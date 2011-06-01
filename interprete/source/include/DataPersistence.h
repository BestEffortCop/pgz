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
#ifndef __DATAPERSISTENCE_H__
#define __DATAPERSISTENCE_H__

#include <vector>

#include "GameData.h"
#include "MapData.h"

class DataPersistence
{
private:
	GameData* gameData;
	std::vector<MapData*> mapDataList;
	int numMapas;

public:
	DataPersistence();
	~DataPersistence();
	bool addMapData(int mapId, char type, int w, int h, const int** layout, int numPuzzles, int numDoors, int numMinibosses, int numCollectables);

	GameData* getGameData();
	MapData* getMapData(int mapId);
	int getMapNumber();

	void save(string path);
	bool load(FILE* f);

	int getMaxLife();
	int getCurrentMoney();
	int getGameProgress();
	int getNumPigeons();
};

#endif