#include "GenOverworld.h"

GenOverworld::GenOverworld(Overworld* overworld, vector<GenZone*>* genZones, DBManager* myDB)
{
	this->overworld = overworld;
	this->genZones = genZones;
	this->myDB = myDB;
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