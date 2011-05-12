#pragma once

#ifndef _FINALDUNGEON_H_
#define _FINALDUNGEON_H_

#include "Dungeon.h"
#include "DunScreen.h"
#include "DBManager.h"

class FinalDungeon: public FinalDungeon {

	private:
		
	public:
		// Debe encargarse de realizar las operaciones con la BDI
		FinalDungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db);

		// Destructora
		~FinalDungeon();

		// Desencadena la generación de la mazmorra 
		void generate();
};

#endif