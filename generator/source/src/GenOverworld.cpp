#include "GenOverworld.h"

GenOverworld::GenOverworld(Overworld* overworld, vector<GenZone*>* genZones, GenDungeon* genDungeon, Decorator* decorator, DBManager* myDB)
{
	this->overworld = overworld;
	this->genZones = genZones;
	this->myDB = myDB;
	this->genDungeon = genDungeon;
	this->decorator = decorator;
}
GenOverworld::~GenOverworld()
{
	overworld = NULL;
	genZones = NULL;
	myDB = NULL;
}

void GenOverworld::guardameSolids(string path)
{
	overworld->guardameSolids(path);
}

void GenOverworld::guardameZonas(string path)
{
	overworld->guardameZonas(path);
}

void GenOverworld::guardamePant(string path)
{
	overworld->guardamePant(path);
}

void GenOverworld::guardameAutotile(string path)
{
	overworld->guardameAutotile(path);
};