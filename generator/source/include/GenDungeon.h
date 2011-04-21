#pragma once

#ifndef _GENDUNGEON_H_
#define _GENDUNGEON_H_

#include <vector>
#include <string>
#include "DungeonM.h"
#include "DungeonJ.h"

using namespace std;

class GenDungeon {
	private:
		vector<Dungeon*>* dungeons;		// Vector en el que se guardan las mazmorras producidas por el generador
		
	public:
		GenDungeon();
		~GenDungeon();
		
		// Guarda y devuelve una referencia a una mazmorra creada en base a estos parámetros
		Dungeon* createDungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DBManager* db);
		// Devuelve una referencia a la mazmorra en la posición i-ésima del vector
		Dungeon* getDungeon(int i);
		// Devuelve la cantidad de mazmorras que han sido generadas
		int getNumDungeons();
		// Guarda en archivo la información de las mamzorras generadas hasta el momento
		void save();
};

#endif