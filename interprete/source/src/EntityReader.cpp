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

#include "EntityReader.h"

#include "CollectableGameItem.h"
#include "TiledEntity.h"


EntityReader::EntityReader(Game* g, GameState* gs, DataBaseInterface* dbi)
{
	game = g;
	gamestate = gs;
	this->dbi = dbi;
};

EntityReader::~EntityReader()
{
};

bool EntityReader::readEntities(FILE* file, vector<Entity*>* screenEntities)
{
	short nentBuf[1];
	if (fread(nentBuf, sizeof(short), 1, file) < 1)
		return false; // fallar, avisar, salir

	short nentities = nentBuf[0];

	std::list<Entity*> specialEntities;

	short entitiesBuf[6];
	short entId;
	short entType;
	short entX, entY, entIdCol, entLinked2;
	Entity* ent = NULL;
	for (int i = 0; i < nentities; i++)
	{
		if (fread(entitiesBuf, sizeof(short), 5, file) < 1)
			return false;

		ent = NULL;
		entId = i;
		entType = entitiesBuf[0];
		entX = entitiesBuf[1];
		entY = entitiesBuf[2];
		entIdCol = entitiesBuf[3];
		entLinked2 = entitiesBuf[4];
	}

	return true;
};