#pragma once

#ifndef _FINALDUNGEON_H_
#define _FINALDUNGEON_H_

#define FINAL_SCREEN 0
#define LOCK_SCREEN 1

#include "Dungeon.h"
#include "DunScreen.h"
#include "Screen.h"
#include "DBManager.h"

class FinalDungeon: public Dungeon {

	private:

		void generateLockScreen();

		void generateFinalScreen(); 

		void allocateSolids(DunScreen* ds, int type);

		// puertas y paredes copia de dunScreen // por no hacer público el que ya tiene
		void placeWalls(DunScreen* ds);

	public:
		// Debe encargarse de realizar las operaciones con la BDI
		FinalDungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db);

		// Destructora
		~FinalDungeon();

		// Desencadena la generación de la mazmorra 
		void generate();
};

#endif