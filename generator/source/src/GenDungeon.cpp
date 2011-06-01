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
	d = new FinalDungeon(zone, /*themeID*/"BORRAME!!!!!!!", gameDiff, dungNumber, ratio, tool, keyObj, dungeonPos, db);
	d->generate();
	dungeons->push_back(d);
	return d;
}