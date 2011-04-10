#pragma once

#ifndef _GENDUNGEON_H_
#define _GENDUNGEON_H_

#include <vector>
#include <string>
#include "DungeonM.h"

using namespace std;

class GenDungeon {
	private:
		vector<Dungeon*>* dungeons;
		
	public:
		GenDungeon();
		~GenDungeon();
		
		Dungeon* createDungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, DBManager* db);
		Dungeon* getDungeon(int i);
		int getNumDungeons();
};

#endif