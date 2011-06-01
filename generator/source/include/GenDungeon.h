/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
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

#ifndef _GENDUNGEON_H_
#define _GENDUNGEON_H_

#include <vector>
#include <string>
#include "DungeonM.h"
#include "DungeonJ.h"
#include "FinalDungeon.h"

using namespace std;

class GenDungeon {
	private:
		vector<Dungeon*>* dungeons;		// Vector en el que se guardan las mazmorras producidas por el generador
		
	public:
		GenDungeon();
		~GenDungeon();
		
		// Guarda y devuelve una referencia a una mazmorra creada en base a estos parámetros
		Dungeon* createDungeon(string zone, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db);
		// Devuelve una referencia a la mazmorra en la posición i-ésima del vector
		Dungeon* getDungeon(int i);
		// Devuelve la cantidad de mazmorras que han sido generadas
		int getNumDungeons();
		// Guarda en archivo la información de las mamzorras generadas hasta el momento
		void save(std::string);
		//crea la p
		Dungeon* createFinalDungeon(string zone, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db);
};

#endif