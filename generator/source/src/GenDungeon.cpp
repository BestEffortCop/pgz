#include "GenDungeon.h"

GenDungeon::GenDungeon() {
	dungeons = new vector<Dungeon*>();
}

GenDungeon::~GenDungeon() {
	for (vector<Dungeon*>::iterator it = dungeons->begin(); it < dungeons->end(); it++)
		delete *it;
	delete dungeons; dungeons = NULL;
}

Dungeon* GenDungeon::createDungeon(string zone, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db) {
	Dungeon* d = NULL;
	// Donde pone forest irá zone, pero por ahora no, que sale debris (Rafa)
	if (rand() % 2 == 0) 
		d = new DungeonM("Forest", "cosa", gameDiff, dungNumber, ratio, tool, keyObj, dungeonPos, db);
	else
		d = new DungeonJ("Forest", /*themeID*/"BORRAME!!!!!!!", gameDiff, dungNumber, ratio, tool, keyObj, dungeonPos, db);

	d->generate();
	dungeons->push_back(d);
	return d;
}

Dungeon* GenDungeon::getDungeon(int i) {
	if (i < 0 || i >= (int)dungeons->size()) return NULL;
	
	return dungeons->at(i);
}

int GenDungeon::getNumDungeons()
{
	return dungeons->size();
}

void GenDungeon::save(std::string path) {
	for (vector<Dungeon*>::iterator it = dungeons->begin(); it < dungeons->end(); it++)
		(*it)->save(path);
}

Dungeon* GenDungeon::createFinalDungeon(string zone, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db)
{
	Dungeon* d = NULL;
	d = new DungeonJ(zone, /*themeID*/"BORRAME!!!!!!!", gameDiff, dungNumber, ratio, tool, keyObj, dungeonPos, db);
	d->generate();
	dungeons->push_back(d);
	return d;
}