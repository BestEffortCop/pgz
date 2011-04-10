#include "GenDungeon.h"

GenDungeon::GenDungeon() {
	dungeons = new vector<Dungeon*>();
}

GenDungeon::~GenDungeon() {
	vector<Dungeon*>::iterator it;
    for(it = dungeons->begin(); it != dungeons->end(); it++)
        if ((*it) != NULL)
        {
			delete (*it);
			(*it) = NULL;
        }
	delete dungeons;
	dungeons = NULL;
}

Dungeon* GenDungeon::createDungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, DBManager* db) {
	Dungeon* d = new DungeonM(zone, theme, gameDiff, dungNumber, ratio, tool, db);
	d->generate();
	dungeons->push_back(d);
	return d;
}

Dungeon* GenDungeon::getDungeon(int i) {
	if (i < 0 || i >= dungeons->size()) return NULL;
	
	return dungeons->at(i);
}

int GenDungeon::getNumDungeons()
{
	return dungeons->size();
}